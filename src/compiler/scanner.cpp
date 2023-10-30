#include <map>
#include <iostream>
#include <optional>

#include "compiler.h"
#include "types/literal.h"
#include "types/token.h"

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

TokenType ReservedOrIdentifier(const std::string& str) {
    static const std::map<std::string, TokenType> lookUpTable{
        {"INSERT", TokenType::INSERT},
        {"SELECT", TokenType::SELECT},
        /*
        {"and", TokenType::AND},       {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},     {"false", TokenType::LOX_FALSE},
        {"fun", TokenType::FUN},       {"for", TokenType::FOR},
        {"if", TokenType::IF},         {"nil", TokenType::NIL},
        {"or", TokenType::OR},         {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
        {"this", TokenType::THIS},     {"true", TokenType::LOX_TRUE},
        {"var", TokenType::VAR},       {"while", TokenType::WHILE}};
        */
    };

    auto iter = lookUpTable.find(str);
    if (iter == lookUpTable.end()) {
        return TokenType::IDENTIFIER;
    }
    return iter->second;
}

std::string getLexeme(const std::string& source, size_t start, size_t end) {
    return source.substr(start, end);
}

OptionalLiteral makeOptionalLiteral(TokenType t, const std::string& lexeme) {
    switch (t) {
        case TokenType::NUMBER:
            return makeOptionalLiteral(std::stod(lexeme));
        case TokenType::STRING:
            return makeOptionalLiteral(lexeme.substr(1, lexeme.size() - 2));
        default: return std::nullopt;
    }
}

Scanner::Scanner(const std::string& p_source) : source(p_source) {}

void Scanner::addToken(TokenType t) {
    const std::string lexeme = getLexeme(source, start, current - start);
    tokens.emplace_back(t, lexeme, makeOptionalLiteral(t, lexeme), line);
}

void Scanner::advance() {
    current++;
}

void Scanner::skipBlockComment() {
    int nesting = 1;
    while (nesting > 0) {
        if (peek() == '\0') {
            //eReporter.setError(line, "Block comment not closed?");
        return;
    }

    if (peek() == '/' && peekNext() == '*') {
        advance();
        nesting++;
    }
    else if (peek() == '*' && peekNext() == '/') {
        advance();
        nesting--;
    }
    else if (peek() == '\n') {
        line++;
    }
        advance();
    }
}

void Scanner::skipComment() {
    while (!isAtEnd() && peek() != '\n') {
        advance();
    }
}

void Scanner::eatIdentifier() {
    while (isAlphaNumeric(peek())) advance();
}

void Scanner::eatNumber() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }
}

void Scanner::eatString() {
    while (!isAtEnd() && peek() != '"') {
    if (peek() == '\n') ++line;
        advance();
    }

    if (isAtEnd()) {
        //eReporter.setError(line, "Unterminated String!");
    }
    else {
        advance();  // consume the closing quote '"'
    }
}

bool Scanner::isAtEnd() {
    return current >= source.size();
}

bool Scanner::matchNext(char expected) {
    bool nextMatches = (peek() == expected);
    if (nextMatches) advance();
    return nextMatches;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if ((current + 1) >= source.size()) return '\0';
    return source[current + 1];
}

void Scanner::tokenizeOne() {
    char c = peek();
    advance();
    switch (c) {
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        /*
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case ':': addToken(TokenType::COLON); break;
        case '.': addToken(TokenType::DOT); break;
        case '?': addToken(TokenType::QUESTION); break;
        case '*': addToken(TokenType::STAR); break;
        case '!':
            addToken(matchNext('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(matchNext('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '>':
            addToken(matchNext('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '<':
            addToken(matchNext('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '-':
            addToken(matchNext('-') ? TokenType::MINUS_MINUS : TokenType::MINUS);
            break;
        case '+':
            addToken(matchNext('+') ? TokenType::PLUS_PLUS : TokenType::PLUS);
            break;
        case '/':
            if (matchNext('/'))
            skipComment();
            else if (matchNext('*'))
            skipBlockComment();
            else
            addToken(TokenType::SLASH);
            break;
        case ' ':
        case '\t':
        case '\r': break;  // whitespace
        case '\n': ++line; break;
        */
        case '"':
            eatString();
            addToken(TokenType::STRING);
            break;
        default:
            if (isDigit(c)) {
                eatNumber();
                addToken(TokenType::NUMBER);
            }
            else if (isAlpha(c)) {
                eatIdentifier();
                const std::string identifier = getLexeme(source, start, current - start);
                addToken(ReservedOrIdentifier(identifier));
            }
            else {
                std::string message = "Unexpected character: ";
                message.append(1, static_cast<char>(c));
                //eReporter.setError(line, message);
            }
            break;
    }
}

std::vector<Token> Scanner::tokenize() {
    while (!isAtEnd()) {
        start = current;
        tokenizeOne();
    }
    tokens.emplace_back(TokenType::TQ_EOF, "", std::nullopt, line);
    std::vector<Token> tokensVec;
    std::move(tokens.begin(), tokens.end(), std::back_inserter(tokensVec));
    return tokensVec;
}
