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
typedef struct BiTNode {
    TElemType       data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;







#ifdef __cplusplus
}
#endif
