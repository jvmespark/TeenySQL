// user interface with teenySQL

#include "core.h"
#include "../compiler/compiler.h"

void interface(std::string s) {
    if (s.empty()) {
        // create a REPL
        std::cout<<"REPL";  
    }
    else {
        // read file
        std::ifstream query("../"+s);
        std::string sql;
        if (query.is_open()) {
            while (query) {
                std::getline (query, sql);
                // parse the line. first i need to understand how a SQL compiler works. what are the tokens/groups?
                std::cout << sql << '\n';
            }
        }
        
        else {
            std::cout << "ERROR: couldn't open file\n";
        }
    }
}