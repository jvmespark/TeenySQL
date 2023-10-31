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
        case 1: // select
            evaluateSelect(std::get<1>(stmt));
            break;
        default:
            std::cout<<"ERROR: EVALUATE STATEMENT: expansion limit"<<std::endl; 
            exit(1);
    }
}

// you can only insert a literal data type into the database, so there is not need to evaluate expression further than simple extraction
void Evaluator::evaluateInsert(const InsertStmtPtr& stmt) {
    ExprPtrVariant expr = std::move(stmt->values);
    if (std::get<LiteralExprPtr>(expr)->literalVal.has_value()) {
        Literal value = *std::move(std::get<LiteralExprPtr>(expr)->literalVal);
        btree.insert(value);
    }
}

void Evaluator::evaluateSelect(const SelectStmtPtr& stmt) {
    TokenType selectVal = std::move(stmt->selectVal);
    if (selectVal == TokenType::STAR) {
        btree.traverse();
        std::cout<<"\n";
    }
}

/*
    TODO
        NOTE TO DEV:
            at the evaluator and b-tree is where smart implementations start to fall apart
            so far i have a very very scrappy working prototype, but what i need to do is the following:
                <x> rebuild the b-tree so it can accept the AST data type Literal. adaptions need to be made to insert and way to traverse and print.
                
                <> add a new statement for SELECT *; which should just traverse and return the values in the tree
                <> add ability to UPDATE based on simple index

                <> after that, make it persistant to the disk and thats probably a wrap

    figure out what purpose a lox object gives me in terms of teenysql, what other expressions do sql rdms use?
    a lox object would let me insert a common data type into the b-tree rather than a literal,variable, etc. another way to package the data
*/