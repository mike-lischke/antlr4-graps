grammar test1;

options { // Trailing comment.
	/*Other comment.*/ superClass = Base1;

	superClass = Base2;

	/* comment */ superClass = Base3; // trailing comment
	/* another comment */
	superClass = /* inline comment */ Base4 /* inline comment */;

	// Single line comment, non-trailing
	/*final comment*/
}

//channels { CommentsChannel, DirectiveChannel }

tokens { // Trailing comment.
	DUMMY,
	Blah,

	// Description of these tokens.
	AnotherToken,
	YetAnotherOneWithLongName // This is important.
}

// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// $antlr-format minEmptyLines 0
// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.
@lexer::header {/* lexer header section */}

// Appears before any #include in h + cpp files.
@lexer::preinclude {/* lexer precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@lexer::postinclude {
/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).
@lexer::context {/* lexer context section */}

// Appears in the public part of the lexer in the h file.
@lexer::members {/* public lexer declarations section */
bool canTestFoo() { return true; }
bool isItFoo() { return true; }
bool isItBar() { return true; }

void myFooLexerAction() { /* do something*/ };
void myBarLexerAction() { /* do something*/ };
}

// Appears in the private part of the lexer in the h file.
@lexer::declarations {/* private lexer declarations/members section */}

// Appears in line with the other class member definitions in the cpp file.
@lexer::definitions {/* lexer definitions section */}

// Actual grammar start.
main	: stat+ EOF;
divide	: ID (and_ GreaterThan)? {doesItBlend()}?;
and_
	@init { doInit(); }
	@after { doAfter(); } : And;

conquer : // Comment comment
	// a description
	divide+
	| {doesItBlend()}? and_ { myAction(); } // trailing description
	// another description
	| ID (LessThan* divide)?? { $ID.text; }
;

// Unused rule to demonstrate some of the special features.
unused[double input = 111]
	returns[double calculated]
	locals[int _a, double _b, int _c]
	@init { doInit(); }
	@after { doAfter(); } : stat;
catch[...] {
  // Replaces the standard exception handling.
}
finally {
  cleanUp();
}

unused2 :
	(unused[1] .)+ (Colon | Semicolon | Plus)? ~Semicolon
;

stat : expr Equal expr Semicolon | expr Semicolon;

expr :
	expr Star expr
	| expr Plus expr
	| OpenPar expr ClosePar
	| <assoc = right> expr QuestionMark expr Colon expr
	| <assoc = right> expr Equal expr
	| identifier = id
	| flowControl
	| INT
	| String
;

flowControl :
	(Return expr | 'return') # Return
	| Continue # Continue
;

id		: ID;
array	: OpenCurly el += INT (Comma el += INT)* CloseCurly;
idarray	:
	OpenCurly element += id (Comma element += id)* CloseCurly
;
any : t = .;

Return		: 'return';
Continue	: 'continue';

INT		: Digit+;
Digit	: [0-9];

ID				: LETTER (LETTER | '0'..'9')*;
fragment LETTER	: [a-zA-Z\u0080-\uFFFF];

Test : 'abc' | 'def' | 'ghi';

LessThan	: '<';
GreaterThan	: '>';
Equal		: '=';
And			: 'and';

// $antlr-format alignColon: none, alignFirstToken on, alignLexerCommand true
Colon:				':';
Semicolon:			';';
Plus:				'+';
Minus:				'-';
Star:				'*';
OpenPar:			'(';
ClosePar:			')';
OpenCurly:			'{';
CloseCurly:			'}';
QuestionMark:		'?';
Comma:				',' -> skip;
Dollar:				'$';
LongLongLongToken:	'ABCDEFGHIJKLMNOPQRSTUVWXYZ'	-> mode(Blah);
Ampersand:			'&'								-> type(DUMMY), mode(Blah);

String:	'"' .*? '"';
Foo:	{canTestFoo()}? 'foo' {isItFoo()}? { myFooLexerAction(); }
;
Bar:	'bar' {isItBar()}? { myBarLexerAction(); };
Any:	Foo Dot Bar? DotDot Baz Bar;

Comment:	'#' ~[\r\n]* '\r'? '\n'; // -> channel(CommentsChannel);
WS:			[\r\n]+	-> channel(99);
WS2:		[ \t]+	-> channel(HIDDEN);

fragment Baz: 'Baz';

Dot:	'.';
DotDot:	'..';
