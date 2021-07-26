#include <stddef.h>

#include "tree.h"

//二叉树的前序遍历递归算法
void preOrderTraverse(BiTree T, void (*operate)(TElemType data)) {
    if (T == NULL) { return; }
    if (operate) { operate(T->data); }
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

//二叉树的中序遍历递归算法
void inOrderTraverse(BiTree T, void (*operate)(TElemType data)) {
    if (T == NULL) { return; }
    InOrderTraverse(T->lchild);
    if (operate) { operate(T->data); }
    InOrderTraverse(T->rchild);
}

//二叉树的后序遍历递归算法
void postOrderTraverse(BiTree T, void (*operate)(TElemType data)) {
    if (T == NULL) { return; }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    if (operate) { operate(T->data); }
}







// /* 按前序输入二叉树中结点的值（一个字符） */
// /* #表示空树，构造二叉链表表示二叉树T。 */
// void CreateBiTree(BiTree* T) {
//     TElemType ch;
//     scanf("%c", &ch);
//     if (ch == '#')
//         *T = NULL;
//     else {
//         *T = (BiTree)malloc(sizeof(BiTNode));
//         if (!*T)
//             exit(OVERFLOW);
//         /* 生成根结点 */
//         (*T)->data = ch;
//         /* 构造左子树 */
//         CreateBiTree(&(*T)->lchild);
//         /* 构造右子树 */
//         CreateBiTree(&(*T)->rchild);
//     }
// }

// /* 二叉树的二叉线索存储结构定义 */
// /* Link==0表示指向左右孩子指针 */
// /* Thread==1表示指向前驱或后继的线索 */
// typedef enum { Link,
//                Thread } PointerTag;
// /* 二叉线索存储结点结构 */
// typedef struct BiThrNode {
//     /* 结点数据 */
//     TElemType data;
//     /* 左右孩子指针 */
//     struct BiThrNode *lchild, *rchild;
//     PointerTag        LTag;
//     /* 左右标志 */
//     PointerTag RTag;
// } BiThrNode, *BiThrTree;

// BiThrTree pre; /* 全局变量，始终指向刚刚访问过的结点 */
// /* 中序遍历进行中序线索化 */
// void InThreading(BiThrTree p) {
//     if (p) {
//         /* 递归左子树线索化 */
//         InThreading(p->lchild);
//         /* 没有左孩子 */
//         if (!p->lchild) {
//             /* 前驱线索 */
//             p->LTag = Thread;
//             /* 左孩子指针指向前驱 */
//             p->lchild = pre;
//         }
//         /* 前驱没有右孩子 */
//         if (!pre->rchild) {
//             /* 后继线索 */
//             pre->RTag = Thread;
//             /* 前驱右孩子指针指向后继（当前结点p） */
//             pre->rchild = p;
//         }
//         /* 保持pre指向p的前驱 */
//         pre = p;
//         /* 递归右子树线索化 */
//         InThreading(p->rchild);
//     }
// }

// /* T指向头结点，头结点左链lchild指向根结点，
//    头结点右链rchild指向中序遍历的 */
// /* 最后一个结点。中序遍历二叉线索链表表示的二
//    叉树T */
// Status InOrderTraverse_Thr(BiThrTree T) {
//     BiThrTree p;
//     /* p指向根结点 */
//     p = T->lchild;
//     /* 空树或遍历结束时，p==T */
//     while (p != T) {
//         /* 当LTag==0时循环到中序序列第一个结点 */
//         while (p->LTag == Link)
//             p = p->lchild;
//         /* 显示结点数据，可以更改为其他对结点操作 */
//         printf("%c", p->data);
//         while (p->RTag == Thread && p->rchild != T) {
//             p = p->rchild;
//             printf("%c", p->data);
//         }
//         /* p进至其右子树根 */
//         p = p->rchild;
//     }
//     return OK;
// }