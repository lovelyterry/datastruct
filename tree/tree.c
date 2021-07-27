#include <stddef.h>

#include "tree.h"

//二叉树的前序遍历递归算法
void preOrderTraverse(BiTree T, void (*operate)(TElemType* data)) {
    if (T == NULL) { return; }
    if (operate) { operate(&(T->data)); }
    preOrderTraverse(T->lchild, operate);
    preOrderTraverse(T->rchild, operate);
}

//二叉树的中序遍历递归算法
void inOrderTraverse(BiTree T, void (*operate)(TElemType* data)) {
    if (T == NULL) { return; }
    inOrderTraverse(T->lchild, operate);
    if (operate) { operate(&(T->data)); }
    inOrderTraverse(T->rchild, operate);
}

//二叉树的后序遍历递归算法
void postOrderTraverse(BiTree T, void (*operate)(TElemType* data)) {
    if (T == NULL) { return; }
    postOrderTraverse(T->lchild, operate);
    postOrderTraverse(T->rchild, operate);
    if (operate) { operate(&(T->data)); }
}

//二叉树的层序遍历递归算法
void floorOrderTraverse(BiTree T, void (*operate)(TElemType* data)) {
    if (T == NULL) { return; }
    //二叉树最多10层 2^10 = 1024
#define queueDepth 1024
    BiTree biTreeQueue[queueDepth + 1] = {};
    int    front                       = 0;
    int    rear                        = 0;

    biTreeQueue[rear] = T;
    rear              = ++rear % queueDepth;
    while ((rear - front + queueDepth) % queueDepth != 0) {
        if (operate) { operate(&(biTreeQueue[front]->data)); }
        if (biTreeQueue[front]->lchild != NULL) {
            biTreeQueue[rear] = biTreeQueue[front]->lchild;
            rear              = ++rear % queueDepth;
        }
        if (biTreeQueue[front]->rchild != NULL) {
            biTreeQueue[rear] = biTreeQueue[front]->rchild;
            rear              = ++rear % queueDepth;
        }
        front = ++front % queueDepth;
    }
}

static BiThrTree preNode;

static void inOrderThreadingImpl(BiThrTree T) {
    if (T == NULL) { return; }
    inOrderThreadingImpl(T->lchild);
    //如果当前节点的左子树为空，则令之左指针指向上一个节点
    if (T->lchild == NULL) {
        T->lTag   = Thread;
        T->lchild = preNode;
    }
    //如果上上一个节点的右子树为空，则令之右指针指向当前节点
    if (preNode != NULL && preNode->rchild == NULL) {
        preNode->rTag   = Thread;
        preNode->rchild = T;
    }
    preNode = T;
    //将当前节点作为上"右节点或右节点的左节点"的上一个节点
    inOrderThreadingImpl(T->rchild);
}

void inOrderThreading(BiThrTree* headNode, BiThrTree T) {
    *headNode = (BiThrTree)malloc(sizeof(BiThrNode));
    //如果树本身是空树
    if (T == NULL) {
        (*headNode)->rchild = *headNode;
        (*headNode)->rTag   = Link;
        (*headNode)->lchild = *headNode;
        (*headNode)->lTag   = Link;
    } else {
        //头结点左孩子设为树根结点
        (*headNode)->lchild = T;
        (*headNode)->lTag   = Link;
        preNode             = headNode;
        //线索化二叉树，preNode作为全局变量，线索化结束后，preNode指向中序序列中最后一个结点
        inOrderThreadingImpl(T);
        preNode->rchild     = *headNode;
        preNode->rTag       = Thread;
        (*headNode)->rchild = preNode;
    }
}

void inOrderTraverseBiThrTree(BiThrTree T, void (*operate)(TElemType* data)) {
    BiThrTree p;
    p = T->lchild;
    while (p != T) {
        while (p->lTag == Link) { p = p->lchild; }
        if (operate) { operate(&(p->data)); }
        while (p->rTag == Thread && p->rchild != T) {
            p = p->rchild;
            if (operate) { operate(&(p->data)); }
        }
        p = p->rchild;
    }
}
