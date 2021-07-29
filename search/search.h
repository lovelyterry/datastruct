#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "tree/tree.h"

#include <stdbool.h>

int sequentialSearch(int array[], int size, int key);
int binarySearch(int array[], int size, int key);

bool searchBiTree(BiTree T, TElemType key, BiTree parent, BiTree* finaly);
bool insertBiTree(BiTree* T, TElemType e);
bool deleteBiTree(BiTree* T);
bool deleteBiTreeByKey(BiTree* T, TElemType key);

//AVL二叉树节点定义
typedef struct AvlTNode {
    TElemType        data;
    struct AvlTNode *lchild, *rchild;
    int              balanceFactor;
} AvlTNode, *AvlTree;

int insertAvlTree(AvlTree* T, int e, bool* taller);

#ifdef __cplusplus
}
#endif
//二叉树的二叉链表结点结构定义
