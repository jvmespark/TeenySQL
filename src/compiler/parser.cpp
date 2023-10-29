#include <exception>
// testing
#include <iostream>

#include "compiler.h"

// toydb: parser: statement, (insert,...) ddl (table,...), expression (paran,comma,literal,...) 
// for now: statement (insert), expression (literal), expand later.

// parse statements. some statements go to parse ddl. in statements you parse expressions.

Parser::Parser(const std::vector<Token>& p_tokens)
    : tokens(p_tokens) {
    this->currentIter = this->tokens.begin();
}

/*
----PARSER HELPERS
*/
// constructor
//advance
// consume binary expressions
// consume or error
// consume one literal (string)
// consume one literal
// consume super
// consume grouping expr
// consume post fix expr
// consume unary expr
// consume var expr
// consume semicolon or error
// get current token type
// get token and advance
// is at end
// match (tokentype)
// match (list of tokentypes)
// match next
// peek

void Parser::advance() {
    if (!isEOF()) {
        currentIter++;
    }
}

Token Parser::getTokenAndAdvance() {
    Token token = peek();
    advance();
    return token;
}

Token Parser::peek() const {
    return *currentIter;
}

bool Parser::match(TokenType type) const {
    if (isEOF()) {
        return false;
    }
    return (type == currentIter->getType());
}

bool Parser::match(const std::initializer_list<TokenType>& types) const {
    bool result = false;
    for (const auto& type : types) {
        result = (result || match(type));
  }
    return result;
}

bool Parser::isEOF() const {
    return peek().getType() == TokenType::TQ_EOF;
}

ExprPtrVariant Parser::consumeOneLiteral(const std::string& str) {
    advance();
    return createLiteralEPV(makeOptionalLiteral(str));
}

ExprPtrVariant Parser::consumeOneLiteral() {
    return createLiteralEPV(getTokenAndAdvance().getOptionalLiteral());
}

void Parser::consumeOrError(TokenType tType, const std::string& errorMessage) {
    if (currentIter->getType() == tType) {
        return advance();
    }
    //throw error(errorMessage + " Got: " + peek().toString());
}

void Parser::consumeSemicolonOrError() {
    consumeOrError(TokenType::SEMICOLON, "Expected a ';'");
}

std::vector<StmtPtrVariant> Parser::parse() {
    while (!isEOF()) {
        std::optional<StmtPtrVariant> statement = parseStatement();
        if (statement.has_value()) {
            statements.push_back(std::move(statement.value()));
        }
        else {
            std::cout<<"ERROR: invalid statement"<<std::endl;
            exit(1);
        }
    }
    return std::move(this->statements);
}



/*
----STATEMENT RULES
*/
// parse
// statements
//  statement rules: insert, ...
// expression
//  expression rules: primary, ...
std::optional<StmtPtrVariant> Parser::parseStatement() {
    if (match(TokenType::INSERT)) return insertStmt();
    return std::nullopt;
}

StmtPtrVariant Parser::insertStmt() {
    advance();
    ExprPtrVariant values = *std::move(parseExpression());
    consumeSemicolonOrError();
    return createInsertSPV(std::move(values));
}



/*
----EXPRESSION RULES
*/
std::optional<ExprPtrVariant> Parser::parseExpression() {
    // TODO
    // comma (?)
    if (match(TokenType::NUMBER)) return consumeOneLiteral();
    return std::nullopt;
}