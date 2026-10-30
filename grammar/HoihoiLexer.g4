lexer grammar HoihoiLexer;

tokens {
    INDENT,
    DEDENT
}

@header {
#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <utility>
}

@members {

    std::deque<std::unique_ptr<antlr4::Token>> pendingTokens;
    std::vector<size_t> indents = { 0 };

    size_t indentationCount(const std::string& text)
    {
        size_t count = 0;

        // text contient par exemple "\n    "
        // On ne compte que les espaces/tabs après le newline.
        for (size_t i = 0; i < text.size(); ++i)
        {
            if (text[i] == ' ')
            {
                ++count;
            }
            else if (text[i] == '\t')
            {
                // Convention simple : tab = 4 espaces
                count += 4;
            }
        }

        return count;
    }

    std::unique_ptr<antlr4::Token> makeLayoutToken(size_t type)
    {
        auto token = std::make_unique<antlr4::CommonToken>(
            std::pair<antlr4::TokenSource*, antlr4::CharStream*>{this, _input},
            type,
            antlr4::Token::DEFAULT_CHANNEL,
            getCharIndex(),
            getCharIndex() - 1
        );

        token->setLine(getLine());
        token->setCharPositionInLine(getCharPositionInLine());

        return token;
    }

    std::unique_ptr<antlr4::Token> popPending()
    {
        auto token = std::move(pendingTokens.front());
        pendingTokens.pop_front();
        return token;
    }

    std::unique_ptr<antlr4::Token> nextToken() override
    {
        // Des tokens INDENT/DEDENT sont déjà en attente.
        if (!pendingTokens.empty())
        {
            return popPending();
        }

        // Demande au lexer ANTLR normal de produire le prochain token.
        auto token = antlr4::Lexer::nextToken();

        // EOF :
        // s'il reste des niveaux d'indentation ouverts,
        // il faut générer les DEDENT manquants.
        if (token->getType() == antlr4::Token::EOF)
        {
            while (indents.size() > 1)
            {
                indents.pop_back();
                pendingTokens.push_back(makeLayoutToken(DEDENT));
            }

            pendingTokens.push_back(std::move(token));

            return popPending();
        }

        // On ne s'intéresse qu'aux NEWLINE.
        if (token->getType() == NEWLINE)
        {
            const std::string text = token->getText();

            // Après le NEWLINE, regarde ce qui arrive.
            const size_t next = _input->LA(1);

            // Ligne vide / commentaire :
            // on ne modifie PAS l'indentation.
            if (next == '\n' ||
                next == '\r' ||
                next == '#' ||
                next == antlr4::Token::EOF)
            {
                return token;
            }

            const size_t indent = indentationCount(text);
            const size_t previous = indents.back();

            if (indent > previous)
            {
                indents.push_back(indent);
                pendingTokens.push_back(makeLayoutToken(INDENT));
            }
            else if (indent < previous)
            {
                while (indents.size() > 1 && indents.back() > indent)
                {
                    indents.pop_back();
                    pendingTokens.push_back(makeLayoutToken(DEDENT));
                }
            }
        }

        return token;
    }

    void reset() override
    {
        antlr4::Lexer::reset();

        pendingTokens.clear();

        indents.clear();
        indents.push_back(0);
    }
}

// Keywords

IF: 'if';
ELIF: 'elif';
ELSE: 'else';
COMPARE: 'compare';
CASE: 'case';

RETURN: 'return';
PASS: 'pass';
WHILE: 'while';
DEF: 'def';

IMPORT: 'import';

HIGH: 'high';
NEUTRAL: 'neutral';
LOW: 'low';

BAG: 'bag';
SET: 'set';
STRING: 'str';
TUPLE: 'tuple';
VECTOR: 'vector';

// Operators

ARROW: '->';
DOT: '.';
DOUBLE_DOT: '..';
STAR: '*';
COMMA: ',';
SEMI_COLON: ';';
COLON: ':';
ASSIGN: '=';
PLUS: '+';
MINUS: '-';
SLASH: '/';
MODULO: '%';
LESS_THAN: '<';
GREATER_THAN: '>';
EQUIVALENT: '<>';
NUMBER: '#';

OR: 'or';
AND: 'and';
NOT: 'not';

EQUAL: '==';
NOT_EQUAL: '!=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';

HEAP: 'heap';
HOLE: 'hole';
FLAT: 'flat';
QUOTE: '\'';
DQUOTE: '"';

EMPTY: 'empty';
THING: 'thing';

STRING_LITERAL
    : QUOTE ('\\' (RN | .) | ~[\\\r\n'])* QUOTE
    | DQUOTE ('\\' (RN | .) | ~[\\\r\n"])* DQUOTE
    ;
    
INTEGER_LITERAL: MINUS? [0-9]+;
FLOAT_LITERAL: MINUS? [0-9]+ '.' ('f' | 'F' | [0-9]*);

IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;

OPEN_PAREN: '(';
CLOSE_PAREN: ')';
OPEN_BRASE: '{';
CLOSE_BRASE: '}';
OPEN_BRACKET: '[';
CLOSE_BRACKET: ']';

NEWLINE: RN [ \t]*;
WS: [ \t]+ -> channel(HIDDEN);
CONTENT: '#' ~[\r\n\f]* -> channel(HIDDEN);

fragment RN: '\r'? '\n';
