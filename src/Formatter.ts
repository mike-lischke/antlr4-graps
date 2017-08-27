/*
 * This file is released under the MIT license.
 * Copyright (c) 2016, 2017, Mike Lischke
 *
 * See LICENSE file for more info.
 */

"use strict";

import { FormattingOptions, LexicalRange } from "../index";

import { Token } from "antlr4ts";
import { ANTLRv4Lexer } from "../parser/ANTLRv4Lexer";

enum InsertTokenType {
    // Positive values are indices into this.tokens.
    LineBreak = -2,
    Space = -3,
    Tab = -4,

    Whitespace = -100,
    Comment = -101,
    WhitespaceEraser = -102 // Marker for any comming whitespace to be ignored.
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
    private entryIs(index: number, type: InsertTokenType): boolean {
        if (index < 0 || index >= this.tokenList.length) {
            return false;
        }

        const entry = this.tokenList[index];
        switch (type) {
            case InsertTokenType.Whitespace:
                return entry == InsertTokenType.LineBreak || entry == InsertTokenType.Space || entry == InsertTokenType.Tab;

            case InsertTokenType.Comment: {
                if (entry < 0) {
                    return false;
                }
                const token = this.tokens[entry];
                return token.type == ANTLRv4Lexer.BLOCK_COMMENT || token.type == ANTLRv4Lexer.LINE_COMMENT
                    || token.type == ANTLRv4Lexer.DOC_COMMENT;
            }

            default: {
                if (entry < 0) {
                    return entry == type;
                }
                const token = this.tokens[entry];
                return token.type == type;
            }
        }
    }

    private lastEntryIs(type: InsertTokenType): boolean {
        return this.entryIs(this.tokenList.length - 1, type);
    }

    /**
     * Skips over all comments and whitespaces backwards and checks the value of the value after that.
     * @param type A token type to check for.
     */
    private lastCodeTokenIs(type: number): boolean {
        let i = this.tokenList.length - 1;
        while (i >= 0) {
            if (!this.entryIs(i, InsertTokenType.WhitespaceEraser)
                && !this.entryIs(i, InsertTokenType.Whitespace)
                && !this.entryIs(i, InsertTokenType.LineBreak)
                && !this.entryIs(i, InsertTokenType.Comment)) {
                break;
            }
            --i;
        }
        if (i < 0) {
            return false;
        }
        return this.tokens[this.tokenList[i]].type == type;
    }

    /**
     * Scan the token list backwards up to the last line break or any non-whitespace token, whichever comes first.
     * @return true if a line break came first.
     */
    private isFirstNonWhitespaceTokenOnLine(): boolean {
        let i = this.tokenList.length - 1;
        while (i >= 0) {
            if (this.entryIs(i, InsertTokenType.LineBreak)) {
                return true;
            }
            if (!this.entryIs(i, InsertTokenType.Whitespace)) {
                return false;
            }
            --i;
        }
        return true;
    }

