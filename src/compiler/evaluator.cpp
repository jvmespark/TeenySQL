#include "evaluator.h"
#include <iostream>

void Evaluator::evaluateStmts(std::vector<StmtPtrVariant> statements) {
    // TODO : return optional not void
    for (const StmtPtrVariant& stmt : statements) {
        evaluateSingleStmt(stmt);
    }
}

void Evaluator::evaluateSingleStmt(const StmtPtrVariant& stmt) {
    switch (stmt.index()) {
        case 0: // insert
            //evaluateInsert(std::get<0>(stmt));
            std::cout<<"INSERT"<<std::endl;
            break;
        default:
            std::cout<<"ERROR: EVALUATE STATEMENT: expansion limit"<<std::endl; 
            exit(1);
    }
}

/*
void Evaluator::evaluteInsert(const InsertStmtPtr& stmt) {
    value_to_insert = evaluateExpr(stmt->values);
    insert();
}
*/