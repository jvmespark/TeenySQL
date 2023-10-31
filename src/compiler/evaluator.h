/*
    the evaluator.
    extracts the information out of the parsed statements and executes them to the b-tree and virtual-machine
*/

#pragma once

#include <vector>

#include "compiler.h"
#include "../engine/btree.h"

class Evaluator {
    public:
        explicit Evaluator(BTree& p_btree);

        void evaluateStmts(std::vector<StmtPtrVariant> statements);
    private:
        // evaluate statements
        // what return type(?), do a bit more research
        void evaluateSingleStmt(const StmtPtrVariant& stmt);
        void evaluateInsert(const InsertStmtPtr& stmt);
        void evaluateSelect(const SelectStmtPtr& stmt);

        // evaluate expressions
        //static evaluateLiteralExpr(const LiteralExprPtr& expr);

        // data
        BTree& btree;
};