    private removeLastEntry() {
        let lastEntry = this.tokenList[this.tokenList.length - 1];
        this.tokenList.pop();
        switch (lastEntry) {
            case InsertTokenType.WhitespaceEraser:
                break; // Ignore.
            case InsertTokenType.LineBreak:
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
        while (this.lastEntryIs(InsertTokenType.LineBreak)) {
            this.removeLastEntry();
        }
    }

    /**
     * Scans backwards and removes any whitespace up to the first non-whitespace.
     * @param tokenList The list to work on.
     */
    private removeTrailingWhitespaces() {
        while (this.lastEntryIs(InsertTokenType.Whitespace)) {
            this.removeLastEntry();
        }
    }

    private pushCurrentIndentation() {
        console.assert(this.currentColumn == 0, "Current column cannot be > 0 when setting new indentation");

        if (this.options.useTab) {
            this.tokenList.push(...Array(this.currentIndentation).fill(InsertTokenType.Tab));
        } else {
            this.tokenList.push(...Array(this.currentIndentation * this.options.tabWidth!).fill(InsertTokenType.Space));
        }
        this.currentColumn = this.currentIndentation * this.options.tabWidth!;
    }

    /**
     * Inserts the given type into the result list, but checks if the entry before `index` is a single line comment.
     * If that's the case we need special handling here.
     */
    private insert(index: number, type: InsertTokenType) {

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
            self.tokenList.splice(index, 0, type);
        }

        switch (type) {
            case InsertTokenType.WhitespaceEraser: { // Doesn't move current position.
                this.tokenList.splice(index, 0, type);
                break;
            }

            case InsertTokenType.LineBreak: {
                this.tokenList.splice(index, 0, type);
                ++this.currentLine;
                this.currentColumn = 0;
                break;
            }

            default: {
                var doDefault = true;

                var token: Token | undefined;
                if (type >= 0) {
                    token = this.tokens[type];
                    if (token.text!.indexOf("\n") > 0) {
                        // We come here if formatting is disabled, so we need to handle linebreaks in whitespaces
                        // here before going to the line comment special handling.
                        this.tokenList.splice(index, 0, type);
                        ++this.currentLine;
                        this.currentColumn = 0;
                        break;
                    }
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
                            this.tokenList.push(InsertTokenType.LineBreak);
                            this.pushCurrentIndentation();
                            this.tokenList.push(type);

                            if (token.type == ANTLRv4Lexer.BLOCK_COMMENT) {
                                insertBlock(token);
                            } else {
                                this.currentColumn += insertLength;
                            }
                        } else {
                            // Not a comment that should be added, so move the new entry *before* the line comment.
                            this.tokenList.splice(this.tokenList.length - 1, 0, type);
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
                            insertBlock(this.tokens[type]);
                            doDefault = false;
                            break;
                        }
                    }
                }

                if (doDefault) {
                    this.tokenList.splice(index, 0, type);
                    this.currentColumn += insertLength;
                }

                break;
            }
        }
    }

    private add(type: InsertTokenType) {
        this.insert(this.tokenList.length, type);
    }

    private addSpace() {
        if (!this.lastEntryIs(InsertTokenType.Space)) {
            this.insert(this.tokenList.length, InsertTokenType.Space);
        }
    }

    private addLineBreak() {
        this.lineBreakPending = false;
        if (this.singleLineBlockNesting == 0) {
            this.insert(this.tokenList.length, InsertTokenType.LineBreak);
        }
    }

    /**
     * Goes backward in the already created token list until the first non-whitespace and non-comment
     * token is found and inserts the given type after that.
     * @param type The type to insert.
     * @param whitSpace If true insert also a space (before the inserted type).
     */
    private insertAfterLastFullToken(type: InsertTokenType, withSpace: boolean) {
        let i = this.tokenList.length - 1;
        while (i > 0) {
            if (!this.entryIs(i, InsertTokenType.Whitespace) && !this.entryIs(i, InsertTokenType.Comment)) {
                break;
            }
            --i;
        }

        if (i > 0) {
            let newEntries = [type];
            if (withSpace) {
                newEntries.unshift(InsertTokenType.Space);
            }
            this.tokenList.splice(i + 1, 0, ...newEntries);
        }
    }

    private ensureMinEmptyLines(): void {
        if (this.options.minEmptyLines! > 0) {
            let lineBreakCount = this.options.minEmptyLines! + 1;
            for (let i = this.tokenList.length - 1; i > 0 && lineBreakCount > 0; --i) {
                if (this.entryIs(i, InsertTokenType.LineBreak)) {
                    --lineBreakCount;
                } else {
                    break;
                }
            }
            this.tokenList.push(...Array(lineBreakCount).fill(InsertTokenType.LineBreak));
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
        this.tokenList = [];
        this.currentIndentation = 0;
        this.setDefaultOptions();
        this.options = Object.assign(this.options, options); // Overwrite default values with passed in values.

        let coalesceWhitespaces = false; // Set in situations where we don't want more than a single space char.
        let inBraces = false; // Set between {} (e.g. in options and tokens blocks).
        let inRule = false;   // Set when we are processing a lexer or parser rule.
        let inNamedAction = false;
        let inLexerCommand = false;
        let formattingDisabled = false;

        // Position info of the target text.
        this.currentColumn = 0;
        this.currentLine = 0;

        // Outside of braces is the grammar introducer command the only one ending in a semicolon.
        // We must not format that like rules, so we add a special state only for this entry.
        let introducerDone = false;

        for (let i = 0; i < this.tokens.length; ++i) {
            let token = this.tokens[i];

            if (formattingDisabled) {
                if (token.type == ANTLRv4Lexer.LINE_COMMENT || token.type == ANTLRv4Lexer.BLOCK_COMMENT) {
                    // See if we can switch formatting on again.
                    let text = token.text!;
                    if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                        text = text.substr(1, text.length - 2);
                    } else {
                        text = text.substr(2, text.length - 4);
                    }
                    if (text.trim() == "antlr-format on") {
                        formattingDisabled = false;
                    }
                }

                if (formattingDisabled) {
                    this.add(i);
                    continue;
                }
            }

            // If no whitespace is coming up we don't need the eraser marker anymore.
            if (token.type != ANTLRv4Lexer.WS && this.lastEntryIs(InsertTokenType.WhitespaceEraser)) {
                this.tokenList.pop();
            }

            switch (token.type) {
                case ANTLRv4Lexer.WS: {
                    if (i == 0) {
                        // Ignore leading whitespaces at the beginning of the grammar.
                        break;
                    }
                    if (this.lastEntryIs(InsertTokenType.WhitespaceEraser)) {
                        // And ignore these incomming whitespaces if there is an eraser marker.
                        this.tokenList.pop();
                        break;
                    }

                    // Analyze whitespaces, we can have a mix of tab/space and line breaks here.
                    let text = token.text!.replace("\r\n", "\n");
                    if (coalesceWhitespaces || (this.singleLineBlockNesting > 0) || text.indexOf("\n") < 0) {
                        // Spaces only. Cannot be at the start of a line, so simply convert them to a single space
                        // unless we need to align following text.
                        if (!this.lastEntryIs(InsertTokenType.Whitespace)) {
                            this.addSpace();
                        }
                        break;
                    }

                    let parts = text.split("\n");

                    // Take into account any linebreaks that are already in the pipeline.
                    if (this.lineBreakPending) {
                        this.lineBreakPending = false;
                    }
                    let j = this.tokenList.length - 1;
                    while (j >= 0) {
                        if (this.entryIs(j, InsertTokenType.LineBreak)) {
                            parts.unshift("");
                        } else {
                            break;
                        }
                        --j;
                    }

                    this.removeTrailingWhitespaces();

                    let breakCount = parts.length - 1 <= this.options.maxEmptyLinesToKeep! ? parts.length - 1 : this.options.maxEmptyLinesToKeep! + 1;
                    this.tokenList.push(...Array(breakCount).fill(InsertTokenType.LineBreak));
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
                        this.lineBreakPending = true;
                    }

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
                    this.handlePendingLinebreak();
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.ACTION_CONTENT: {
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.END_ACTION: {
                    if (!inRule) {
                        inNamedAction = false;
                        coalesceWhitespaces = false;
                        this.lineBreakPending = true;
                    }
                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.BLOCK_COMMENT:
                case ANTLRv4Lexer.DOC_COMMENT:
                case ANTLRv4Lexer.LINE_COMMENT: {
                    // If this comment is at the beginning of a line at top level with no
                    // comment on the previous line then make sure we have the requested number
                    // of empty lines in the code.
                    if (this.currentIndentation == 0
                        && this.lastEntryIs(InsertTokenType.LineBreak)
                        && !this.entryIs(this.tokenList.length - 2, InsertTokenType.Comment)) {
                        this.ensureMinEmptyLines();
                    }

                    this.add(i);
                    if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                        this.lineBreakPending = true;
                    } else {
                        this.addSpace();
                    }

                    // Finally check if formatting should be switched off.
                    if (token.type != ANTLRv4Lexer.DOC_COMMENT) {
                        let text = token.text!;
                        if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                            text = text.substr(2, text.length - 2);
                        } else {
                            text = text.substr(2, text.length - 4);
                        }
                        if (text.trim() == "antlr-format off") {
                            this.lineBreakPending = false;
                            this.add(InsertTokenType.WhitespaceEraser);
                            formattingDisabled = true;
                        }
                    }

                    break;
                }

                case ANTLRv4Lexer.ASSIGN:
                case ANTLRv4Lexer.PLUS_ASSIGN: {
                    if (this.options.spaceBeforeAssignmentOperators) {
                        if (!this.lastEntryIs(InsertTokenType.Whitespace)) {
                            this.addSpace();
                        }
                        this.add(i);
                        this.addSpace();
                    } else {
                        if (this.lastEntryIs(InsertTokenType.Whitespace)) {
                            this.removeLastEntry();
                        }
                        this.add(i);
                    }
                    this.add(InsertTokenType.WhitespaceEraser);
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
                    this.add(InsertTokenType.WhitespaceEraser);
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
                    this.add(InsertTokenType.WhitespaceEraser);
                    break;

                case ANTLRv4Lexer.FRAGMENT:
                case ANTLRv4Lexer.PRIVATE:
                case ANTLRv4Lexer.PROTECTED:
                case ANTLRv4Lexer.PUBLIC:
                case ANTLRv4Lexer.TOKEN_REF:
                case ANTLRv4Lexer.RULE_REF: {
                    if (!inNamedAction) {
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
                    this.add(InsertTokenType.WhitespaceEraser);
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
                    if (!this.lastEntryIs(InsertTokenType.Space)) {
                        this.addSpace();
                    }
                    this.add(i);
                    this.addSpace();
                    this.add(InsertTokenType.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.BEGIN_ARGUMENT: {
                    this.removeTrailingWhitespaces();
                    // fall through
                }

                case ANTLRv4Lexer.ARGUMENT_CONTENT:
                case ANTLRv4Lexer.END_ARGUMENT: {
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

                case ANTLRv4Lexer.CATCH:
                case ANTLRv4Lexer.FINALLY: {
                    this.removeTrailingWhitespaces();
                    this.addLineBreak();
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
                case InsertTokenType.LineBreak:
                    result += "\n";
                    break;
                case InsertTokenType.Space:
                    result += " ";
                    break;
                case InsertTokenType.Tab:
                    result += "\t";
                    break;
                case InsertTokenType.WhitespaceEraser: // Ignore.
                    break;

                default:
                    result += this.tokens[index].text;
                    break;
            }
        }
        return [result, range];
    }

    private options: FormattingOptions;
    private tokenList: number[];
    private currentIndentation: number;
    private lineBreakPending = false; // Insert a line break before the next code token (if not there already).

    private currentLine: number;
    private currentColumn: number;

    // When a block has been determined to fit as a whole on a single line (relevant only if allowShortBlocksOnASingleLine is true),
    // this var directs linebreak handling.
    // Note: counting begins on the most outer block that can be formatted on a single line, which is not necessarily
    //       the rule itself.
    private singleLineBlockNesting = 0;
}
