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

// Insert markers are what the output pipeline (see below) is made of (if not direct token indices).
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
    Error = -103,

    // Block markers.
    Range = -100000,           // Indirect index into the range list.
    Alignment = -200000,       // Indirect index into the alignment groups list.
    WhitespaceBlock = -300000, // Indirect index into the whitespace list.
}

function isRangeBlock(marker: InsertMarker): boolean {
    return (marker <= InsertMarker.Range) && (marker > InsertMarker.Alignment);
};
function isAlignmentBlock(marker: InsertMarker): boolean {
    return (marker <= InsertMarker.Alignment) && (marker > InsertMarker.WhitespaceBlock);
};
function isWhitespaceBlock(marker: InsertMarker): boolean {
    return (marker <= InsertMarker.WhitespaceBlock);
};

// Enum used to address a specific alignment status in the alignment map.
enum AlignmentType {
    Colon,
    FirstToken,
    Label,
    LexerCommand,
    Action,
    TrailingComment,
    Trailers // Align all of label, action, trailing comment and lexer command (whatever comes first).
}

// Holds line number and group index for a specific alignment. For each alignment type there's an own
// status, to allow multiple alignments per line.
interface AlignmentStatus {
    lastLine: number; // The line number of the last alignment entry in the current group (if there's one currently).
    groupIndex: number; // Index into the alignment groups list if a group is active.
}

export class GrammarFormatter {
    constructor(private tokens: Token[]) { }

