/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { FormattingOptions, LexicalRange } from "../index";

import { Token } from "antlr4ts";
import { Interval } from "antlr4ts/misc";

import { ANTLRv4Lexer } from "../parser/ANTLRv4Lexer";

// The result list is a collection of insert markers which direct the text generation process.
// Such a marker either is an index into the source token list (if >= 0) or marks special behavior.
enum InsertMarker {
    // Token markers.
    // EOF is -1
    LineBreak = -2,
    Space = -3,
    Tab = -4,

    // Markers for a group of elements.
    Whitespace = -100,
    Comment = -101,

    // Action markers.
    WhitespaceEraser = -102, // Marker for any comming whitespace to be ignored.

    // Block marker.
    Range = -1000 // Indirect index into a range table.
}

export class GrammarFormatter {
    constructor(private tokens: Token[]) { }

    private setDefaultOptions() {
        this.options = {};
        this.options.alignConsecutiveDeclarations = false;
        this.options.alignTrailingComments = false;
        this.options.allowShortBlocksOnASingleLine = true;
        this.options.breakBeforeBraces = false;
        this.options.columnLimit = 100;
        this.options.indentWidth = 4;
        this.options.continuationIndentWidth = this.options.indentWidth;
        this.options.keepEmptyLinesAtTheStartOfBlocks = false;
        this.options.maxEmptyLinesToKeep = 1;
        this.options.reflowComments = true;
        this.options.spaceBeforeAssignmentOperators = true;
        this.options.tabWidth = 4;
        this.options.useTab = true;

        this.options.alignColon = false;
        this.options.allowShortRulesOnASingleLine = true;
        this.options.alignTrailingPredicates = true;
        this.options.alignSemicolon = "ownLine";
        this.options.breakBeforeParens = false;
        this.options.ruleInternalsOnSingleLine = false;
        this.options.minEmptyLines = 0;
    }

    /** Is the value at the given index in the token list of the given type? */
    private entryIs(index: number, marker: InsertMarker): boolean {
        if (index < 0 || index >= this.tokenList.length) {
            return false;
        }

        const entry = this.tokenList[index];
        switch (marker) {
            case InsertMarker.Whitespace:
                return entry == InsertMarker.LineBreak || entry == InsertMarker.Space || entry == InsertMarker.Tab;

            case InsertMarker.Comment: {
                if (entry < 0) {
                    return false;
                }
                const token = this.tokens[entry];
                return token.type == ANTLRv4Lexer.BLOCK_COMMENT || token.type == ANTLRv4Lexer.LINE_COMMENT
                    || token.type == ANTLRv4Lexer.DOC_COMMENT;
            }

            default: {
                if (entry < 0) {
                    return entry == marker;
                }
                const token = this.tokens[entry];
                return token.type == marker;
            }
        }
    }

    private lastEntryIs(marker: InsertMarker): boolean {
        return this.entryIs(this.tokenList.length - 1, marker);
    }

    /**
     * Skips over all comments and whitespaces backwards and checks the value of the value after that.
     * @param type A token type to check for.
     */
    private lastCodeTokenIs(marker: InsertMarker): boolean {
        let i = this.tokenList.length - 1;
        while (i >= 0) {
            if (!this.entryIs(i, InsertMarker.WhitespaceEraser)
                && !this.entryIs(i, InsertMarker.Whitespace)
                && !this.entryIs(i, InsertMarker.LineBreak)
                && !this.entryIs(i, InsertMarker.Comment)) {
                break;
            }
            --i;
        }
        if (i < 0) {
            return false;
        }
        return this.tokens[this.tokenList[i]].type == marker;
    }

    /**
     * Scan the token list backwards up to the last line break or any non-whitespace token, whichever comes first.
     * @return true if a line break came first.
     */
    private isFirstNonWhitespaceTokenOnLine(): boolean {
        let i = this.tokenList.length - 1;
        while (i >= 0) {
            if (this.entryIs(i, InsertMarker.LineBreak)) {
                return true;
            }
            if (!this.entryIs(i, InsertMarker.Whitespace)) {
                return false;
            }
            --i;
        }
        return true;
    }

