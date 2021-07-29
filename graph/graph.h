#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ADT 图(Graph)
// Data
//     顶点的有穷非空集合和边的集合。
// Operation
//     CreateGraph(*G, V, VR): 按照顶点集V和边弧集VR的定义构造图G。
//     DestroyGraph(*G):       图G存在则销毁。
//     LocateVex(G, u):        若图G中存在顶点u，则返回图中的位置。
//     GetVex(G, v):           返回图G中顶点v的值。
//     PutVex(G, v, value):    将图G中顶点v赋值value。
//     FirstAdjVex(G, *v):     返回顶点v的一个邻接顶点，若顶点在G中无邻接顶点返回空。
//     NextAdjVex(G, v, *w):   返回顶点v相对于顶点w的下一个邻接顶点，
//                             若w是v的最后一个邻接点则返回“空”。
//     InsertVex(*G, v):       在图G中增添新顶点v。
//     DeleteVex(*G, v):       删除图G中顶点v及其相关的弧。
//     InsertArc(*G, v, w):    在图G中增添弧<v,w>，若G是无向图，还需要增添对称弧<w,v>。
//     DeleteArc(*G, v, w):    在图G中删除弧<v,w>，若G是无向图，则还删除对称弧<w,v>。
//     DFSTraverse(G):         对图G中进行深度优先遍历，在遍历过程对每个顶点调用。
//     HFSTraverse(G):         对图G中进行广度优先遍历，在遍历过程对每个顶点调用。
// endADT

typedef char VertexType;
typedef int  EdgeType;

//图的邻接矩阵表示方法

#define MAXVEX 100
//无穷大
#define INFINITY (0x7FFFFFFFL)

typedef struct MGraph {
    //顶点数组
    VertexType vexs[MAXVEX];
    //邻接矩阵，可看作边表
    EdgeType arc[MAXVEX][MAXVEX];
    int      numVertexes;
    int      numEdges;
} MGraph;

//图的邻接表表示方法
typedef struct EdgeNode {
    //邻接点域(和哪个个顶点相连)，存储该顶点对应的下标
    int adjvex;
    //用于存储权值，对于非网图可以不需要
    EdgeType weight;
    //链域，指向下一个邻接点
    struct EdgeNode* next;
} EdgeNode;

//顶点表结点
typedef struct VertexNode {
    //顶点域，存储顶点信息
    VertexType data;
    //边的表头指针
    EdgeNode* firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct GraphAdjList {
    AdjList adjList;
    int numVertexes;
    int numEdges;
} GraphAdjList;


//邻接矩阵的深度遍历操作
void depthFirstSearchTraverseMGraph(MGraph* G, void (*operate)(VertexType* data));
//邻接表的深度遍历操作
void depthFirstSearchTraverseGraphAdjList(GraphAdjList* GL, void (*operate)(VertexType* data));
//邻接矩阵的广度遍历算法
void breadthFirstSearchTraverseMGraph(MGraph* G, void (*operate)(VertexType* data));
//邻接表的广度遍历算法
void breadthFirstSearchTraverseGraphAdjList(GraphAdjList* GL, void (*operate)(VertexType* data));

//Prim算法生成最小生成树
//adjvex记录某一顶点(即数组索引对应的顶点)和“已经归纳进最小生成树中的顶点”中的哪个相连时权值最小，也就是最后要求的结果
int miniSpanTreePrim(MGraph* G, int* adjvex);





#ifdef __cplusplus
}
#endif
