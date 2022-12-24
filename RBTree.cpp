/**
 * @file RBTree.cpp
 * @author Yunus Emre Cakiroglu (cakiroglu19@itu.edu.tr)
 * @brief Function implementations of RBTree
 * @version 0.1
 * @date 2022-12-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "RBTree.h"
#include <iostream>

/**
 * @brief Constructor of RBTreeNode struct.
 * 
 * @param k value to hold.
 */
RBTreeNode::RBTreeNode(int k, std::string Metadata, int BurstTime){
    this->key = k;
    this->color = true; // Bool value to keep color data. True for Red, False for Black.
    this->Metadata = Metadata;
    this->BurstTime = BurstTime;

    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

/**
 * @brief Constructor of RBTree class.
 * 
 */
RBTree::RBTree(){
    this->root_ = nullptr;
}

/**
 * @brief Insert new node to tree given key value.
 * 
 * @param key value to hold in new node.
 */
void RBTree::Insert(int key, std::string metadata, int BurstTime){
    // Create the new node
    RBTreeNode *node = new RBTreeNode(key, metadata, BurstTime);

    // Find the correct position for the new node
    RBTreeNode *y = nullptr;
    RBTreeNode *x = root_;

    while (x != nullptr) {
        y = x;
        if (node->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;

    if (y == nullptr) {
        root_ = node;  // Tree was empty
    } else if (node->key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }

    // Rebalance the tree
    InsertFixup(node);
}

/**
 * @brief Return node with minimum key of sub-tree given node.
 * 
 * @param node with sub-tree.
 * @return RBTreeNode* 
 */
RBTreeNode* RBTree::Minimum(RBTreeNode *node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/**
 * @brief Return node with maximum key of sub-tree given node.
 * 
 * @param node with sub-tree.
 * @return RBTreeNode* 
 */
RBTreeNode* RBTree::Maximum(RBTreeNode *node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}
/**
 * @brief Helper function for DeleteFixup
 * Implementation of Psuedocode from CLRS
 * @param u node - 1
 * @param v node - 2
 */
void RBTree::Transplant(RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == nullptr) {
        root_ = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

/**
 * @brief Delete the first node with given key.
 * 
 * @param key value to match node.
 */
void RBTree::Delete(RBTreeNode *node) {

    if (node->parent == nullptr && node->left == nullptr && node->right == nullptr){ // Check if its only node in tree
        root_ = nullptr;
        return;  // Node with the given key not found
    } 

    RBTreeNode *y = node;
    RBTreeNode *x = nullptr;

    bool y_original_color = y->color;
    /**
     * @brief Implementation of Psuedocode from CLRS book.
     * 
     */
    if (node->left == nullptr) {
        x = node->right;
        Transplant(node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        Transplant(node, node->left);
    } else {
        y = Minimum(node->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            Transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        Transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    
    if (y_original_color == false) {
            DeleteFixup(x);
    }
}

/**
 * @brief Fix routine to meet RBTree rules.
 * 
 * @param node with sub-tree.
 */
void RBTree::DeleteFixup(RBTreeNode *node) {
    while (node != root_ && node->color == false) {
        if (node == node->parent->left) {
            RBTreeNode *w = node->parent->right;
        if (w->color == true) {
            // Case 1: w is red
            w->color = false;
            node->parent->color = true;
            RotateLeft(node->parent);
            w = node->parent->right;
        }
        if (w->left->color == false && w->right->color == false) {
            // Case 2: w is black and both of its children are black
            w->color = true;
            node = node->parent;
        } else {
            if (w->right->color == false) {
                // Case 3: w is black, w->left is red, and w->right is black
                w->left->color = false;
                w->color = true;
                RotateRight(w);
                w = node->parent->right;
            }
            // Case 4: w is black and w->right is red
            w->color = node->parent->color;
            node->parent->color = false;
            w->right->color = false;
            RotateLeft(node->parent);
            node = root_;
            }
        } else {
            RBTreeNode *w = node->parent->left;
            if (w->color == true) {
                // Case 1: w is red
                w->color = false;
                node->parent->color = true;
                RotateRight(node->parent);
                w = node->parent->left;
            }
            if (w->right->color == false && w->left->color == false) {
                // Case 2: w is black and both of its children are black
                w->color = true;
                node = node->parent;
            } else {
                if (w->left->color == false) {
                    // Case 3: w is black, w->right is red, and w->left is black
                    w->right->color = false;
                    w->color = true;
                    RotateLeft(w);
                    w = node->parent->left;
                }
                // Case 4: w is black and w->left is red
                w->color = node->parent->color;
                node->parent->color = false;
                w->left->color = false;
                RotateRight(node->parent);
                node = root_;
            }
        }
    }
    node->color = false;
}

void RBTree::InsertFixup(RBTreeNode *node) {
    // Fix violations of the red-black tree properties
    while (node != root_ && node->parent->color == true) {
        RBTreeNode *uncle = nullptr;
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == true) {
                // Case 1: uncle is red
                node->parent->color = false;
                uncle->color = false;
                node->parent->parent->color = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                // Case 2: uncle is black, node is a right child
                node = node->parent;
                RotateLeft(node);
                }
                // Case 3: uncle is black, node is a left child
                node->parent->color = false;
                node->parent->parent->color = true;
                RotateRight(node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == true) {
                // Case 1: uncle is red
                node->parent->color = false;
                uncle->color = false;
                node->parent->parent->color = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                // Case 2: uncle is black, node is a left child
                node = node->parent;
                RotateRight(node);
                }
                // Case 3: uncle is black, node is a right child
                node->parent->color = false;
                node->parent->parent->color = true;
                RotateLeft(node->parent->parent);
            }
        }
    }
    root_->color = false;  // The root should always be black
}

/**
 * @brief Search given key value through RBTree.
 * 
 * @param key value to search.
 * @return RBTreeNode* 
 */
RBTreeNode* RBTree::Search(int key) {
    RBTreeNode *node = root_;
    while (node != nullptr) {
    if (key == node->key) {
        return node;
        } else if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
  return nullptr;  // Node with the given key not found
}
/**
 * @brief Rotate RBTree of given root node to left.
 * 
 * @param node to rotate sub-tree.
 */
void RBTree::RotateLeft(RBTreeNode *node) {
    RBTreeNode *y = node->right;
    node->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        root_ = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

/**
 * @brief Rotate RBTree of given root node to right.
 * 
 * @param node to rotate sub-tree.
 */
void RBTree::RotateRight(RBTreeNode *node) {
    RBTreeNode *y = node->left;
    node->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        root_ = y;
    } else if (node == node->parent->right) {
        node->parent->right = y;
    } else {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}

RBTreeNode* RBTree::GetRoot(){
    return RBTree::root_;
}

void RBTree::PrintInOrder(std::ostream &os, RBTreeNode *node) {
    if (node == nullptr) return;
    PrintInOrder(os, node->left);
    os << node->Metadata << ":" << node->key << "-" << (node->color ? "Red" : "Black") << (node == this->root_ ? "," : ";");
    PrintInOrder(os, node->right);
}