    private removeLastEntry() {
        if (this.formattingDisabled) {
            return;
        }

        let lastEntry = this.tokenList[this.tokenList.length - 1];
        this.tokenList.pop();
        switch (lastEntry) {
            case InsertMarker.WhitespaceEraser:
                break; // Ignore.
            case InsertMarker.LineBreak:
                --this.currentLine;
                break;
            default:
                --this.currentColumn;
                break;
        }
        console.assert(this.currentLine >= 0, "Current line can never be less than 0");
        console.assert(this.currentColumn >= 0, "Current column can never be less than 0");
    }

    /**
     * Scans backwards and removes line breaks up to the first non line break token.
     * @param tokenList The list to work on.
     */
    private removeTrailingLineBreaks() {
        if (this.formattingDisabled) {
            return;
        }

        while (this.lastEntryIs(InsertMarker.LineBreak)) {
            this.removeLastEntry();
        }
    }

    /**
     * Scans backwards and removes any whitespace up to the first non-whitespace.
     * @param tokenList The list to work on.
     */
    private removeTrailingWhitespaces() {
        if (this.formattingDisabled) {
            return;
        }

        while (this.lastEntryIs(InsertMarker.Whitespace)) {
            this.removeLastEntry();
        }
    }

    private pushCurrentIndentation() {
        if (this.formattingDisabled) {
            return;
        }

        console.assert(this.currentColumn == 0, "Current column cannot be > 0 when setting new indentation");

        if (this.options.useTab) {
            this.tokenList.push(...Array(this.currentIndentation).fill(InsertMarker.Tab));
        } else {
            this.tokenList.push(...Array(this.currentIndentation * this.options.tabWidth!).fill(InsertMarker.Space));
        }
        this.currentColumn = this.currentIndentation * this.options.tabWidth!;
    }

    /**
     * Inserts the given marker into the result list, but checks if the entry before `index` is a single line comment.
     * If that's the case we need special handling here.
     */
    private insert(index: number, marker: InsertMarker) {
        if (this.formattingDisabled) {
            return;
        }

        let self = this;

        /** Helper function to insert a block with embedded line breaks. */
        function insertBlock(token: Token): void {
            let parts = token.text!.split("\n");
            if (parts.length == 1) {
                self.currentColumn += token.text!.length;
            } else {
                self.currentLine += parts.length - 1;
                self.currentColumn = parts[parts.length - 1].length; // TODO: should probably handle tabs here.
            }
            self.tokenList.splice(index, 0, marker);
        }

        switch (marker) {
            case InsertMarker.WhitespaceEraser: { // Doesn't move current position.
                this.tokenList.splice(index, 0, marker);
                break;
            }

            case InsertMarker.LineBreak: {
                this.tokenList.splice(index, 0, marker);
                ++this.currentLine;
                this.currentColumn = 0;
                break;
            }

            default: {
                var doDefault = true;

                var token: Token | undefined;
                if (marker >= 0) {
                    token = this.tokens[marker];
                }

                const insertLength = token ? token.stopIndex - token.startIndex + 1 : 1;

                // Check for a trailing line comment at the current token list end (if we add there).
                if (index == this.tokenList.length && this.lastEntryIs(ANTLRv4Lexer.LINE_COMMENT)) {
                    if (token) {
                        // Pending line breaks are usually transparent for comments (handled after them).
                        // But when adding a comment after a single line comment there can only be a line break between them.
                        if (token.type == ANTLRv4Lexer.LINE_COMMENT || token.type == ANTLRv4Lexer.BLOCK_COMMENT || token.type == ANTLRv4Lexer.DOC_COMMENT) {
                            this.lineBreakPending = false;
                            ++this.currentLine;
                            this.currentColumn = 0;
                            this.tokenList.push(InsertMarker.LineBreak);
                            this.pushCurrentIndentation();
                            this.tokenList.push(marker);

                            if (token.type == ANTLRv4Lexer.BLOCK_COMMENT) {
                                insertBlock(token);
                            } else {
                                this.currentColumn += insertLength;
                            }
                        } else {
                            // Not a comment that should be added, so move the new entry *before* the line comment.
                            this.tokenList.splice(this.tokenList.length - 1, 0, marker);
                            this.currentColumn += insertLength;
                        }
                    } // Values < 0 can be ignored here (shouldn't be added after a line comment).

                    doDefault = false;
                    break;
                }

                if (token) {
                    switch (token.type) {
                        case ANTLRv4Lexer.BLOCK_COMMENT: {
                            insertBlock(token);
                            doDefault = false;
                            break;
                        }

                        case ANTLRv4Lexer.ACTION_CONTENT: { // Action content can contain line breaks.
                            insertBlock(this.tokens[marker]);
                            doDefault = false;
                            break;
                        }
                    }
                }

                if (doDefault) {
                    this.tokenList.splice(index, 0, marker);
                    this.currentColumn += insertLength;
                }

                break;
            }
        }
    }

