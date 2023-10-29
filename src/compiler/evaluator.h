/*
    the evaluator.
    turns the parsed statements and executes them to the b-tree and machine
*/

#pragma once

#include <vector>
#include "compiler.h"

class Evaluator {
    public:
        void evaluateStmts(std::vector<StmtPtrVariant> statements);
    private:
        // evaluate statements
        // what return type(?), do a bit more research
        void evaluateSingleStmt(const StmtPtrVariant& stmt);
        //evaluateInsertStmt(const InsertStmtPtr& stmt);

        // evaluate expressions
        // static evaluateLiteralExpr(const LiteralExprPtr& expr);
};