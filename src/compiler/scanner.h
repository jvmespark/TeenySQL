/*
    lexical scanner to tokenize inputs

    goes through and matches the code/queries with the associated token
    returns a vector of the tokens
*/

#pragma once

#include <list>
#include <string>
#include <vector>

#include "./types/token.h"

class Scanner {
    public:
        Scanner(const std::string &sql);
        std::vector<Token> tokenize();

    private:
        bool isAtEnd();
        void tokenizeOne();
        void advance();
        bool matchNext(char expected);
        char peek();
        char peekNext();
        void skipComment();
        void skipBlockComment();
        void eatIdentifier();
        void eatNumber();
        void eatString();
        void addToken(TokenType t);

        const std::string &source;

        std::list<Token> tokens;
        size_t start = 0;
        size_t current = 0;
        int line = 1;
};