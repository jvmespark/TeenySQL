#include "compiler.h"

#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <utility>

/*
----AST NODE TYPE CONTSTRUCTORS
*/
// expressions
LiteralExpr::LiteralExpr(OptionalLiteral value)
    : literalVal(std::move(value)) {}

// statements
InsertStmt::InsertStmt(ExprPtrVariant values)
    : values(std::move(values)) {}
SelectStmt::SelectStmt(TokenType selectVal)
    : selectVal(std::move(selectVal)) {}

/*
---POINTER CREATORS
*/
// expressions
ExprPtrVariant createLiteralEPV(OptionalLiteral literal) {
    return std::make_unique<LiteralExpr>(std::move(literal));
}

// statements
StmtPtrVariant createInsertSPV(ExprPtrVariant values) {
    return std::make_unique<InsertStmt>(std::move(values));
}

StmtPtrVariant createSelectSPV(TokenType selectVal) {
    return std::make_unique<SelectStmt>(std::move(selectVal));
}