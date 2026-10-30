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
    | importStmt NEWLINE+
    ;

importStmt
    : IMPORT IDENTIFIER (DOT IDENTIFIER)* 
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
    | addition EQUIVALENT addition
    ;

addition
    : multiplication ((PLUS | MINUS) multiplication)*
    ;

multiplication
    : primary ((STAR | MODULO | SLASH) primary)*
    ;

primary
    : MINUS? OPEN_PAREN expr CLOSE_PAREN attribute*
    | MINUS? IDENTIFIER attribute*
    | MINUS? fun attribute*
    | MINUS? cluster attribute*
    | primitive
    | EMPTY
    ;

cluster
    : vector
    | bag
    | tuple
    | set
    | string
    ;

attribute
    : (DOT | COLON) IDENTIFIER attributeArgs?
    | OPEN_BRACKET expr CLOSE_BRACKET attributeArgs?
    ;

attributeArgs
    : OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

vector
    : OPEN_BRACKET (expr (COMMA expr)*)? CLOSE_BRACKET
    | VECTOR OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

bag
    : OPEN_BRASE (expr (COMMA expr)*)? CLOSE_BRASE
    | BAG OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

tuple
    : TUPLE OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

set
    : SET OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

string
    : STRING OPEN_PAREN (expr (COMMA expr)*)? CLOSE_PAREN
    ;

fun
    : IDENTIFIER OPEN_PAREN
      (expr (COMMA expr)*)?
      CLOSE_PAREN
    ;

number
    : INTEGER_LITERAL
    | FLOAT_LITERAL
    ;

primitive
    : STRING_LITERAL
    | number
    | HIGH
    | NEUTRAL
    | LOW
    ;
