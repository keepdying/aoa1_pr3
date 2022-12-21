#ifndef RBTree_H
#define RBTree_H

#include <string>

/**
 * @brief RBTreeNode struct template.
 * 
 */
struct RBTreeNode {
    int key;
    bool color;
    std::string metadata;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;

    RBTreeNode(int k);
};

/**
 * @brief RBTree class template.
 * 
 */
class RBTree {
    public:
    void Insert(int key);
    void Delete(int key);
    RBTreeNode* Search(int key);

    private:

    RBTreeNode *root_;
    void InsertFixup(RBTreeNode *node);
    void DeleteFixup(RBTreeNode *node);

    void RotateLeft(RBTreeNode *node);
    void RotateRight(RBTreeNode *node);

    void Transplant(RBTreeNode *u, RBTreeNode *v);

    RBTreeNode* Minimum(RBTreeNode *node);
    RBTreeNode* Maximum(RBTreeNode *node);

    RBTreeNode* Successor(RBTreeNode *node);
    RBTreeNode* Predecessor(RBTreeNode *node);
    
};

#endif