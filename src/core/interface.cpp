#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <vector>
#include <variant>
#include <string>

#include "core.h"
#include "../compiler/compiler.h"
#include "../engine/engine.h"

void interpret(std::string sql) {
    Scanner scanner(sql);
    std::vector<Token> tokenVec = scanner.tokenize();

    // NOTE: testing purposes
    for (int i = 0; i < tokenVec.size(); i++) {
        std::cout<<"TESTING: "<<tokenVec[i].toString()<<std::endl;
    }

    Parser parser(tokenVec);
    std::vector<StmtPtrVariant> statements = parser.parse();

    // NOTE: testing purposes
    for (int i = 0; i < statements.size(); i++) {
        StmtPtrVariant* stmt = &statements[i];
        // really complicated right now, but thats because this isnt the usual way you would breakdown statements
        // this would get passed to the evaulator
        // and based on the variant index it would be switch cased (insert,...)
        // from there the abstraction gets smaller (hopefully)
        Literal v = *std::move(std::get<LiteralExprPtr>(std::get<InsertStmtPtr>(*stmt)->values)->literalVal);
        std::cout<<"TESTING: "<<getLiteralString(v)<<std::endl;
    }   
        
    BTree btree(3);
    Evaluator evaluator(btree);
    evaluator.evaluateStmts(std::move(statements));

    // NOTE: testing purposes
    std::cout<<"TESTING: \n";
    btree.traverse();
}

void interface(std::string source) {
    // TODO print a console title 
    // TODO meta commands
    if (source=="REPL") {
        // REPL  
        std::string line;
        while (std::cout << "> " && std::getline(std::cin, line)) {
            interpret(line);
        }
    }
    else {
        // read script
        std::ifstream script("../"+source);
        
        if (!script.good()) {
            std::cout << "ERROR: couldn't open file\n";
            exit(1);
        }

        std::stringstream buffer;
        buffer << script.rdbuf();
        std::string sql = buffer.str();

        interpret(sql);
    }
}