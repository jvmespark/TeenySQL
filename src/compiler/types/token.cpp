#include "token.h"
#include "literal.h"

#include <map>
#include <string>
#include <type_traits>
#include <utility>

const std::string& TokenTypeString(const TokenType value) {
    static const std::map<TokenType, std::string> lookUpTable{
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::STRING, "STRING"},
        {TokenType::NUMBER, "NUMBER"},
        {TokenType::STAR, "STAR"},
        {TokenType::SELECT, "SELECT"},
        {TokenType::TQ_EOF, "EOF"}
    };
        /*
        {TokenType::LEFT_PAREN, "LEFT_PAREN"},
        {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
        {TokenType::LEFT_BRACE, "LEFT_BRACE"},
        {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::COLON, "COLON"},
        {TokenType::DOT, "DOT"},
        {TokenType::QUESTION, "QUESTION"},
        {TokenType::SLASH, "SLASH"},
        {TokenType::STAR, "STAR"},
        {TokenType::BANG, "BANG"},
        {TokenType::BANG_EQUAL, "BANG_EQUAL"},
        {TokenType::EQUAL, "EQUAL"},
        {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
        {TokenType::GREATER, "GREATER"},
        {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::LESS, "LESS"},
        {TokenType::LESS_EQUAL, "LESS_EQUAL"},
        {TokenType::MINUS, "MINUS"},
        {TokenType::MINUS_MINUS, "MINUS_MINUS"},
        {TokenType::PLUS, "PLUS"},
        {TokenType::PLUS_PLUS, "PLUS_PLUS"},
        {TokenType::AND, "AND"},
        {TokenType::CLASS, "CLASS"},
        {TokenType::ELSE, "ELSE"},
        {TokenType::LOX_FALSE, "FALSE"},
        {TokenType::FUN, "FUN"},
        {TokenType::FOR, "FOR"},
        {TokenType::IF, "IF"},
        {TokenType::NIL, "NIL"},
        {TokenType::OR, "OR"},
        {TokenType::PRINT, "PRINT"},
        {TokenType::RETURN, "RETURN"},
        {TokenType::SUPER, "SUPER"},
        {TokenType::THIS, "THIS"},
        {TokenType::LOX_TRUE, "TRUE"},
        {TokenType::VAR, "VAR"},
        {TokenType::WHILE, "WHILE"},
        */ 
    return lookUpTable.find(value)->second;
}

Token::Token(TokenType p_type, std::string p_lexeme, OptionalLiteral p_literal, int p_line)
    :
        type(p_type),
        lexeme(std::move(p_lexeme)),
        literal(std::move(p_literal)),
        line(p_line) {}

Token::Token(TokenType p_type, const char* p_lexeme, OptionalLiteral p_literal, int p_line)
    :
        type(p_type),
        lexeme(p_lexeme),
        literal(std::move(p_literal)),
        line(p_line) {}

Token::Token(TokenType p_type, const char* p_lexeme)
    :
        type(p_type), lexeme(p_lexeme) {}

std::string  Token::toString() const {
    std::string result = std::to_string(line) + " " + TokenTypeString(type) + " " + lexeme + " ";
    result += literal.has_value() ? getLiteralString(literal.value()) : "No Literal";
    return result;
}

TokenType Token::getType() const {
    return this->type;
}

const std::string& Token::getTypeString() const {
    return TokenTypeString(this->type);
}

const std::string& Token::getLexeme() const {
    return this->lexeme;
};

const OptionalLiteral& Token::getOptionalLiteral() const {
    return this->literal;
}

int Token::getLine() const {
    return this->line;
}