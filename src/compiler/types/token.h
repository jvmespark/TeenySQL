/*
    token types
*/

#pragma once

#include <string>

#include "literal.h"

enum class TokenType {
    // Single-character tokens.
    /*
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COLON,
    COMMA,
    DOT,
    QUESTION,
    SEMICOLON,
    SLASH,
    STAR,
    */
   SEMICOLON,

    // One or two character tokens.
    /*
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    MINUS,
    MINUS_MINUS,
    PLUS,
    PLUS_PLUS,
    */

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    /*
    AND,
    CLASS,
    ELSE,
    LOX_FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    LOX_TRUE,
    VAR,
    WHILE,
    */
    INSERT,

    TQ_EOF
};

class Token {
    public:
        Token(TokenType p_type, std::string p_lexeme, OptionalLiteral p_literal, int p_line);
        Token(TokenType p_type, const char* p_lexeme, OptionalLiteral p_literal, int p_line);
        Token(TokenType p_type, const char* p_lexeme);

        [[nodiscard]] std::string toString() const;
        [[nodiscard]] TokenType getType() const;
        [[nodiscard]] const std::string& getTypeString() const;
        [[nodiscard]] int getLine() const;
        [[nodiscard]] const std::string& getLexeme() const;
        [[nodiscard]] const OptionalLiteral& getOptionalLiteral() const;

    private:
        const TokenType type;
        const std::string lexeme;
        OptionalLiteral literal = std::nullopt;
        const int line = -1;
};