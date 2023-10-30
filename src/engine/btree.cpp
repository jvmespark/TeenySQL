#include <iostream>

#include "engine.h"

/*
    BTreeNode
*/

BTreeNode::BTreeNode(int p_minDegree, bool leaf1) {
    minDegree = p_minDegree;
    leaf = leaf1;
 
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new Literal[2*minDegree-1];
    C = new BTreeNode *[2*minDegree];
 
    // Initialize the number of keys as 0
    n = 0;
}
 
void BTreeNode::traverse() {
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        std::cout << " " << getLiteralString(keys[i]);
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}
 
BTreeNode *BTreeNode::search(Literal k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;
 
    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;
 
    // Go to the appropriate child
    return C[i]->search(k);
}


// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(Literal k) {
    // Initialize index as index of rightmost element
    int i = n-1;
 
    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
 
        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    }
    else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;
 
        // See if the found child is full
        if (C[i+1]->n == 2*minDegree-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);
 
            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 
// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y) {
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->minDegree, y->leaf);
    z->n = minDegree - 1;
 
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < minDegree-1; j++)
        z->keys[j] = y->keys[j+minDegree];
 
    // Copy the last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < minDegree; j++)
            z->C[j] = y->C[j+minDegree];
    }
 
    // Reduce the number of keys in y
    y->n = minDegree - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
    // Link the new child to this node
    C[i+1] = z;
 
    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    // Copy the middle key of y to this node
    keys[i] = y->keys[minDegree-1];
 
    // Increment count of keys in this node
    n = n + 1;
}

/*
    BTree 
*/

BTree::BTree(int p_minDegree) {
    root = NULL;
    minDegree = p_minDegree;
}
 
// The main function that inserts a new key in this B-Tree
void BTree::insert(Literal k) {
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(minDegree, true);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*minDegree-1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(minDegree, false);
 
            // Make old root as child of new root
            s->C[0] = root;
 
            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
 
            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}
 
void BTree::traverse() {
    if (root != NULL) root->traverse();
}

BTreeNode* BTree::search(Literal k) {
    if (root != NULL) {
        return root->search(k);
    }
    return NULL;
}