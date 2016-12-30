
import { Lexer } from 'antlr4ts';
import { CharStream } from 'antlr4ts';
import { Token } from 'antlr4ts';
import { Interval } from 'antlr4ts/misc';

import { ANTLRv4Lexer } from './ANTLRv4Lexer';

export abstract class LexerAdaptor extends Lexer {
    private _currentRuleType : number = Token.INVALID_TYPE;

    public emit(): Token {
        if (this._type == ANTLRv4Lexer.ID) {
            let firstChar : string = this._input.getText(new Interval(this._tokenStartCharIndex, this._tokenStartCharIndex));
            if (firstChar.charAt(0) == firstChar.charAt(0).toUpperCase()) {
                this._type = ANTLRv4Lexer.TOKEN_REF;
            } else {
                this._type = ANTLRv4Lexer.RULE_REF;
            }

            if (this._currentRuleType == Token.INVALID_TYPE) { // if outside of rule def
                this._currentRuleType = this._type; // set to inside lexer or parser rule
            }
        } else if (this._type == ANTLRv4Lexer.SEMI) { // exit rule def
            this._currentRuleType = Token.INVALID_TYPE;
        }
        return super.emit();
    }

    protected handleBeginArgument() {
        if (this._currentRuleType == ANTLRv4Lexer.TOKEN_REF) {
            this.pushMode(ANTLRv4Lexer.LexerCharSet);
            this.more();
        } else {
            this.pushMode(ANTLRv4Lexer.Argument);
        }
    }

    protected handleEndArgument() {
        this.popMode();
        if (this._modeStack.size() > 0) {
            this.setType(ANTLRv4Lexer.ARGUMENT_CONTENT);
        }
    }

    protected handleEndAction() {
        this.popMode();
        if (this._modeStack.size() > 0) {
            this.setType(ANTLRv4Lexer.ACTION_CONTENT);
        }
    }
}
