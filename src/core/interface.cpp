#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  

#include "core.h"
#include "../compiler/compiler.h"

void interpret(std::string sql) {
    Scanner scanner(sql);
    std::vector<Token> tokenVec = scanner.tokenize();

    // NOTE: testing purposes
    for (int i = 0; i < tokenVec.size(); i++) {
        std::cout<<tokenVec[i].toString()<<std::endl;
    }

    /*
    Parser parser(tokenVec);
    std::vector<AST::StmtPrtVariant> statements = parser.parse();

    Evaluator evaluator;
    evaluator.evaluateStmts(statements);
    */
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