    private add(marker: InsertMarker) {
        this.insert(this.tokenList.length, marker);
    }

    /**
     * Computes the new column offset we get when adding the given text.
     * There must be no linebreaks in the text.
     */
    private updateCurrentColumn(text: string) {
        for (let char of text) {
            if (char == "\t") {
                // Round up column offset to next tab stop.
                let offsetToNextTabStop = this.options.tabWidth! - (this.currentColumn % this.options.tabWidth!);
                this.currentColumn += offsetToNextTabStop;
            } else {
                ++this.currentColumn;
            }
        }
    }

    /**
     * Used only for real tokens (indices), e.g. in non-formatting mode.
     * Inserts a range for the given start and end markers.
     * No processing takes place, except for line/column updates.
     */
    private addRaw(start: InsertMarker, stop: InsertMarker) {
        let interval = Interval.of(this.tokens[start].startIndex, this.tokens[stop].stopIndex);
        let text = this.tokens[0].inputStream!.getText(interval);

        if (text.indexOf("\n") >= 0) {
            let parts = text.split("\n");
            this.currentColumn = 0;
            this.currentLine += parts.length - 1;
            this.updateCurrentColumn(parts[parts.length - 1]);
        } else {
            this.updateCurrentColumn(text);
        }
        this.ranges.push([start, stop]);
        this.tokenList.push(InsertMarker.Range - this.currentRangeIndex++);
    }

    private addSpace() {
        if (!this.lastEntryIs(InsertMarker.Space)) {
            this.insert(this.tokenList.length, InsertMarker.Space);
        }
    }

    private addLineBreak() {
        this.lineBreakPending = false;
        if (this.singleLineBlockNesting == 0) {
            this.insert(this.tokenList.length, InsertMarker.LineBreak);
        }
    }

    /**
     * Goes backward in the already created token list until the first non-whitespace and non-comment
     * token is found and inserts the given type after that.
     * @param type The type to insert.
     * @param whitSpace If true insert also a space (before the inserted type).
     */
    private insertAfterLastFullToken(marker: InsertMarker, withSpace: boolean) {
        if (this.formattingDisabled) {
            return;
        }

        let i = this.tokenList.length - 1;
        while (i > 0) {
            if (!this.entryIs(i, InsertMarker.Whitespace) && !this.entryIs(i, InsertMarker.Comment)) {
                break;
            }
            --i;
        }

        if (i > 0) {
            let newEntries = [marker];
            if (withSpace) {
                newEntries.unshift(InsertMarker.Space);
            }
            this.tokenList.splice(i + 1, 0, ...newEntries);
        }
    }

    /**
     * Ensure there are at least as many empty lines as specified in the options,
     * but not more than max empty lines.
     */
    private ensureMinEmptyLines(): void {
        if (this.formattingDisabled) {
            return;
        }

        if (this.options.minEmptyLines! > 0) {
            let lineBreakCount = Math.min(this.options.minEmptyLines!, this.options.maxEmptyLinesToKeep!) + 1;
            for (let i = this.tokenList.length - 1; i > 0 && lineBreakCount > 0; --i) {
                if (this.entryIs(i, InsertMarker.LineBreak)) {
                    --lineBreakCount;
                } else {
                    break;
                }
            }
            this.tokenList.push(...Array(lineBreakCount).fill(InsertMarker.LineBreak));
            this.currentLine += lineBreakCount;
        }
    }

