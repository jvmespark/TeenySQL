/*
    parser to turn scanned tokens into an abstract syntax tree nodetype representation
    top down recursive descent parser implementation

    goes through and logically matches and groups tokens and stores them in a AST pointer type with all necessary information

    in parser:
        consume blocks of grouped info and make them into AST node. return a vector of all these ptrs after.

    in AST nodes:
        ultimately they are structs and you fill in the info. then make you pointer of that struct type
            ex: expressions and statements
                literal is an expr, insert is a statement. etc.

*/

#pragma once

#include <vector>

#include "./types/literal.h"
#include "./types/token.h"
#include "AST.h"

class Parser {
    public:
    private:
};