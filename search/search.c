#include "search.h"

#include <stddef.h>
#include <stdlib.h>

int sequentialSearch(int array[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (array[i] == key) { return i; }
    }
    return -1;
}

int binarySearch(int array[], int size, int key) {
    int start = 0;
    int end   = size - 1;
    //最后start < key, end > key
    while (start <= end) {
        int mid = (start + end) / 2;
        if (key < array[mid]) {
            end = mid - 1;
        } else if (key > array[mid]) {
            start = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

//二叉排序树查找算法
bool searchBiTree(BiTree T, TElemType key, BiTree parent, BiTree* finaly) {
    //如果 T 指针为空，说明查找失败，令finaly指针指向查找过程中最后一个叶子结点，并返回查找失败的信息
    if (T == NULL) {
        *finaly = parent;
        return false;
    } else if (key == T->data) {
        *finaly = T;
        return true;
    } else if (key < T->data) {
        return searchBiTree(T->lchild, key, T, finaly);
    } else {
        return searchBiTree(T->rchild, key, T, finaly);
    }
}

bool insertBiTree(BiTree* T, TElemType e) {
    //用于存储查找过程中的最后一个节点
    BiTree finaly = NULL;
    if (!searchBiTree((*T), e, NULL, &finaly)) {
        BiTree newNode  = (BiTree)malloc(sizeof(BiNode));
        newNode->data   = e;
        newNode->lchild = NULL;
        newNode->rchild = NULL;
        if (finaly == NULL) {
            (*T) = newNode;
        } else if (e < finaly->data) {
            finaly->lchild = newNode;
        } else {
            finaly->rchild = newNode;
        }
        return true;
    } else {
        //数据已经存在，这里不做处理
        return false;
    }
}

bool deleteBiTree(BiTree* T) {
    if ((*T) == NULL) { return false; }
    if ((*T)->lchild == NULL && (*T)->rchild == NULL) {
        //情况 1，节点(*T) 本身为叶子结点，直接删除即可
        free((*T));
        (*T) = NULL;
    } else if (!(*T)->lchild) {
        //左子树为空，只需用节点T 的右子树根结点代替节点T 即可
        BiTree oldTree = (*T);
        (*T)           = (*T)->rchild;
        free(oldTree);
    } else if (!(*T)->rchild) {
        //右子树为空，只需用节点(*T) 的左子树根结点代替节点(*T) 即可
        BiTree oldTree = (*T);
        (*T)           = (*T)->lchild;
        free(oldTree);
    } else {
        //左右子树均不为空,q用来保存前驱的双亲节点，s用来保存前驱
        BiTree q = (*T);
        BiTree s = (*T)->lchild;
        //遍历，找到节点(*T) 的直接前驱
        while (s->rchild) {
            q = s;
            s = s->rchild;
        }
        (*T)->data = s->data;
        //判断结点 (*T) 的左子树不是是s(q == (*T) ?)，把s的左子树系到(*T) 右子树上
        //否则，那么把s的左子树系到(*T) 的左子树上
        if (q != (*T)) {
            q->rchild = s->lchild;
        } else {
            q->lchild = s->lchild;
        }
        free(s);
    }
    return true;
}

bool deleteBiTreeByKey(BiTree* T, TElemType key) {
    if ((*T) == NULL) {
        return false;
    } else {
        if (key == (*T)->data) {
            return deleteBiTree(T);
        } else if (key < (*T)->data) {
            return deleteBiTreeByKey(&((*T)->lchild), key);
        } else {
            return deleteBiTreeByKey(&((*T)->rchild), key);
        }
    }
}

//===========================================================

#define LH (+1) /* 左子树高 */
#define EQ (0)  /* 等高 */
#define RH (-1) /* 右子树高 */

//对二叉排序树作右旋处理
//处理之后root指向新的树根结点，即旋转处理之前的左子树的根结点
//右旋就是以某节点的左节点为中心进行向右的旋转，取代并成为之前自己的父节点，然后把之前的父节点变为自己的右子节点
static void rightRotate(AvlTree* root) {
    //L指向root的左子树根节点
    AvlTree L = (*root)->lchild;
    /* L的右子树挂接为root的左子树 */
    (*root)->lchild = L->rchild;
    L->rchild       = (*root);
    *root           = L;
}

//对二叉排序树作左旋处理
//处理之后root指向新的树根结点，即旋转处理之前的右子树的根结点
//左旋就是以某节点的右节点为中心进行向左的旋转，取代并成为之前自己的父节点，然后把之前的父节点变为自己的左子节点
static void leftRotate(AvlTree* root) {
    //L指向root的左子树根节点
    AvlTree R = (*root)->rchild;
    /* L的右子树挂接为root的左子树 */
    (*root)->rchild = R->lchild;
    R->lchild       = (*root);
    *root           = R;
}

//对以指针root所指结点为根的二叉树作左平衡旋转处理
//本算法结束时，指针root指向新的根节点
static void leftBalance(AvlTree* root) {
    AvlTree L = (*root)->lchild;
    if (L->balanceFactor == EQ) {
        return;
    } else if (L->balanceFactor == LH) {
        //检查T的左子树的平衡度，并作相应平衡处理，新结点插入在T的左孩子的左子树上，要作单右旋处理
        (*root)->balanceFactor = EQ;
        L->balanceFactor       = EQ;
        rightRotate(root);
    } else {
        //新结点插入在T的左孩子的右子树上，要作双旋处理，Lr指向T的左孩子的右子树
        AvlTree Lr = L->rchild;
        //修改root及其左孩子的平衡因子
        switch (Lr->balanceFactor) {
        case LH: {
            (*root)->balanceFactor = RH;
            L->balanceFactor       = EQ;
            break;
        }
        case EQ: {
            (*root)->balanceFactor = EQ;
            L->balanceFactor       = EQ;
            break;
        }
        case RH: {
            (*root)->balanceFactor = EQ;
            L->balanceFactor       = LH;
            break;
        }
        }
        Lr->balanceFactor = EQ;
        leftRotate(&(*root)->lchild);
        rightRotate(root);
    }
}

//对以指针root所指结点为根的二叉树作左平衡旋转处理
//本算法结束时，指针root指向新的根节点
static void rightBalance(AvlTree* root) {
    AvlTree R = (*root)->rchild;
    if (R->balanceFactor == EQ) {
        return;
    } else if (R->balanceFactor == RH) {
        //检查T的右子树的平衡度，并作相应平衡处理，新结点插入在T的右孩子的右子树上，要作单左旋处理
        (*root)->balanceFactor = EQ;
        R->balanceFactor       = EQ;
        leftRotate(root);
    } else {
        //新结点插入在T的右孩子的左子树上，要作双旋处理，Lr指向T的左孩子的右子树
        AvlTree Rl = R->lchild;
        //修改T及其左孩子的平衡因子
        switch (Rl->balanceFactor) {
        case LH: {
            (*root)->balanceFactor = EQ;
            R->balanceFactor       = RH;
            break;
        }
        case EQ: {
            (*root)->balanceFactor = EQ;
            R->balanceFactor       = EQ;
            break;
        }
        case RH: {
            (*root)->balanceFactor = EQ;
            R->balanceFactor       = LH;
            break;
        }
        }
        Rl->balanceFactor = EQ;
        rightRotate(&(*root)->rchild);
        leftRotate(root);
    }
}

//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入，否则直接返回
//数据元素为e的新结点。若因插入而使二叉排序树失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否
int insertAvlTree(AvlTree* T, int e, bool* taller) {
    if (*T == NULL) {
        *T                  = (AvlTree)malloc(sizeof(AvlTNode));
        (*T)->lchild        = NULL;
        (*T)->rchild        = NULL;
        (*T)->balanceFactor = EQ;
        (*T)->data          = e;
        *taller             = true;
    } else {
        if (e == (*T)->data) {
            *taller = false;
            return false;
        }
        if (e < (*T)->data) {
            if (!insertAvlTree(&(*T)->lchild, e, taller)) {
                return false;
            } else if (*taller) {
                switch ((*T)->balanceFactor) {
                case LH: {
                    leftBalance(T);
                    *taller = false;
                    break;
                }
                case EQ: {
                    (*T)->balanceFactor = LH;
                    *taller             = true;
                    break;
                }
                case RH: {
                    (*T)->balanceFactor = EQ;
                    *taller             = false;
                    break;
                }
                }
            }
        } else {
            if (!insertAvlTree(&(*T)->rchild, e, taller)) {
                return false;
            } else if (*taller) {
                switch ((*T)->balanceFactor) {
                case LH: {
                    (*T)->balanceFactor = EQ;
                    *taller             = false;
                    break;
                }
                case EQ: {
                    (*T)->balanceFactor = RH;
                    *taller             = true;
                    break;
                }
                case RH: {
                    rightBalance(T);
                    *taller = false;
                    break;
                }
                }
            }
        }
    }
    return true;
}


//散列表查找算法
typedef struct HashTable {
    int* elem;
    int count;
} HashTable;

int m = 0;

//这个哈希算表算法真的太low了，冲突处理用的是往后移动，且没有rehash，都不想拿出去，看看就行了

#define NULLKEY (0x0FFFFFFF)

void initHashTable(HashTable* H) {
    m        = 1024;
    H->count = m;
    H->elem  = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) { H->elem[i] = NULLKEY; }
}

int hash(int key) {
    return key % m;
}

void insertHash(HashTable* H, int key) {
    int addr = hash(key);
    while (H->elem[addr] != NULLKEY) { addr = (addr + 1) % m; }
    H->elem[addr] = key;
}

bool searchHash(HashTable H, int key, int* addr) {
    *addr = hash(key);
    while (H.elem[*addr] != key) {
        *addr = (*addr + 1) % m;
        // 如果循环回到原点,则说明关键字不存在
        if (H.elem[*addr] == NULLKEY || *addr == hash(key)) {
            return false;
        }
    }
    return true;
}