    /**
     * This is the main formatting routine.
     *
     * @param options
     * @param range
     */
    public formatGrammar(options: FormattingOptions, range: LexicalRange): [string, LexicalRange] {
        this.setDefaultOptions();
        this.options = Object.assign(this.options, options); // Overwrite default values with passed in values.

        this.outputPipeline = [];
        this.currentIndentation = 0;
        this.singleLineBlockNesting = 0

        this.ranges = [];
        this.currentRangeIndex = 0;
        this.rangeStart = -1;

        this.alignments.clear();
        this.alignmentGroups = [];
        this.whitespaceList = [];

        // Position info of the target text.
        this.currentColumn = 0;
        this.currentLine = 0;
        this.formattingDisabled = false;

        let coalesceWhitespaces = false; // Set in situations where we don't want multiple consecutive whitespaces.
        let inBraces = false; // Set between {} (e.g. in options and action blocks).
        let inRule = false;   // Set when we are processing a lexer or parser rule.
        let inNamedAction = false; // Ditto for a named action.
        let inLexerCommand = false; // Ditto for a lexer command (the part starting with ->).
        let inCatchFinally = false; // Ditto for catch/finally blocks.

        let inSingleLineRule = false; // Set when an entire rule is placed on a single line.
        let minLineInsertionPending = false; // Set when the min line setting must be enforced after next line break.

        for (let i = 0; i < this.tokens.length; ++i) {
            let token = this.tokens[i];

            // If no whitespace is coming up we don't need the eraser marker anymore.
            if (token.type != ANTLRv4Lexer.WS && this.lastEntryIs(InsertMarker.WhitespaceEraser)) {
                this.outputPipeline.pop();
            }

            switch (token.type) {
                case ANTLRv4Lexer.WS: {
                    if (i == 0 || this.formattingDisabled) {
                        // Ignore leading whitespaces at the beginning of the grammar.
                        break;
                    }

                    let nextType = this.tokens[i + 1].type;
                    let localCommentAhead = (nextType == ANTLRv4Lexer.LINE_COMMENT
                        || nextType == ANTLRv4Lexer.BLOCK_COMMENT || nextType == ANTLRv4Lexer.DOC_COMMENT);

                    if (this.lastEntryIs(InsertMarker.WhitespaceEraser)) {
                        // And ignore these incomming whitespaces if there is an eraser marker
                        // (unless comments after a line break follow, which we want to stay on their line).
                        this.outputPipeline.pop();

                        if (!localCommentAhead) {
                            break;
                        }
                    }

                    // Analyze whitespaces, we can have a mix of tab/space and line breaks here.
                    let text = token.text!.replace("\r\n", "\n");
                    let hasLineBreaks = text.indexOf("\n") >= 0;
                    if (!localCommentAhead || !hasLineBreaks ) {
                        if (!hasLineBreaks || coalesceWhitespaces || this.singleLineBlockNesting > 0) {
                            if (!this.lastEntryIs(InsertMarker.Whitespace)) {
                                this.addSpace();
                            }
                            break;
                        }
                    }

                    let parts = text.split("\n");
                    let breakCount = 0;

                    // Limit the number of line breaks before a comment right after a left parenthesis.
                    if (localCommentAhead && this.lastCodeTokenIs(ANTLRv4Lexer.LPAREN)
                        && !this.options.keepEmptyLinesAtTheStartOfBlocks) {
                        breakCount = 1;
                    } else {
                        // Take into account any linebreaks that are already in the pipeline.
                        let j = this.outputPipeline.length - 1;
                        while (j >= 0) {
                            if (this.entryIs(j, InsertMarker.LineBreak)) {
                                ++breakCount;
                            } else {
                                break;
                            }
                            --j;
                        }

                        breakCount = Math.max(breakCount, parts.length - 1);
                        breakCount = Math.min(breakCount, this.options.maxEmptyLinesToKeep! + 1);
                    }
                    this.removeTrailingWhitespaces();

                    this.outputPipeline.push(...Array(breakCount).fill(InsertMarker.LineBreak));
                    this.currentLine += breakCount;
                    this.currentColumn = 0;

                    if (minLineInsertionPending) {
                        minLineInsertionPending = false;
                        this.ensureMinEmptyLines();
                    }
                    this.pushCurrentIndentation();

                    break;
                }

                case ANTLRv4Lexer.SEMI: {
                    this.removeTrailingWhitespaces();

                    // Single line mode here can be caused by 2 situations:
                    // single line block from the last alt or single line rule.
                    // In the first case we have to end single line mode now, otherwise
                    // after the alignment handling.
                    if (!inSingleLineRule) {
                        this.singleLineBlockNesting = 0;
                    }

                    // Even if the rule is on a single line we have to check for semicolon placement,
                    // because in case of a hanging colon only the body of the rule is on a single line,
                    // while name and semicolon are placed on own lines.
                    let canAlignSemicolon = !inSingleLineRule || this.options.alignColons == "hanging";
                    if (canAlignSemicolon && !inBraces && inRule) {
                        switch (this.options.alignSemicolons) {
                            case "none":
                                this.add(i);
                                break;
                            case "ownLine": {
                                let forceNewLine = !this.options.singleLineOverrulesHangingColon
                                    && this.options.alignColons == "hanging";
                                this.addLineBreak(forceNewLine);
                                break;
                            }
                            case "hanging":
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                                break;
                        }

                        this.add(i);
                    } else {
                        this.add(i);
                    }

                    if (!inBraces && this.currentIndentation > 0) {
                        --this.currentIndentation;
                    }

                    // Now we can end single line mode in any case (if not done yet above).
                    this.singleLineBlockNesting = 0;
                    inSingleLineRule = false;

                    if (this.currentIndentation == 0) {
                        minLineInsertionPending = true;
                    } else {
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                    }

                    coalesceWhitespaces = false;
                    inLexerCommand = false;
                    if (!inBraces) {
                        inRule = false;
                    }
                    break;
                }

                case ANTLRv4Lexer.LBRACE: {
                    if (this.singleLineBlockNesting == 0 && this.options.breakBeforeBraces) {
                        this.removeTrailingWhitespaces();
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                        this.add(i);
                    } else {
                        this.removeTrailingWhitespaces();
                        this.addSpace();
                        this.add(i);
                    }

                    ++this.currentIndentation;
                    inBraces = true;

                    if (!this.nonBreakingTrailerAhead(i)) {
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                    }

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

                    minLineInsertionPending = this.currentIndentation == 0;

                    inBraces = false;
                    coalesceWhitespaces = false;
                    inRule = false;
                    break;
                }

                case ANTLRv4Lexer.BEGIN_ACTION: {
                    if (this.formattingDisabled) {
                        break;
                    }

                    if (this.options.alignTrailers) {
                        this.addAlignmentEntry(AlignmentType.Trailers);
                    } else if (this.options.alignActions) {
                        this.addAlignmentEntry(AlignmentType.Action);
                    }

                    this.add(i++);
                    if (inCatchFinally && this.tokens[i].text !== "\n") {
                        this.addLineBreak();
                    }

                    // Find the action end token.
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

                    minLineInsertionPending = this.currentIndentation == 0;
                    if (!inRule) {
                        inNamedAction = false;
                        coalesceWhitespaces = false;
                    }
                    inCatchFinally = false;

                    break;
                }

                case ANTLRv4Lexer.LINE_COMMENT:
                case ANTLRv4Lexer.BLOCK_COMMENT: {
                    this.processFormattingCommands(i);
                    // fall through
                }

                case ANTLRv4Lexer.DOC_COMMENT: {
                    // If this comment is the first non-whitespace entry on the current line
                    // some extra processing is required.
                    let index = this.outputPipeline.length;
                    while (--index > 0) {
                        if (this.outputPipeline[index] != InsertMarker.Space
                            && this.outputPipeline[index] != InsertMarker.Tab) {
                            break;
                        }
                    }

                    if (index > 0 && this.outputPipeline[index] == InsertMarker.LineBreak) {
                        /*// Comment starts the line (or even entirely is the line).
                        // See if we are directly after a block start or a comment line,
                        // in which case we don't do additional processing.
                        let afterBlockStart = this.entryIs(index - 1, ANTLRv4Lexer.LBRACE)
                            || this.entryIs(index - 1, ANTLRv4Lexer.LPAREN);
                        let afterCommentLine = false;
                        if (!afterBlockStart) {
                            // Scan back to previous line break.
                            while (--index > 0 && !this.entryIs(index, InsertMarker.LineBreak)) { }
                            if (index > 0) {
                                // Scan forward to first non-whitespace entry or a line break.
                                while (++index < this.outputPipeline.length) {
                                    if (this.entryIs(index, InsertMarker.Comment)) {
                                        afterCommentLine = true;
                                        break;
                                    }
                                    if (this.entryIs(index, InsertMarker.LineBreak)
                                        || !this.entryIs(index, InsertMarker.Whitespace)) {
                                        break;
                                    }
                                }
                            }
                        }

                        if (!afterBlockStart && !afterCommentLine) {
                            while (this.lastEntryIs(InsertMarker.Space) || this.lastEntryIs(InsertMarker.Tab)) {
                                this.removeLastEntry();
                            }
                            this.ensureMinEmptyLines();
                            this.pushCurrentIndentation();
                        }*/
                    } else if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                        // There's something before the comment on the current line.
                        // Trigger normal alignment handling then.
                        if (this.options.alignTrailers) {
                            this.addAlignmentEntry(AlignmentType.Trailers);
                        } else if (this.options.alignTrailingComments) {
                            this.addAlignmentEntry(AlignmentType.TrailingComment);
                        }
                    }

                    this.add(i);
                    if (token.type == ANTLRv4Lexer.LINE_COMMENT) {
                        if (this.currentIndentation > 0) {
                            this.addLineBreak();
                            this.pushCurrentIndentation();
                        }
                    } else {
                        this.addSpace();
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
                    if (inRule) {
                        this.removeTrailingWhitespaces();
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

                case ANTLRv4Lexer.COLON: {
                    ++this.currentIndentation;

                    let [containsAlts, singleLineLength] = this.getBlockInfo(i, new Set([ANTLRv4Lexer.SEMI]));
                    singleLineLength += this.currentColumn;
                    if (this.options.allowShortRulesOnASingleLine && singleLineLength <= (2 * this.options.columnLimit! / 3)) {
                        ++this.singleLineBlockNesting;
                        inSingleLineRule = true;
                    }

                    switch (this.options.alignColons) {
                        case "hanging": {
                            this.removeTrailingWhitespaces();

                            let forceNewLine = !this.options.singleLineOverrulesHangingColon;
                            this.addLineBreak(forceNewLine);
                            this.pushCurrentIndentation(forceNewLine);
                            this.add(i);
                            this.addSpace();
                            break;
                        }
                        case "none": {
                            this.removeTrailingWhitespaces();
                            this.add(i);
                            if (!this.nonBreakingTrailerAhead(i)) {
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                            } else {
                                this.addSpace();
                            }
                            break;
                        }
                        case "trailing": {
                            this.removeTrailingWhitespaces();
                            if (this.singleLineBlockNesting > 0) {
                                this.addAlignmentEntry(AlignmentType.Colon);
                                this.add(InsertMarker.WhitespaceEraser);
                            }
                            this.add(i);
                            if (!this.nonBreakingTrailerAhead(i)) {
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                            } else {
                                this.addSpace();
                            }
                            break;
                        }
                    }

                    // Aligning the first token only makes sense if the entire rule is on a single line.
                    if (this.options.alignFirstTokens && this.singleLineBlockNesting > 0) {
                        this.addAlignmentEntry(AlignmentType.FirstToken);
                        this.add(InsertMarker.WhitespaceEraser);
                    }

                    break;
                }

                case ANTLRv4Lexer.COLONCOLON:
                    this.removeTrailingWhitespaces();
                    this.add(i);
                    this.add(InsertMarker.WhitespaceEraser);
                    break;

                case ANTLRv4Lexer.IMPORT:
                case ANTLRv4Lexer.LEXER:
                case ANTLRv4Lexer.PARSER:
                case ANTLRv4Lexer.GRAMMAR:
                case ANTLRv4Lexer.MODE: {
                    if (!inNamedAction && !inRule) {
                        // We increase the current indentation here only to have an easier time
                        // when handling the ending semicolon. Otherwise we would have to add
                        // extra checks to know which command the semicolon ends.
                        ++this.currentIndentation;

                        coalesceWhitespaces = true;
                        inRule = true;
                    }
                    this.add(i);
                    break;
                }

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

                case ANTLRv4Lexer.OPTIONS:
                case ANTLRv4Lexer.TOKENS:
                case ANTLRv4Lexer.CHANNELS: {
                    coalesceWhitespaces = true;
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
                    // Starts a new alt. If we are in the first single line nesting level
                    // (not to be confused with block nesting, we can have the first single line block
                    // at, say, block nesting 10), we have to end the current single line block
                    // (which is the previous alt) and see if we can start a new one.
                    if (this.singleLineBlockNesting > 1) {
                        this.addSpace();
                    } else {
                        if (!inSingleLineRule) {
                            // If we are in a single line rule block it means we are not ending a
                            // single line alt block.
                            this.singleLineBlockNesting = 0;

                            this.removeTrailingWhitespaces();
                            this.addLineBreak();
                            this.pushCurrentIndentation();

                            let [containsAlts, singleLineLength] = this.getBlockInfo(i,
                                new Set([ANTLRv4Lexer.OR, ANTLRv4Lexer.SEMI]));

                            // See if we should enter single line mode.
                            if ((!containsAlts || this.options.allowShortBlocksOnASingleLine)
                                && singleLineLength <= (this.options.columnLimit! / 2 + 3)) {
                                ++this.singleLineBlockNesting;
                            }
                        }
                    }

                    this.add(i);
                    break;
                }

                case ANTLRv4Lexer.LPAREN: {
                    if (inLexerCommand) {
                        this.add(i);
                        break;
                    }

                    if (this.singleLineBlockNesting > 0) {
                        // If we are already in single line mode add a nesting level.
                        // It's impossible to have a multi line block within a single line block.
                        // The other way around it's well possible, though.
                        // See a few lines below why we increase by 2.
                        this.singleLineBlockNesting += 2;
                        ++this.currentIndentation;
                        this.add(i);
                    } else {
                        // First check if we can put the entire block on a single line (if the block option is set).
                        let [containsAlts, singleLineLength] = this.getBlockInfo(i, new Set([ANTLRv4Lexer.RPAREN]));
                        singleLineLength += this.currentColumn;

                        if (this.options.allowShortBlocksOnASingleLine
                            && singleLineLength <= (2 * this.options.columnLimit! / 3)) {
                            // Increase by 2: one for the block and one for the first alt.
                            // We increase for the alt even if there's no content or only a single alt.
                            // Doing that simplifies handling when closing the block.
                            this.singleLineBlockNesting += 2;
                        }

                        if (this.singleLineBlockNesting == 0) {
                            if (this.options.breakBeforeParens) {
                                this.removeTrailingWhitespaces();
                                this.addLineBreak();
                                this.pushCurrentIndentation();
                            }

                            this.add(i);
                            ++this.currentIndentation;

                            this.addLineBreak();
                            this.pushCurrentIndentation();

                            // If the entire block is too long, see if the first alt would fit on a single line.
                            [containsAlts, singleLineLength] = this.getBlockInfo(i,
                                new Set([ANTLRv4Lexer.OR, ANTLRv4Lexer.RPAREN]));
                            if (singleLineLength <= (this.options.columnLimit! / 2 + 3)) {
                                ++this.singleLineBlockNesting;
                            }
                        } else {
                            this.add(i);
                            ++this.currentIndentation;
                        }

                    }

                    break;
                }

                case ANTLRv4Lexer.RPAREN: {
                    if (inLexerCommand) {
                        this.add(i);
                        break;
                    }

                    if (this.singleLineBlockNesting > 0) {
                        // If we are in single line mode when we end an alt it means
                        // the nesting counter was increased for it. Hence we can count down here.
                        --this.singleLineBlockNesting;
                    }

                    if (this.currentIndentation > 0) {
                        --this.currentIndentation;
                    }

                    this.removeTrailingWhitespaces();

                    // If the single line counter is still > 0 it means the entire block is
                    // to be formatted on a single line.
                    if (this.singleLineBlockNesting > 0) {
                        this.add(i);
                    } else {
                        this.addLineBreak();
                        this.pushCurrentIndentation();
                        this.add(i);

                        if (!this.nonBreakingTrailerAhead(i)) {
                            //this.addLineBreak();
                        }
                    }

                    if (this.singleLineBlockNesting > 0) {
                        // Now decrease single line block counter for the closing parenthesis too.
                        --this.singleLineBlockNesting;
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
                    if (this.options.alignTrailers) {
                        this.addAlignmentEntry(AlignmentType.Trailers);
                    } else if (this.options.alignLexerCommands) {
                        this.addAlignmentEntry(AlignmentType.LexerCommand);
                    } else {
                        if (!this.lastEntryIs(InsertMarker.Space)) {
                            this.addSpace();
                        }
                    }
                    this.add(i);
                    this.addSpace();
                    this.add(InsertMarker.WhitespaceEraser);
                    break;
                }

                case ANTLRv4Lexer.COMMA: {
                    this.removeTrailingWhitespaces();
                    this.add(i);
                    if (inBraces) {
                        coalesceWhitespaces = false; // For tokens block.
                        if (!this.nonBreakingTrailerAhead(i)) {
                            this.addLineBreak();
                            this.pushCurrentIndentation();
                        }
                    } else {
                        this.addSpace();
                    }
                    break;
                }

                case ANTLRv4Lexer.POUND: {
                    // Starting a label. They are not trailing per se, but we treat them so
                    // if not in single line mode, as they look similar like trailing comments.
                    let willUseAlignment = false;
                    if (this.singleLineBlockNesting == 0) {
                        if (this.options.alignTrailers) {
                            willUseAlignment = true,
                            this.addAlignmentEntry(AlignmentType.Trailers);
                        } else if (this.options.alignLabels) {
                            willUseAlignment = true,
                            this.addAlignmentEntry(AlignmentType.Label);
                        }
                    }

                    if (!willUseAlignment && !this.lastEntryIs(InsertMarker.Space)) {
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
                    coalesceWhitespaces = true;
                    this.add(i);
                    break;
            }
        }

        // Output phase: compose all collected entries into a result string.
        // Start with computing all alignments.
        this.computeAlignments();

        let result = "";
        let pendingLineComment = -1;
        let hadErrorOnLine = false;
        for (let entry of this.outputPipeline) {
            switch (entry) {
                case InsertMarker.LineBreak:
                    if (pendingLineComment > 0) {
                        let lastChar = result[result.length - 1];
                        if (lastChar != " " && lastChar != "\t" && lastChar != "\n") {
                            result += " ";
                        }
                        result += this.tokens[pendingLineComment].text;
                        pendingLineComment = -1;
                    }
                    result += "\n";
                    hadErrorOnLine = false;
                    break;
                case InsertMarker.Space:
                    result += " ";
                    break;
                case InsertMarker.Tab:
                    result += "\t";
                    break;
                case InsertMarker.WhitespaceEraser: // Ignore.
                    break;
                case InsertMarker.Error:
                    if (!hadErrorOnLine) { // Don't output more than one error per line.
                        result += "<<Unexpected input or wrong formatter command>>";
                        hadErrorOnLine = true;
                    }
                    break;
                default:
                    if (entry < 0) {
                        // One of the block markers. Alignment blocks are removed at this point and
                        // replaced by whitespace indices.
                        if (isWhitespaceBlock(entry)) {
                            result += this.whitespaceList[-(entry - InsertMarker.WhitespaceBlock)];
                        } else if (isRangeBlock(entry)) {
                            // Copy an entire block.
                            let rangeIndex = -(entry - InsertMarker.Range);
                            let startIndex = this.ranges[rangeIndex][0];
                            let endIndex = this.ranges[rangeIndex][1];
                            let interval = Interval.of(this.tokens[startIndex].startIndex, this.tokens[endIndex].stopIndex);
                            result += this.tokens[0].inputStream!.getText(interval);
                        }
                    } else {
                        if (this.tokens[entry].type == ANTLRv4Lexer.LINE_COMMENT) {
                            // Ensure we don't print out a line comment before anything
                            // but a line break.
                            pendingLineComment = entry;
                            break;
                        }
                        result += this.tokens[entry].text;
                    }
                    break;
            }
        }
        return [result, range];
    }

    private setDefaultOptions() {
        this.options = {};
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

        this.options.alignColons = "none";
        this.options.allowShortRulesOnASingleLine = true;
        this.options.alignSemicolons = "ownLine";
        this.options.singleLineOverrulesHangingColon = true;
        this.options.breakBeforeParens = false;
        this.options.ruleInternalsOnSingleLine = false;
        this.options.minEmptyLines = 0;
        this.options.groupedAlignments = true;
        this.options.alignFirstTokens = false;
        this.options.alignLexerCommands = false;
        this.options.alignActions = false;
        this.options.alignTrailers = false;
    }

    /** Is the value at the given index in the token list of the given type? */
    private entryIs(index: number, marker: InsertMarker): boolean {
        if (index < 0 || index >= this.outputPipeline.length) {
            return false;
        }

        const entry = this.outputPipeline[index];
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
        return this.entryIs(this.outputPipeline.length - 1, marker);
    }

    /**
     * Skips over all comments and whitespaces backwards and checks the value of the value after that.
     * @param type A token type to check for.
     */
    private lastCodeTokenIs(marker: InsertMarker): boolean {
        let i = this.outputPipeline.length - 1;
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
        return this.tokens[this.outputPipeline[i]].type == marker;
    }

    /**
     * Scan the token list backwards up to the last line break or any non-whitespace token, whichever comes first.
     * @return true if a line break came first.
     */
    private isFirstNonWhitespaceTokenOnLine(): boolean {
        let i = this.outputPipeline.length - 1;
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

        let lastEntry = this.outputPipeline[this.outputPipeline.length - 1];
        this.outputPipeline.pop();
        switch (lastEntry) {
            case InsertMarker.WhitespaceEraser:
                break; // Ignore.
            case InsertMarker.LineBreak:
                --this.currentLine;
                break;
            case InsertMarker.Tab: {
                let offset = this.currentColumn % this.options.tabWidth!;
                this.currentColumn -= (offset > 0 ? offset : this.options.tabWidth!);
                break;
            }

            default:
                --this.currentColumn;
                break;
        }
        console.assert(this.currentLine >= 0, "Current line can never be less than 0");
        console.assert(this.currentColumn >= 0, "Current column can never be less than 0");
    }

    /**
     * Scans backwards and removes line breaks up to the first non line break token.
     * @param outputPipeline The list to work on.
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
     * @param outputPipeline The list to work on.
     */
    private removeTrailingWhitespaces() {
        if (this.formattingDisabled) {
            return;
        }

        while (this.lastEntryIs(InsertMarker.Whitespace)) {
            this.removeLastEntry();
        }
    }

    private pushCurrentIndentation(force: boolean = false) {
        if (this.formattingDisabled || (!force && this.singleLineBlockNesting > 0)) {
            return;
        }

        if (this.currentColumn > 0) {
            this.outputPipeline.push(InsertMarker.Error);

        }

        if (this.options.useTab) {
            this.outputPipeline.push(...Array(this.currentIndentation).fill(InsertMarker.Tab));
        } else {
            this.outputPipeline.push(...Array(this.currentIndentation * this.options.indentWidth!).fill(InsertMarker.Space));
        }
        this.currentColumn = this.currentIndentation * this.options.indentWidth!;
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
            self.outputPipeline.splice(index, 0, marker);
        }

        switch (marker) {
            case InsertMarker.WhitespaceEraser: { // Doesn't move current position.
                this.outputPipeline.splice(index, 0, marker);
                return;
            }

            case InsertMarker.LineBreak: {
                this.outputPipeline.splice(index, 0, marker);
                ++this.currentLine;
                this.currentColumn = 0;
                return;
            }

            default: {
                var token: Token | undefined;
                if (marker >= 0) {
                    token = this.tokens[marker];
                }

                const insertLength = token ? token.stopIndex - token.startIndex + 1 : 1;
                if (token) {
                    switch (token.type) {
                        case ANTLRv4Lexer.BLOCK_COMMENT: {
                            insertBlock(token);
                            return;
                        }

                        case ANTLRv4Lexer.ACTION_CONTENT: { // Action content can contain line breaks.
                            insertBlock(this.tokens[marker]);
                            return
                        }
                    }
                }

                this.outputPipeline.splice(index, 0, marker);
                this.currentColumn += insertLength;

                break;
            }
        }
    }

    private add(marker: InsertMarker) {
        this.insert(this.outputPipeline.length, marker);
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
        this.outputPipeline.push(InsertMarker.Range - this.currentRangeIndex++);
    }

    private addSpace() {
        if (!this.lastEntryIs(InsertMarker.Space) && !this.lastEntryIs(ANTLRv4Lexer.LINE_COMMENT)) {
            this.insert(this.outputPipeline.length, InsertMarker.Space);
        }
    }

    private addLineBreak(force: boolean = false) {
        if (this.singleLineBlockNesting == 0 || force) {
            // If the current line ends with tabs/spaces, remove them first.
            while (this.lastEntryIs(InsertMarker.Space) || this.lastEntryIs(InsertMarker.Tab)) {
                this.removeLastEntry();
            }
            this.insert(this.outputPipeline.length, InsertMarker.LineBreak);
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
            for (let i = this.outputPipeline.length - 1; i > 0 && lineBreakCount > 0; --i) {
                if (this.entryIs(i, InsertMarker.LineBreak)) {
                    --lineBreakCount;
                } if (this.entryIs(i, InsertMarker.Whitespace)) {
                    continue;
                } else {
                    break;
                }
            }

            this.outputPipeline.push(...Array(lineBreakCount).fill(InsertMarker.LineBreak));
            this.currentLine += lineBreakCount;
            if (lineBreakCount > 0) {
                this.currentColumn = 0;
            }
        } else if (!this.lastEntryIs(InsertMarker.LineBreak)) {
            this.addLineBreak();
        }
    }

    /**
     * Starting from position i this methods scans forward in the input token list to determine
     * if the block contains alternatives and how long it would be (in characters) if the block would be
     * formatted on a single line. If there's a single line comment somewhere we cannot do such a simple formatting, however.
     *
     * @param i The position to start scanning from. Should point to either a colon or an opening parenthesis.
     */
    private getBlockInfo(i: number, stoppers: Set<number>): [boolean, number] {
        let containsAlts = false;
        let overallLength = 1;
        let nestingLevel = 0;
        let inSet = false;

        let token = this.tokens[i];
        if (token.type == ANTLRv4Lexer.COLON || token.type == ANTLRv4Lexer.OR) {
            ++overallLength; // One for the space after these two.
        }

        while (++i < this.tokens.length) {
            token = this.tokens[i];
            switch (token.type) {
                case ANTLRv4Lexer.WS: {
                    // Ignore whitespaces here. We pretend there is always a single space char
                    // between tokens and we will add them below (except for certain tokens).
                    break;
                }

                case ANTLRv4Lexer.LPAREN: {
                    ++nestingLevel;
                    ++overallLength;
                    break;
                }

                case ANTLRv4Lexer.RPAREN: {
                    // No need to add a space here (we have one from the previous token).
                    ++overallLength;

                    if (nestingLevel > 0) {
                        --nestingLevel;
                    } else {
                        // No check here if RPAREN is in the list of stoppers.
                        // If it is we return. If not and we got an RPAREN at nesting level 0
                        // we found an unbalanced block and return also.
                        return [containsAlts, overallLength];
                    }

                    break;
                }

                case ANTLRv4Lexer.SEMI: {
                    ++overallLength;
                    if (stoppers.has(ANTLRv4Lexer.SEMI)) {
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

                case ANTLRv4Lexer.LINE_COMMENT: {
                    // Single line comments cannot be formatted on a single line (they would hide what follows).
                    // Signal that by a large overall length.
                    return [containsAlts, 1e100];
                }

                case ANTLRv4Lexer.BLOCK_COMMENT:
                case ANTLRv4Lexer.DOC_COMMENT: {
                    // If the comment contains a linebreak we cannot format the block as single line.
                    if (token.text!.indexOf("\n") >= 0) {
                        return [containsAlts, 1e100];
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
                        return [containsAlts, 1e100];
                    } else {
                        ++overallLength;
                    }
                    break;
                }

                case ANTLRv4Lexer.OR: {
                    if (nestingLevel == 0) {
                        if (stoppers.has(ANTLRv4Lexer.OR)) {
                            return [containsAlts, overallLength];
                        }
                        containsAlts = true;
                    }
                    overallLength += 2;
                    break;
                }

                case ANTLRv4Lexer.NOT: {
                    ++overallLength; // Unary NOT, no space after that.
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

        // We should never arrive here, since we bail out above when the block end was found.
        return [containsAlts, overallLength];
    }

    /**
     * Determines if there is an element after the given position which should go
     * on the current line (line comment, lexer commands).
     */
    private nonBreakingTrailerAhead(i: number): boolean {
        if (this.tokens[++i].type == ANTLRv4Lexer.WS) {
            if (this.tokens[i].text!.indexOf("\n") >= 0) {
                return false;
            }
            ++i;
        }

        return this.tokens[i].type == ANTLRv4Lexer.LINE_COMMENT
            || this.tokens[i].type == ANTLRv4Lexer.RARROW
            || this.tokens[i].type == ANTLRv4Lexer.LPAREN;
    }

    /**
     * Scans the given comment for any of the formatter commands and parses them out.
     */
    private processFormattingCommands(index: number): void {

        let me = this;
        function resetAlignmentStatus(type: AlignmentType) {
            let status = me.alignments.get(type);
            if (status) {
                status.lastLine = -1;
                status.groupIndex = -1;
            }
        }

        let text = this.tokens[index].text!;
        text = text.substr(2, text.length - 2).trim();
        if (text.startsWith("$antlr-format")) {
            let entries = text.substr("$antlr-format".length + 1, text.length).split(",");
            for (let entry of entries) {
                let groups = /(\w+)(?:(?:\s*\:)?\s*)?(\w+|[0-9]+)?/i.exec(entry.trim());
                if (groups != undefined) {
                    switch (groups[1]) {
                        case "reset":
                            this.setDefaultOptions();
                            break;
                        case "on":
                        case "true":
                            this.formattingDisabled = false;
                            if (this.rangeStart > -1) {
                                this.addRaw(this.rangeStart, index - 1);
                            }
                            break;
                        case "off":
                        case "false":
                            this.formattingDisabled = true;
                            this.rangeStart = index;
                            break;

                        case "alignTrailingComments":
                        case "allowShortBlocksOnASingleLine":
                        case "breakBeforeBraces":
                        case "keepEmptyLinesAtTheStartOfBlocks":
                        case "reflowComments":
                        case "spaceBeforeAssignmentOperators":
                        case "useTab":
                        case "allowShortRulesOnASingleLine":
                        case "singleLineOverrulesHangingColon":
                        case "breakBeforeParens":
                        case "ruleInternalsOnSingleLine":
                        case "groupedAlignments":
                        case "alignFirstTokens":
                        case "alignLexerCommands":
                        case "alignActions":
                        case "alignTrailers": {
                            if (groups.length > 2
                                && (groups[2] == "true"
                                    || groups[2] == "false")
                                    || groups[2] == "on"
                                    || groups[2] == "off") {
                                this.options[groups[1]] = (groups[2] == "true" || groups[2] == "on");

                                // Some additional handling for alignments. Switching an alignment means
                                // that the alignment group for that alignment is finished.
                                switch (groups[1]) {
                                    case "groupedAlignments": {
                                        // End all ongoing alignment groups when switching grouped alignments.
                                        for (let entry of this.alignments) {
                                            entry[1].lastLine = -1;
                                            entry[1].groupIndex = -1;
                                        }
                                        break;
                                    }
                                    case "alignTrailingComments":
                                        resetAlignmentStatus(AlignmentType.TrailingComment);
                                        break;
                                    case "alignFirstTokens":
                                        resetAlignmentStatus(AlignmentType.FirstToken);
                                        break;
                                    case "alignLexerCommands":
                                        resetAlignmentStatus(AlignmentType.LexerCommand);
                                        break;
                                    case "alignActions":
                                        resetAlignmentStatus(AlignmentType.Action);
                                        break;
                                    case "alignTrailers":
                                        resetAlignmentStatus(AlignmentType.Trailers);
                                        break;
                                }
                            } else {
                                this.add(InsertMarker.Error);
                            }
                            break;
                        }

                        case "columnLimit":
                        case "continuationIndentWidth":
                        case "indentWidth":
                        case "maxEmptyLinesToKeep":
                        case "tabWidth":
                        case "minEmptyLines": {
                            if (groups.length > 2) {
                                let value = parseInt(groups[2]);
                                if (value != undefined) {
                                    this.options[groups[1]] = value;
                                } else {
                                    this.add(InsertMarker.Error);
                                }
                            } else {
                                this.add(InsertMarker.Error);
                            }
                            break;
                        }

                        case "alignColons": {
                            if (groups.length > 2) {
                                let value = groups[2];
                                if (value == "none" || value == "trailing" || value == "hanging") {
                                    this.options.alignColons = value;
                                } else {
                                    this.add(InsertMarker.Error);
                                }
                            } else {
                                this.add(InsertMarker.Error);
                            }
                            break;
                        }
                        case "alignSemicolons": {
                            if (groups.length > 2) {
                                let value = groups[2];
                                if (value == "none" || value == "ownLine" || value == "hanging") {
                                    this.options.alignSemicolons = value;
                                } else {
                                    this.add(InsertMarker.Error);
                                }
                            } else {
                                this.add(InsertMarker.Error);
                            }
                            break;
                        }
                        default: {
                            this.add(InsertMarker.Error);
                            break;
                        }
                    }
                }
            }
        }
    }

    /**
     * Inserts an alignment marker for the current alignment group for the given type.
     * If there's currently no active group a new one is started. This happens also if the current
     * position does not qualify for the current group.
     */
    private addAlignmentEntry(type: AlignmentType): void {
        if (!this.alignments.has(type)) {
            this.alignments.set(type, { lastLine: -1, groupIndex: -1 });
        }

        let status = this.alignments.get(type)!;

        // While we allow multiple different alignment types on a single line, we don't want the same type
        // more than once on a line.
        if (status.lastLine != this.currentLine) {
            while (this.lastEntryIs(InsertMarker.Space)) {
                this.removeLastEntry();
            }

            let startNewGroup = true;
            if (status.lastLine > -1) {
                // There's an active group. See if we can append the new entry to it.
                if (!this.options.groupedAlignments || status.lastLine + 1 == this.currentLine) {
                    // We can extend the active group.
                    startNewGroup = false;

                    // Groups consist of indices into the output pipeline.
                    // The insert marker in the pipeline points to the alignment group.
                    this.alignmentGroups[status.groupIndex].push(this.outputPipeline.length);
                    this.outputPipeline.push(InsertMarker.Alignment - status.groupIndex);
                }
            }

            if (startNewGroup) {
                status.groupIndex = this.alignmentGroups.length;
                this.alignmentGroups.push([this.outputPipeline.length]);
                this.outputPipeline.push(InsertMarker.Alignment - status.groupIndex);
            }

            status.lastLine = this.currentLine;
        }
    }

    /**
     * Goes through the output pipeline, looking for alignment markers. If one is found all members
     * for this alignment group are examined to find the column to align to and the markers are replaced
     * by indices into a list, where we keep the whitespaces to fill in.
     */
    private computeAlignments(): void {
        for (let index of this.outputPipeline) {
            if (index <= InsertMarker.WhitespaceBlock) {
                continue;
            }

            if (index <= InsertMarker.Alignment) {
                let groupIndex = -(index - InsertMarker.Alignment);
                let group = this.alignmentGroups[groupIndex];

                // If the group only consists of a single member then ignore it.
                if (group.length == 1) {
                    this.outputPipeline[group[0]] = InsertMarker.Space;
                    continue;
                }

                let columns: number[] = [];
                for (let member of group) {
                    console.assert(this.outputPipeline[member] <= InsertMarker.Alignment);
                    columns.push(this.computeColumn(member));
                }

                // Determine the largest column and bring this up to the next tab stop (if we are using tabs)
                // or add a single space to the longest column and align all others to this position.
                let useTabs = this.options.useTab;
                let maxColumn = Math.max(...columns);
                if (useTabs) {
                    maxColumn += this.options.tabWidth! - (maxColumn % this.options.tabWidth!);
                } else {
                    ++maxColumn;
                }

                // Compute required whitespace inserts and store them in the whitespace list.
                // Replace the alignment markers in the current group with the indices in that list.
                for (let i = 0; i < group.length; ++i) {
                    let whitespaceIndex = InsertMarker.WhitespaceBlock - this.whitespaceList.length;
                    this.outputPipeline[group[i]] = whitespaceIndex;

                    let whitespaces;
                    if (useTabs) {
                        let tabCount = Math.floor((maxColumn - columns[i]) / this.options.tabWidth!);
                        if ((maxColumn - columns[i]) % this.options.tabWidth! != 0) {
                            ++tabCount;
                        }
                        whitespaces = Array(tabCount).fill("\t").join("");
                    } else {
                        whitespaces = Array(maxColumn - columns[i]).fill(" ").join("");
                    }
                    this.whitespaceList.push(whitespaces);
                }
            }
        }
    }

    /**
     * Determines the column offset of the given entry in the output pipeline.
     */
    private computeColumn(offset: number): number {
        let result = 0;

        // Scan back to last line break.
        let run = offset;
        while (--run > -1) {
            if (this.outputPipeline[run] == InsertMarker.LineBreak) {
                break;
            }
        }

        // Now sum up the individual entries. Need to collect text here since ranges
        // as well as lexer tokens can contain tabs.
        let text = "";
        while (++run < offset) {
            let entry = this.outputPipeline[run];
            switch (entry) {
                case InsertMarker.Space:
                    text += " ";
                    break;
                case InsertMarker.Tab:
                    text += "\t";
                    break;
                case InsertMarker.WhitespaceEraser: // Ignore.
                case InsertMarker.Error:
                    break;
                default:
                    // We cannot see alignment markers here (as we are currently processing one),
                    // nor whitespace blocks (we are inserting them afterwards).
                    if (entry < 0) {
                        if (isRangeBlock(entry)) {
                            // Copy an entire block.
                            let rangeIndex = -(entry - InsertMarker.Range);
                            let startIndex = this.ranges[rangeIndex][0];
                            let endIndex = this.ranges[rangeIndex][1];
                            let interval = Interval.of(this.tokens[startIndex].startIndex, this.tokens[endIndex].stopIndex);
                            text += this.tokens[0].inputStream!.getText(interval);
                        } if (isWhitespaceBlock(entry)) {
                            let whitespaceIndex = -(entry - InsertMarker.WhitespaceBlock);
                            text += this.whitespaceList[whitespaceIndex];
                        }
                    } else {
                        text += this.tokens[entry].text;
                    }
                    break;

            }
        }

        for (let char of text) {
            if (char == "\t") {
                result += this.options.tabWidth! - (result % this.options.tabWidth!);
            } else {
                ++result;
            }
        }

        return result;
    }

    private options: FormattingOptions;

    // The pipeline contains markers for constructing the final text.
    // A marker is either an index in the token list (if >= 0) or one of the special markers
    // (when < 0), like space, line break, alignment and range markers.
    private outputPipeline: InsertMarker[];

    private currentIndentation: number;
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
    private rangeStart: number; // Holds the start index of a range when collecting.

    // For each possible alignment type (colon, first token, trailing predicate, trailing comment etc.)
    // there's one status record in this map.
    private alignments: Map<AlignmentType, AlignmentStatus> = new Map();
    private alignmentGroups: number[][]; // A list of output pipeline indices for groups of alignments.
    private whitespaceList: string[]; // A list of strings containing whitespaces to insert for alignment.
}
