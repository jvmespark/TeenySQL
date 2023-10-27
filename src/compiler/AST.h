/*
    abstract syntax tree node types
    bunch of pointer types that represent the grouping and info of that type structure
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <variant>

#include "types/literal.h"
#include "types/token.h"
#include "types/uncopyable.h"

/*
----FORWARD DECLARATIONS OF AST NODE TYPES
*/
// expression
struct LiteralExpr;

// statement
struct InsertStmt;



/*
----UNIQUE POINTERS
*/
// expressions
using LiteralExprPtr = std::unique_ptr<LiteralExpr>;

// statements
using InsertStmtPtr = std::unique_ptr<InsertStmt>;



/*
----VARIANT POINTERS 
*/
// expressions
using ExprPtrVariant = std::variant<LiteralExprPtr>;

ExprPtrVariant createLiteralEPV(OptionalLiteral literal);

// statements
using StmtPtrVariant = std::variant<InsertStmtPtr>;

StmtPtrVariant createInsertSPV(ExprPtrVariant values);



/*
----AST NODE TYPES
*/
// expressions
struct LiteralExpr final : public Uncopyable {
    OptionalLiteral literalVal;

    explicit LiteralExpr(OptionalLiteral value);
};

// statements
struct InsertStmt final : public Uncopyable {
    /*
        TODO
        heres how toydb declares an insert statement:
            Insert {
                table: String,
                columns: Option<Vec<String>>,
                values: Vec<Vec<Expression>>,
            },
        for now im just going to store a single value
    */
    ExprPtrVariant values;

    explicit InsertStmt(ExprPtrVariant values);
};