    private handlePendingLinebreak(): boolean {
        if (this.lineBreakPending) {
            this.lineBreakPending = false;
            if (this.singleLineBlockNesting > 0) {
                return true;
            }

            this.removeTrailingWhitespaces();
            this.addLineBreak();
            if (this.currentIndentation == 0) {
                // On top level. Ensure min empty lines.
                this.ensureMinEmptyLines();
            } else {
                this.pushCurrentIndentation();
            }
            return true;
        }
        return false;
    }

    /**
     * Starting from position i this methods scans forward in the input token list to determine
     * if the block contains alternatives and how long it would be (in characters) if the block would be
     * formatted on a single line. If there's a single line comment somewhere we cannot do such a simple formatting, however.
     *
     * @param i The position to start scanning from. Should point to either a colon or an opening parenthesis.
     */
    private getBlockInfo(i: number): [boolean, number] {
        let containsAlts = false;
        let overallLength = 1;
        let blockEnd = ANTLRv4Lexer.RPAREN;
        if (this.tokens[i].type == ANTLRv4Lexer.COLON) {
            blockEnd = ANTLRv4Lexer.SEMI;
            ++overallLength; // The space we'll add after the colon.
        }

        let nestingLevel = 0;

        while (++i < this.tokens.length) {
            let token = this.tokens[i];
            switch (token.type) {
                case ANTLRv4Lexer.WS: {
                    // Ignore whitespaces. We account for them below.
                    break;
                }

                case ANTLRv4Lexer.LPAREN: {
                    ++nestingLevel;
                    ++overallLength;
                    break;
                }

                case ANTLRv4Lexer.RPAREN: {
                    ++overallLength;

                    // In unbalanced blocks return if we cannot unwind.
                    if (nestingLevel == 0
                        || (nestingLevel == 1 && (blockEnd == ANTLRv4Lexer.RPAREN))) {
                        return [containsAlts, overallLength];
                    }
                    --nestingLevel;
                    break;
                }

                case ANTLRv4Lexer.SEMI: {
                    ++overallLength;
                    if (blockEnd == ANTLRv4Lexer.SEMI) {
                        return [containsAlts, overallLength];
                    }
                    break;
                }

                case ANTLRv4Lexer.QUESTION:
                case ANTLRv4Lexer.STAR:
                case ANTLRv4Lexer.PLUS: {
                    ++overallLength; // No addition for a space. That happened already.
                    break;
                }

                case ANTLRv4Lexer.LINE_COMMENT:
                case ANTLRv4Lexer.POUND: {
                    // Single line comments cannot be formatted on a single line (they would hide what follows).
                    // Same for alt labels. Signal that by a large overall length.
                    overallLength = 1e100;
                    break;
                }

                case ANTLRv4Lexer.BLOCK_COMMENT:
                case ANTLRv4Lexer.DOC_COMMENT: {
                    // If the comment contains a linebreak we cannot format the block as single line.
                    if (token.text!.indexOf("\n") >= 0) {
                        overallLength = 1e100;
                    } else {
                        overallLength += token.text!.length + 1;
                    }
                    break;
                }

                case ANTLRv4Lexer.BEGIN_ACTION:
                case ANTLRv4Lexer.ACTION_CONTENT:
                case ANTLRv4Lexer.END_ACTION: {
                    // No extra space. These are entire blocks we take over as they are.
                    if (token.text == "\n") {
                        overallLength = 1e100;
                    } else {
                        ++overallLength;
                    }
                    break;
                }

                case ANTLRv4Lexer.OR: {
                    containsAlts = true;
                    overallLength += 2;
                    break;
                }

                default:
                    if (token.text) {
                        overallLength += token.text.length;
                    }
                    ++overallLength; // Add one for a space char which must follow this token.
                    break;
            }
        }

        return [containsAlts, overallLength];
    }

