#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ADT 树(tree)
// Data
//     树是由一个根结点和若干棵子树构成。树中结点具有相同数据类型及层次关系。
// Operation
//     InitTree(*T):               构造空树T。
//     DestroyTree(*T):            销毁树T。
//     CreateTree(*T, definition): 按definition中给出树的定义来构造树。
//     ClearTree(*T):              若树T存在，则将树T清为空树。
//     TreeEmpty(T):               若T为空树，返回true，否则返回false。
//     TreeDepth(T):               返回T的深度。
//     Root(T):                    返回T的根结点。
//     Value(T, cur_e):            cur_e是树T中一个结点，返回此结点的值。
//     Assign(T, cur_e, value):    给树T的结点cur_e赋值为value。
//     Parent(T, cur_e):           若cur_e是树T的非根结点，则返回它的双亲，否则返回空。
//     LeftChild(T, cur_e):        若cur_e是树T的非叶结点，则返回它的最左孩子，否则返回空。
//     RightSibling(T, cur_e):     若cur_e有右兄弟，则返回它的右兄弟，否则返回空。
//     InsertChild(*T, *p, i, c):  其中p指向树T的某个结点，i为所指结点p的度加上1，
//                                 非空树c与T不相交，操作结果为插入c为树T中p指结点的第i棵子树。
//     DeleteChild(*T, *p, i):     其中p指向树T的某个结点，i为所指结点p的度，
//                                 操作结果为删除T中p所指结点的第i棵子树。
// endADT

//-----------------------------------------------------------------------

// 1. 二叉树中，第 i 层最多有 2^(i-1) 个结点。
// 2. 如果二叉树的深度为 K，那么此二叉树最多有 2^(K)-1 个结点。
// 3. 二叉树中，终端结点数（叶子结点数）为 n0，度为 2 的结点数为 n2，则 n0=n2+1。
// 4. 具有n个结点的完全二叉树的深度为|log2(n+1)|（|x|表示不大于x的最大整数）

//      性质 3 的计算方法为：对于一个二叉树来说，除了度为 0 的叶子结点和度为 2 的结点，
//      剩下的就是度为 1 的结点（设为 n1），那么总结点 n=n0+n1+n2。 同时，对于每一个
//      结点来说都是由其父结点分支表示的，假设树中分枝数为 B，那么总结点数 n=B+1。而分
//      枝数是可以通过 n1 和 n2 表示的，即 B=n1+2*n2。所以，n 用另外一种方式表示为 
//      n=n1+2*n2+1。两种方式得到的 n 值组成一个方程组，就可以得出 n0=n2+1。

// 性质5：如果对一棵有n个结点的完全二叉树（其深度为）的结点按层序编号（从第1层到第n层，每层从左到右），对任一结点i（1≤i≤n）有：
// 1．如果i=1，则结点i是二叉树的根，无双亲；如果i>1，则其双亲是结点。
// 2．如果2i>n，则结点i无左孩子（结点i为叶子结点）；否则其左孩子是结点2i。
// 3．如果2i+1>n，则结点i无右孩子；否则其右孩子是结点2i+1。


#define MAX_TREE_SIZE 100

//树结点的数据类型
typedef int TElemType;

//双亲表示法
typedef struct PNode {
    TElemType data;
    int       parent;
} PNode;

typedef struct PTree {
    PNode nodes[MAX_TREE_SIZE];
    int   root;
    int   nodeNum;
} PTree;

//孩子表示法
typedef struct CNode {
    int           child;
    struct CNode* next;
} * ChildPtr;

typedef struct {
    TElemType data;
    ChildPtr  firstchild;
} CTBox;

typedef struct {
    CTBox nodes[MAX_TREE_SIZE];
    int   root;
    int   nodeNum;
} CTree;

//树的孩子兄弟表示法(链表)
typedef struct CSNode {
    TElemType      data;
    struct CSNode *firstchild, *rightsib;
} CSNode, *CSTree;

//-----------------------------------------------------------------------

//二叉树的二叉链表结点结构定义
typedef struct BiNode {
    TElemType      data;
    struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

//二叉树的前序遍历递归算法
void preOrderTraverse(BiTree T, void (*operate)(TElemType* data));
//二叉树的中序遍历递归算法
void inOrderTraverse(BiTree T, void (*operate)(TElemType* data));
//二叉树的后序遍历递归算法
void postOrderTraverse(BiTree T, void (*operate)(TElemType* data));
//二叉树的层序遍历递归算法
void floorOrderTraverse(BiTree T, void (*operate)(TElemType* data));

typedef enum {
    //指向左右孩子指针
    Link,
    //指向前驱或后继的线索
    Thread
} PointerTag;

// 线索二叉书存储结点结构
typedef struct BiThrNode {
    TElemType         data;
    struct BiThrNode *lchild, *rchild;
    PointerTag        lTag;
    PointerTag        rTag;
} BiThrNode, *BiThrTree;

void inOrderThreading(BiThrTree* headNode, BiThrTree T);
void inOrderTraverseBiThrTree(BiThrTree T, void (*operate)(TElemType* data));

//哈夫曼树结点结构
typedef struct {
    //结点权重
    int weight;
    //父结点、左孩子、右孩子在数组中的位置下标(-1表示不存在)
    int parent, left, right;
} HTNode, *HuffmanTree;

typedef char ** HuffmanCode;

//HT为地址传递的存储哈夫曼树的数组，w为存储结点权重值的数组，n为结点个数
void createHuffmanTree(HuffmanTree* HT, int* w, int n);
//从叶子结点一直找到根结点，逆向记录途中经过的标记。(也可以从根节点出发，遍历哈夫曼数，查找对应元素，从而获取路径)
void huffmanCoding(HuffmanTree HT, HuffmanCode* HC, int n);
//计算皇后问题
int calculteQueenSolution(int* chessboard, const int boardSize);

#ifdef __cplusplus
}
#endif
