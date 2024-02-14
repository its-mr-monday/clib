#ifndef BINTREE_H
#define BINTREE_H
#pragma once

typedef struct BinTreeNode {
    int data;
    struct BinTreeNode *left;
    struct BinTreeNode *right;
} BinTreeNode;

typedef struct BinTree {
    BinTreeNode *root;
} BinTree;

BinTree * malloc_bintree();
void free_bintree(BinTree *tree);

BinTreeNode* tree_getroot(BinTree *tree);
void tree_add(BinTree *tree, int data);
void tree_remove(BinTree *tree, int data);
BinTreeNode* tree_find(BinTree *tree, int data);
void tree_print(BinTree *tree);
#endif
