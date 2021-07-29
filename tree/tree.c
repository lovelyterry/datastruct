#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

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
    ++rear;
    rear = rear % queueDepth;
    while ((rear - front + queueDepth) % queueDepth != 0) {
        if (operate) { operate(&(biTreeQueue[front]->data)); }
        if (biTreeQueue[front]->lchild != NULL) {
            biTreeQueue[rear] = biTreeQueue[front]->lchild;
            ++rear;
            rear = rear % queueDepth;
        }
        if (biTreeQueue[front]->rchild != NULL) {
            biTreeQueue[rear] = biTreeQueue[front]->rchild;
            ++rear;
            rear = rear % queueDepth;
        }
        ++front;
        front = front % queueDepth;
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
    } else {
        T->lTag = Link;
    }
    //如果上上一个节点的右子树为空，则令之右指针指向当前节点
    if (preNode != NULL && preNode->rchild == NULL) {
        preNode->rTag   = Thread;
        preNode->rchild = T;
    } else {
        preNode->rTag = Link;
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
        preNode             = *headNode;
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

// Huffman Tree
//HT数组中存放的哈夫曼树，size表示HT数组的大小，index1和index2为树中最小的两个节点索引
static void selectMin2(HuffmanTree HT, int size, int* index1, int* index2) {
    int min1, min2;
    //遍历数组初始下标为 0
    int i = 0;
    //找到还没构建树的结点
    while (HT[i].parent != -1 && i < size) { i++; }
    min1    = HT[i].weight;
    *index1 = i;
    i++;
    while (HT[i].parent != -1 && i < size) { i++; }
    //对找到的两个结点比较大小，min2为大的，min1为小的
    if (HT[i].weight < min1) {
        min2    = min1;
        *index2 = *index1;
        min1    = HT[i].weight;
        *index1 = i;
    } else {
        min2    = HT[i].weight;
        *index2 = i;
    }
    //两个结点和后续的所有未构建成树的结点做比较
    for (int j = i + 1; j < size; j++) {
        if (HT[j].parent != -1) { continue; }
        if (HT[j].weight < min1) {
            min2    = min1;
            min1    = HT[j].weight;
            *index2 = *index1;
            *index1 = j;
        } else if (HT[j].weight < min2) {
            min2    = HT[j].weight;
            *index2 = j;
        }
    }
}

//HT为地址传递的存储哈夫曼树的数组，w为存储结点权重值的数组，n为结点个数
void createHuffmanTree(HuffmanTree* HT, int* w, int n) {
    if (n <= 1) { return; }  // 如果只有一个编码就相当于0
    int m = 2 * n - 1;       // 哈夫曼树总节点数，n就是叶子结点
    *HT   = (HuffmanTree)malloc((m) * sizeof(HTNode));
    memset(*HT, 0, (m) * sizeof(HTNode));
    // 初始化哈夫曼树中的所有结点
    for (int i = 0; i < n; i++) {
        (*HT + i)->weight = *(w + i);
        (*HT + i)->parent = -1;
        (*HT + i)->left   = -1;
        (*HT + i)->right  = -1;
    }
    //从树组的下标 n 开始初始化哈夫曼树中除叶子结点外的结点
    for (int i = n; i < m; i++) {
        (*HT + i)->weight = 0;
        (*HT + i)->parent = -1;
        (*HT + i)->left   = -1;
        (*HT + i)->right  = -1;
    }
    //构建哈夫曼树
    for (int i = n; i < m; i++) {
        int index1, index2;
        selectMin2(*HT, i, &index1, &index2);
        (*HT)[index1].parent = i;
        (*HT)[index2].parent = i;
        (*HT)[i].left        = index1;
        (*HT)[i].right       = index2;
        (*HT)[i].weight      = (*HT)[index1].weight + (*HT)[index2].weight;
    }
}

//HT为哈夫曼树，HC为存储结点哈夫曼编码的二维动态数组，n为结点的个数
//从叶子结点一直找到根结点，逆向记录途中经过的标记。
void huffmanCoding(HuffmanTree HT, HuffmanCode* HC, int n) {
    *HC            = (HuffmanCode)malloc(n * sizeof(char*));
    char* codeStr  = (char*)malloc(n * sizeof(char));  //存放结点哈夫曼编码的字符串数组
    codeStr[n - 1] = '\0';                             //字符串结束符
    for (int i = 0; i < n; i++) {
        //从叶子结点出发，得到的哈夫曼编码是逆序的，需要在字符串数组中逆序存放
        int start = n - 1;
        //当前结点在数组中的位置
        int c = i;
        //当前结点的父结点在数组中的位置
        int j = HT[i].parent;
        // 一直寻找到根结点
        while (j != -1) {
            // 如果该结点是父结点的左孩子则对应路径编码为0，否则为右孩子编码为1
            if (HT[j].left == c) {
                codeStr[--start] = '0';
            } else {
                codeStr[--start] = '1';
            }
            //以父结点为孩子结点，继续朝树根的方向遍历
            c = j;
            j = HT[j].parent;
        }
        //跳出循环后，cd数组中从下标 start 开始，存放的就是该结点的哈夫曼编码
        (*HC)[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy((*HC)[i], &codeStr[start]);
    }
    free(codeStr);
}

static int count = 0;

//检测棋子放在第row行第column列是否成功
static bool checkPlaceOK(int* chessboard, int row, int column) {
    for (int i = 0; i < row; ++i) {
        //遍历已经放置完成，同一行只放置了一个，所以不可能存在冲突
        //检测是否存在棋子是否在同一列，column+-row和chessboard[i] +- i相等表示在同一对角线上（行列之差的绝对值）
        if (chessboard[i] == column || chessboard[i] - i == column - row || chessboard[i] + i == column + row) {
            return false;
        }
    }
    return true;
}

static void printSolution(int* chessboard, const int boardSize) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            printf((chessboard[i] == j ? "O " : "- "));
        }
        printf("\r\n");
    }
    printf("\r\n");
}

static void addQueen(int* chessboard, const int boardSize, int row) {
    if (row < boardSize) {
        for (int column = 0; column < boardSize; ++column) {
            if (checkPlaceOK(chessboard, row, column)) {
                chessboard[row] = column;
                addQueen(chessboard, boardSize, row + 1);
            }
        }
    } else {
        count++;
        if (boardSize <= 8) {
            printSolution(chessboard, boardSize);
        }
    }
}

int calculteQueenSolution(int* chessboard, const int boardSize) {
    addQueen(chessboard, boardSize, 0);
    return count;
}