    public formatGrammar(options: FormattingOptions, range: LexicalRange): [string, LexicalRange] {
        this.setDefaultOptions();
        this.options = Object.assign(this.options, options); // Overwrite default values with passed in values.

        this.tokenList = [];
        this.currentIndentation = 0;
        this.singleLineBlockNesting = 0

        this.ranges = [];
        this.currentRangeIndex = 0;

        // Position info of the target text.
        this.currentColumn = 0;
        this.currentLine = 0;
        this.lineBreakPending = false;
        this.formattingDisabled = false;

        let coalesceWhitespaces = false; // Set in situations where we don't want more than a single space char.
        let inBraces = false; // Set between {} (e.g. in options and action blocks).
        let inRule = false;   // Set when we are processing a lexer or parser rule.
        let inNamedAction = false;
        let inLexerCommand = false;
        let inCatchFinally = false;
        let rangeStart = 0;

        // Outside of braces is the grammar introducer command the only one ending in a semicolon.
        // We must not format that like rules, so we add a special state only for this entry.
        let introducerDone = false;

        for (let i = 0; i < this.tokens.length; ++i) {
            let token = this.tokens[i];

            // If no whitespace is coming up we don't need the eraser marker anymore.
            if (token.type != ANTLRv4Lexer.WS && this.lastEntryIs(InsertMarker.WhitespaceEraser)) {
                this.tokenList.pop();
            }

            switch (token.type) {
                case ANTLRv4Lexer.WS: {
                    if (i == 0 || this.formattingDisabled) {
                        // Ignore leading whitespaces at the beginning of the grammar.
                        break;
                    }
                    if (this.lastEntryIs(InsertMarker.WhitespaceEraser)) {
                        // And ignore these incomming whitespaces if there is an eraser marker.
                        this.tokenList.pop();
                        break;
                    }

                    // Analyze whitespaces, we can have a mix of tab/space and line breaks here.
                    let text = token.text!.replace("\r\n", "\n");
                    if (coalesceWhitespaces || (this.singleLineBlockNesting > 0) || text.indexOf("\n") < 0) {
                        // Spaces only. Cannot be at the start of a line, so simply convert them to a single space
                        // unless we need to align following text.
                        if (!this.lastEntryIs(InsertMarker.Whitespace)) {
                            this.addSpace();
                        }
                        break;
                    }

                    let parts = text.split("\n");

                    // Take into account any linebreaks that are already in the pipeline.
                    this.handlePendingLinebreak();
                    let j = this.tokenList.length - 1;
                    while (j >= 0) {
                        if (this.entryIs(j, InsertMarker.LineBreak)) {
                            parts.unshift("");
                        } else {
                            break;
                        }
                        --j;
                    }

                    this.removeTrailingWhitespaces();

                    let breakCount = parts.length - 1 <= this.options.maxEmptyLinesToKeep! ? parts.length - 1 : this.options.maxEmptyLinesToKeep! + 1;
                    this.tokenList.push(...Array(breakCount).fill(InsertMarker.LineBreak));
                    this.currentLine += breakCount;
                    this.currentColumn = 0;

                    // If the last entry is not empty we got some indentation for the same line.
                    // Replace this by our current indentation.
                    if (parts[parts.length - 1].length > 0) {
                        this.pushCurrentIndentation();
                    }
                    break;
                }

                case ANTLRv4Lexer.SEMI: {
                    this.removeTrailingWhitespaces();
                    if (introducerDone && !inBraces && inRule) {
                        switch (this.options.alignSemicolon) {
                            case "trailing":
                                this.insertAfterLastFullToken(i, true);
                                break;
                            case "ownLine":
                                this.addLineBreak();
                                break;
                            case "ownLineIndent":
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                                break;
                            case "ownLineAlign":
                                this.addLineBreak();
                                this.pushCurrentIndentation(); // TODO: real alignment.
                                break;
                        }
                        this.add(i);
                        if (this.currentIndentation > 0) {
                            --this.currentIndentation;
                        }
                    } else {
                        this.add(i);
                    }
                    this.lineBreakPending = true;

                    // Set to 0 regardless of what it was when entering here.
                    // This way we can better handle unbalanced nested blocks.
                    this.singleLineBlockNesting = 0;

                    coalesceWhitespaces = false;
                    introducerDone = true;
                    inLexerCommand = false;
                    if (!inBraces) {
                        inRule = false;
                    }
                    break;
                }

                case ANTLRv4Lexer.LBRACE: {
                    if (this.options.breakBeforeBraces) {
                        this.removeTrailingWhitespaces();
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                        this.add(i);
                    } else {
                        this.removeTrailingWhitespaces();
                        this.addSpace();
                        this.add(i);
                        this.lineBreakPending = true;
                    }
                    ++this.currentIndentation;
                    inBraces = true;
                    break;
                }

                case ANTLRv4Lexer.RBRACE: {
                    this.removeTrailingWhitespaces();
                    this.addLineBreak();
                    if (this.currentIndentation > 0) {
                        --this.currentIndentation;
                    }
                    this.pushCurrentIndentation();
                    this.add(i);
                    this.addLineBreak();
                    inBraces = false;
                    coalesceWhitespaces = false;
                    inRule = false;
                    break;
                }

                case ANTLRv4Lexer.BEGIN_ACTION: {
                    if (this.formattingDisabled) {
                        break;
                    }

                    this.handlePendingLinebreak();
                    this.add(i++);
                    if (inCatchFinally && this.tokens[i].text !== "\n") {
                        this.addLineBreak();
                    }

                    // Find the argument end token.
                    let startIndex = i;
                    while (this.tokens[i].type != Token.EOF && this.tokens[i].type != ANTLRv4Lexer.END_ACTION) {
                        ++i;
                    }

                    // Add a new range for the action code.
                    this.addRaw(startIndex, i - 1);
                    if (inCatchFinally && this.tokens[i - 1].text !== "\n") {
                        this.addLineBreak();
                    }
                    this.add(i);

                    if (!inRule) {
                        inNamedAction = false;
                        coalesceWhitespaces = false;
                        this.lineBreakPending = true;
                    }
                    inCatchFinally = false;

                    break;
                }

                case ANTLRv4Lexer.BLOCK_COMMENT:
                case ANTLRv4Lexer.DOC_COMMENT:
                case ANTLRv4Lexer.LINE_COMMENT: {
                    var text: string | undefined;
                    if (token.type != ANTLRv4Lexer.DOC_COMMENT) {
                        text = token.text!;
                        if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                            text = text.substr(2, text.length - 2).trim();
                        } else {
                            text = text.substr(2, text.length - 4).trim();
                        }
                    }

                    if (this.formattingDisabled && text === "antlr-format on") {
                        this.formattingDisabled = false;
                        this.addRaw(rangeStart, i - 1);
                    }

                    // If this comment is at the beginning of a line at top level with no
                    // comment on the previous line then make sure we have the requested number
                    // of empty lines in the code.
                    if (this.currentIndentation == 0
                        && this.lastEntryIs(InsertMarker.LineBreak)
                        && !this.entryIs(this.tokenList.length - 2, InsertMarker.Comment)) {
                        this.ensureMinEmptyLines();
                    } else if (!this.lastEntryIs(InsertMarker.Whitespace)) {
                        this.addSpace();
                    }

                    this.add(i);
                    if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                        //this.lineBreakPending = true;
                    } else {
                        this.addSpace();
                    }

                    if (text === "antlr-format off") {
                        this.lineBreakPending = false;
                        this.formattingDisabled = true;
                        rangeStart = i + 1; // The comment has already been added.
                    }

                    break;
                }

                case ANTLRv4Lexer.ASSIGN:
                case ANTLRv4Lexer.PLUS_ASSIGN: {
                    if (this.options.spaceBeforeAssignmentOperators) {
                        if (!this.lastEntryIs(InsertMarker.Whitespace)) {
                            this.addSpace();
                        }
                        this.add(i);
                        this.addSpace();
                    } else {
                        if (this.lastEntryIs(InsertMarker.Whitespace)) {
                            this.removeLastEntry();
                        }
                        this.add(i);
                    }
                    this.add(InsertMarker.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.AT: {
                    this.handlePendingLinebreak();
                    if (inRule) {
                        this.removeTrailingWhitespaces();
                        this.lineBreakPending = false;
                        if (this.options.ruleInternalsOnSingleLine) {
                            this.addSpace();
                        } else {
                            this.addLineBreak();
                            ++this.currentIndentation;
                            this.pushCurrentIndentation();
                            --this.currentIndentation;
                        }
                    } else {
                        inNamedAction = true;
                    }

                    this.add(i);
                    this.add(InsertMarker.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.COLON:
                    if (this.options.alignColon) {

                    } else {
                        this.removeTrailingWhitespaces();
                        this.add(i);
                        this.lineBreakPending = true;
                        ++this.currentIndentation;
                    }

                    let [containsAlts, singleLineLength] = this.getBlockInfo(i);
                    if (this.options.allowShortBlocksOnASingleLine && singleLineLength <= (this.options.columnLimit! / 2 + 3)) {
                        ++this.singleLineBlockNesting;
                    }
                    break;

                case ANTLRv4Lexer.COLONCOLON:
                    this.removeTrailingWhitespaces();
                    this.add(i);
                    this.add(InsertMarker.WhitespaceEraser);
                    break;

                case ANTLRv4Lexer.FRAGMENT:
                case ANTLRv4Lexer.PRIVATE:
                case ANTLRv4Lexer.PROTECTED:
                case ANTLRv4Lexer.PUBLIC:
                case ANTLRv4Lexer.TOKEN_REF:
                case ANTLRv4Lexer.RULE_REF: {
                    if (!inNamedAction && !inBraces) {
                        inRule = true;
                    }
                    // fall through
                }

                case ANTLRv4Lexer.IMPORT:
                case ANTLRv4Lexer.LEXER:
                case ANTLRv4Lexer.PARSER:
                case ANTLRv4Lexer.GRAMMAR:
                case ANTLRv4Lexer.OPTIONS:
                case ANTLRv4Lexer.TOKENS:
                case ANTLRv4Lexer.CHANNELS:
                case ANTLRv4Lexer.MODE: {
                    coalesceWhitespaces = true;
                    this.handlePendingLinebreak();
                    this.add(i);
                    if (!inLexerCommand) {
                        this.addSpace();
                    }
                    this.add(InsertMarker.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.PLUS:
                case ANTLRv4Lexer.QUESTION:
                case ANTLRv4Lexer.STAR: {
                    this.removeTrailingWhitespaces();
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.OR: {
                    if (this.singleLineBlockNesting == 0) {
                        this.removeTrailingWhitespaces();
                        this.lineBreakPending = false;
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                    } else {
                        this.addSpace();
                    }
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.LPAREN: {
                    if (this.singleLineBlockNesting > 0) {
                        // If we are already in single line mode add a nesting level.
                        ++this.singleLineBlockNesting;
                    } else {
                        // If not see if we should enter single line mode.
                        this.handlePendingLinebreak();
                        let [containsAlts, singleLineLength] = this.getBlockInfo(i);
                        if ((!containsAlts || this.options.allowShortBlocksOnASingleLine) && singleLineLength <= (this.options.columnLimit! / 2 + 3)) {
                            this.lineBreakPending = false;
                            ++this.singleLineBlockNesting;
                        } else {
                            // Multi-line block formatting starts here. Put blocks only on multiple lines if they contain alternatives.
                            if (this.options.breakBeforeParens) {
                                this.removeTrailingWhitespaces();
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                            } else {
                                this.removeTrailingWhitespaces();
                                this.addSpace();
                                if (containsAlts) {
                                    this.lineBreakPending = true;
                                }
                            }
                            ++this.currentIndentation;
                        }
                    }
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.RPAREN: {
                    if (this.singleLineBlockNesting > 0) {
                        --this.singleLineBlockNesting;
                        this.removeTrailingWhitespaces();
                        this.add(i);
                    } else {
                        this.removeTrailingWhitespaces();
                        this.addLineBreak();
                        if (this.currentIndentation > 0) {
                            --this.currentIndentation;
                        }
                        this.pushCurrentIndentation();
                        this.add(i);
                        this.addLineBreak();
                        break;

                    }
                    break;
                }

                case ANTLRv4Lexer.GT: {
                    this.removeTrailingWhitespaces();
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.RARROW: {
                    inLexerCommand = true;
                    if (!this.lastEntryIs(InsertMarker.Space)) {
                        this.addSpace();
                    }
                    this.add(i);
                    this.addSpace();
                    this.add(InsertMarker.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.BEGIN_ARGUMENT: {
                    if (this.formattingDisabled) {
                        break;
                    }

                    this.removeTrailingWhitespaces();
                    this.add(i++);

                    // Find the argument end token.
                    let startIndex = i;
                    while (this.tokens[i].type != Token.EOF && this.tokens[i].type != ANTLRv4Lexer.END_ARGUMENT) {
                        ++i;
                    }

                    // Add a new range for the action code.
                    this.addRaw(startIndex, i);
                    break;
                }

                case ANTLRv4Lexer.CATCH:
                case ANTLRv4Lexer.FINALLY: {
                    inCatchFinally = true;
                    this.removeTrailingWhitespaces();
                    this.addLineBreak();
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.RETURNS:
                case ANTLRv4Lexer.LOCALS: {
                    this.removeTrailingWhitespaces();
                    if (this.options.ruleInternalsOnSingleLine) {
                        this.addSpace();
                    } else {
                        this.addLineBreak();
                        ++this.currentIndentation;
                        this.pushCurrentIndentation();
                        --this.currentIndentation;
                    }
                    this.add(i);
                    break;
                }

                case Token.EOF:
                    // Ensure a line break at the end of the text.
                    this.removeTrailingWhitespaces();
                    this.addLineBreak();
                    break;

                default:
                    this.handlePendingLinebreak();
                    coalesceWhitespaces = true;
                    this.add(i);
                    break;
            }
        }

        let result = "";
        for (let index of this.tokenList) {
            switch (index) {
                case InsertMarker.LineBreak:
                    result += "\n";
                    break;
                case InsertMarker.Space:
                    result += " ";
                    break;
                case InsertMarker.Tab:
                    result += "\t";
                    break;
                case InsertMarker.WhitespaceEraser: // Ignore.
                    break;

                default:
                    if (index <= InsertMarker.Range) {
                        // Copy an entire block.
                        let rangeIndex = -(index - InsertMarker.Range);
                        let startIndex = this.ranges[rangeIndex][0];
                        let endIndex = this.ranges[rangeIndex][1];
                        let interval = Interval.of(this.tokens[startIndex].startIndex, this.tokens[endIndex].stopIndex);
                        result += this.tokens[0].inputStream!.getText(interval);
                    } else {
                        result += this.tokens[index].text;
                    }
                    break;
            }
        }
        return [result, range];
    }

    private options: FormattingOptions;
    private tokenList: InsertMarker[];
    private currentIndentation: number;
    private lineBreakPending: boolean; // Insert a line break before the next code token (if not there already).
    private formattingDisabled: boolean; // When true no formatting takes place.

    private currentLine: number;
    private currentColumn: number;

    // When a block has been determined to fit as a whole on a single line (relevant only if allowShortBlocksOnASingleLine is true),
    // this var directs linebreak handling.
    // Note: counting begins on the most outer block that can be formatted on a single line, which is not necessarily
    //       the rule itself.
    private singleLineBlockNesting: number;

    // A list of index pairs describing start and end of a token sequence in the original token stream.
    // This is mostly used to avoid having to place a large list of action tokens in the generated list.
    private ranges: [InsertMarker, InsertMarker][];
    private currentRangeIndex: InsertMarker; // When scanning a range this contains the start token index.
}
