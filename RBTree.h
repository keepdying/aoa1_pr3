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
    std::string metaData;
    int timeToLive;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;

    RBTreeNode(int k, std::string metadata, int timeToLive);
};

/**
 * @brief RBTree class template.
 * 
 */
class RBTree {
    public:
    void Insert(int key, std::string metadata, int timetolive);
    void Delete(RBTreeNode *node);
    RBTreeNode* GetRoot();
    RBTreeNode* Search(int key);
    RBTreeNode* Minimum(RBTreeNode *node);

    private:
    RBTreeNode *root_;
    void InsertFixup(RBTreeNode *node);
    void DeleteFixup(RBTreeNode *node);

    void RotateLeft(RBTreeNode *node);
    void RotateRight(RBTreeNode *node);

    void Transplant(RBTreeNode *u, RBTreeNode *v);

    RBTreeNode* Maximum(RBTreeNode *node);

    // RBTreeNode* Successor(RBTreeNode *node);
    // RBTreeNode* Predecessor(RBTreeNode *node);
};

#endif