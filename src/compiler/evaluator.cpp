#include <iostream>
#include <variant>

#include "evaluator.h"

Evaluator::Evaluator(BTree& p_btree)
    : btree(p_btree) {}

void Evaluator::evaluateStmts(std::vector<StmtPtrVariant> statements) {
    // TODO : return optional not void
    for (const StmtPtrVariant& stmt : statements) {
        evaluateSingleStmt(stmt);
    }
}

void Evaluator::evaluateSingleStmt(const StmtPtrVariant& stmt) {
    switch (stmt.index()) {
        case 0: // insert
            evaluateInsert(std::get<0>(stmt));
            break;
        default:
            std::cout<<"ERROR: EVALUATE STATEMENT: expansion limit"<<std::endl; 
            exit(1);
    }
}

void Evaluator::evaluateInsert(const InsertStmtPtr& stmt) {
    // TODO brute force method here to extract data, not good...or is it(?)
    Literal value = *std::move(std::get<LiteralExprPtr>(stmt->values)->literalVal);
    //    std::cout<<getLiteralString(v)<<std::endl;
    //LiteralExprPtr values = evaluateExpr(stmt->values);
    btree.insert((int)std::get<1>(value));
}