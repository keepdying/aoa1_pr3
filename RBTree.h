#ifndef RBTree_H
#define RBTree_H

#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief RBTreeNode struct template.
 * 
 */
struct RBTreeNode {
    int key;
    bool color;
    std::string Metadata;
    int BurstTime;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;

    RBTreeNode(int k, std::string metadata, int BurstTime);
};

/**
 * @brief RBTree class template.
 * 
 */
class RBTree {
    public:
    void Insert(int key, std::string metadata, int BurstTime);
    void Delete(RBTreeNode *node);
    RBTreeNode* GetRoot();
    RBTreeNode* Search(int key);
    RBTreeNode* Minimum(RBTreeNode *node);
    void PrintInOrder(std::ostream &os, RBTreeNode *node);
    RBTree();

    private:
    RBTreeNode *root_;
    void InsertFixup(RBTreeNode *node);
    void DeleteFixup(RBTreeNode *node);

    void RotateLeft(RBTreeNode *node);
    void RotateRight(RBTreeNode *node);

    void Transplant(RBTreeNode *u, RBTreeNode *v);

    RBTreeNode* Maximum(RBTreeNode *node);

};

#endif