/*
    core user interface with teenySQL
*/

#pragma once

#include "../engine/btree.h"

void interpret(std::string sql, BTree& btree);
void interface(std::string source);