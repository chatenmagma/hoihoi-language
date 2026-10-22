parser grammar HoihoiParser;

options {
    tokenVocab = HoihoiLexer;
}


program
    : NEWLINE*
      stmt*
      NEWLINE*
      EOF
    ;

stmt
    : simpleStmt NEWLINE+
    | blockStmt
    ;

simpleStmt
    : assign
    | expr
    | PASS
    | RETURN expr?
    ;

blockStmt
    : ifStmt
    | whileStmt
    | funStmt
    ;

ifStmt
    : IF expr COLON suite elif* else?
    ;

elif
    : ELIF expr COLON suite
    ;

else
    : ELSE COLON suite
    ;

whileStmt
    : WHILE expr COLON suite
    ;

funStmt
    : DEF IDENTIFIER OPEN_PAREN args? CLOSE_PAREN (ARROW objectType)? COLON suite
    ;

args
    : IDENTIFIER (COMMA objectType)? (COLON IDENTIFIER (COMMA objectType)?)*
    ;

suite
    : NEWLINE INDENT stmt+ DEDENT
    ;

assign
    : IDENTIFIER (COMMA objectType)? ASSIGN expr
    | IDENTIFIER (COMMA objectType)? (ADD_ASSIGN | SUB_ASSIGN | MUL_ASSIGN) expr
    ;

objectType
    : IDENTIFIER (OR IDENTIFIER)*
    | THING
    ;

expr
    : NOT? or
    ;

or
    : and (OR and)*
    ;

and
    : comparaision (AND comparaision)*
    | addition (AND addition)*
    ;

comparaision
    : addition EQUAL addition
    | addition NOT_EQUAL addition
    | addition LESS_THAN addition
    | addition GREATER_THAN addition
    ;

addition
    : multiplication ((PLUS | MINUS) multiplication)*
    ;

multiplication
    : attribute ((STAR | MODULO | SLASH) attribute)*
    ;

primary
    : IDENTIFIER
    | fun
    | clusterLiteral
    | PRIMITIVE primitive
    | OPEN_PAREN expr CLOSE_PAREN
    | EMPTY
    ;

clusterLiteral
    : OPEN_BRACKET (primitive (COMMA primitive)*)? CLOSE_BRACKET
    | primitive
    ;

attribute
    : primary (OPEN_BRACKET expr CLOSE_BRACKET)?
    | primary ((DOT | COLON) IDENTIFIER)?
    | primary ((DOT | COLON) fun)?
    ;

fun
    : IDENTIFIER OPEN_PAREN
      (expr (COMMA expr)*)?
      CLOSE_PAREN
    ;

primitive
    : MINUS? NUMBER_LITERAL
    | STRING_LITERAL
    | HIGH
    | NEUTRAL
    | LOW
    ;
