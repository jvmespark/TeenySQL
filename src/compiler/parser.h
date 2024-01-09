/*
    parser to turn scanned tokens into an abstract syntax tree nodetype representation
    top down recursive descent parser implementation

    goes through and logically matches and groups tokens and packages all the necessary information to a AST node/block

    in parser:
        consume blocks of grouped info and make them into AST node. return a vector of all these ptrs after.

    in AST nodes:
        ultimately they are structs and you fill in the info. then make you pointer of that struct type
            ex: expressions and statements
                literal is an expr, insert is a statement. etc.

*/

#pragma once

#include <vector>
#include <optional>

#include "./types/literal.h"
#include "./types/token.h"
#include "AST.h"

class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);

        std::vector<StmtPtrVariant> parse();
    private:
        std::optional<StmtPtrVariant> parseStatement();

        // statement parsing
        StmtPtrVariant insertStmt();
        StmtPtrVariant selectStmt();

        // expression parsing
        std::optional<ExprPtrVariant> parseExpression();

        // parser
        Token peek() const;
        bool isEOF() const;
        Token getTokenAndAdvance();
        void advance();
        bool match(TokenType type) const;
        bool match(const std::initializer_list<TokenType>& types) const;
        void consumeOrError(TokenType tType, const std::string& errorMessage);
        void consumeSemicolonOrError();

        ExprPtrVariant consumeOneLiteral();
        ExprPtrVariant consumeOneLiteral(const std::string& s);

        // data
        const std::vector<Token>& tokens;
        std::vector<StmtPtrVariant> statements;
        std::vector<Token>::const_iterator currentIter;
};  