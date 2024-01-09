/*
    balanced tree implementation for indexing
*/

#pragma once

#include "../compiler/AST.h"
 
class BTreeNode {
    public:
        BTreeNode(int p_minDegree, bool _leaf);
    
        // A utility function to insert a new key in the subtree rooted with
        // this node. The assumption is, the node must be non-full when this
        // function is called
        void insertNonFull(Literal k);
    
        // A utility function to split the child y of this node. i is index of y in
        // child array C[].  The Child y must be full when this function is called
        void splitChild(int i, BTreeNode *y);

        void traverse();    
        BTreeNode *search(Literal k);

    friend class BTree;

    private:
        Literal *keys;
        int minDegree;
        BTreeNode **C; // An array of child pointers
        int n;     // Current number of keys
        bool leaf; // Is true when node is leaf. Otherwise false
};
 
// A BTree
class BTree {
    public:
        BTree(int p_minDegree);
    
        void traverse();
        BTreeNode* search(Literal k);
        void insert(Literal k);

    private:
        BTreeNode *root;
        int minDegree;
};