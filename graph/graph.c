#include "graph.h"
#include "queue/queue.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//邻接矩阵的深度优先递归算法
static void depthFirstSearchMGraph(MGraph* G, int i, bool* visited, void (*operate)(VertexType* data)) {
    visited[i] = true;
    if (operate) { operate(&G->vexs[i]); }
    //有路可以走，且没有访问过，则访问
    for (int j = 0; j < G->numVertexes; j++) {
        if (G->arc[i][j] && !visited[j]) { depthFirstSearchMGraph(G, j, visited, operate); }
    }
}

//邻接矩阵的深度遍历操作
void depthFirstSearchTraverseMGraph(MGraph* G, void (*operate)(VertexType* data)) {
    bool* visited = malloc(sizeof(bool) * G->numVertexes);
    for (int i = 0; i < G->numVertexes; i++) { visited[i] = false; }
    for (int i = 0; i < G->numVertexes; i++) {
        if (!visited[i]) { depthFirstSearchMGraph(G, i, visited, operate); }
    }
    free(visited);
}

//邻接表的深度优先递归算法
static void depthFirstSearchGraphAdjList(GraphAdjList* GL, int i, bool* visited, void (*operate)(VertexType* data)) {
    visited[i] = true;
    if (operate) { operate(&GL->adjList[i].data); }
    EdgeNode* p = GL->adjList[i].firstedge;
    //有路可以走，且没有访问过，则访问
    while (p) {
        if (!visited[p->adjvex]) { depthFirstSearchGraphAdjList(GL, p->adjvex, visited, operate); }
        p = p->next;
    }
}

//邻接表的深度遍历操作
void depthFirstSearchTraverseGraphAdjList(GraphAdjList* GL, void (*operate)(VertexType* data)) {
    bool* visited = malloc(sizeof(bool) * GL->numVertexes);
    for (int i = 0; i < GL->numVertexes; i++) { visited[i] = false; }
    for (int i = 0; i < GL->numVertexes; i++) {
        if (!visited[i]) { depthFirstSearchGraphAdjList(GL, i, visited, operate); }
    }
    free(visited);
}

//邻接矩阵的广度遍历算法
void breadthFirstSearchTraverseMGraph(MGraph* G, void (*operate)(VertexType* data)) {
    bool* visited = malloc(sizeof(bool) * G->numVertexes);

    SqQueue Q = { 0 };
    for (int i = 0; i < G->numVertexes; i++) { visited[i] = false; }
    for (int i = 0; i < G->numVertexes; i++) {
        if (visited[i]) { continue; }
        visited[i] = true;
        if (operate) { operate(&G->vexs[i]); }
        enSqQueue(&Q, i);
        while (lengthSqQueue(&Q)) {
            deSqQueue(&Q, &i);
            for (int j = 0; j < G->numVertexes; j++) {
                if (G->arc[i][j] && !visited[j]) {
                    visited[j] = true;
                    if (operate) { operate(&G->vexs[j]); }
                    enSqQueue(&Q, j);
                }
            }
        }
    }
    free(visited);
}

//邻接表的广度遍历算法
void breadthFirstSearchTraverseGraphAdjList(GraphAdjList* GL, void (*operate)(VertexType* data)) {
    bool*   visited = malloc(sizeof(bool) * GL->numVertexes);
    SqQueue Q       = { 0 };
    for (int i = 0; i < GL->numVertexes; i++) { visited[i] = false; }
    for (int i = 0; i < GL->numVertexes; i++) {
        if (!visited[i]) {
            visited[i] = true;
            if (operate) { operate(&GL->adjList[i].data); }
            enSqQueue(&Q, i);
            while (lengthSqQueue(&Q)) {
                deSqQueue(&Q, &i);
                EdgeNode* p = GL->adjList[i].firstedge;
                while (p) {
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = true;
                        if (operate) { operate(&GL->adjList[p->adjvex].data); }
                        enSqQueue(&Q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
    free(visited);
}

// 普里姆算法在找最小生成树时，将顶点分为两类，一类是在查找的过程中已经包含在树中的（假设为A类），剩下的是另一类（假设为B类）。
// 对于给定的连通网，起始状态全部顶点都归为B类。在找最小生成树时，选定任意一个顶点作为起始点，并将之从B类移至A类；
// 然后找出B类中到A类中的顶点之间权值最小的顶点，将之从B类移至A类，如此重复，直到B类中没有顶点为止。
// 所走过的顶点和边就是该连通图的最小生成树。
//Prim算法生成最小生成树
//adjvex记录某一顶点(即数组索引对应的顶点)和“已经归纳进最小生成树中的顶点”中的哪个相连时权值最小，也就是最后要求的结果
int miniSpanTreePrim(MGraph* G, int* adjvex) {
    //用于记录最小生成树的权值和
    int sum = 0;
    //用于临时存放某一顶点到最小生成树的权值(距离)(如果是0,则表示已经被纳入最小生成树中(已经在A类中))
    int lowcost[MAXVEX];
    //0点和0点联通
    adjvex[0] = 0;
    //初始化其余的点到(起始点)0点距离(自己到自己的距离为0)
    for (int i = 0; i < G->numVertexes; i++) { lowcost[i] = G->arc[0][i]; }
    for (int i = 1; i < G->numVertexes; i++) {
        //这段程序的作用是为了找到lowcost中最小值所在的索引(即另一顶点)，并赋值给k
        int min = INFINITY;
        int j   = 1;
        int k   = 0;
        while (j < G->numVertexes) {
            //权值为0，说明顶点已经归入最小生成树中
            if (lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                k   = j;
            }
            j++;
        }
        sum += lowcost[k];
        //将距离最小生成树的顶点归入最小生成树(即赋值为0)
        lowcost[k] = 0;
        //由于此时树中新加入了一个顶点k，判断，从k点出发，到达其它各顶点的权值是否比之前记录的权值还要小
        for (int j = 1; j < G->numVertexes; j++) {
            if (lowcost[j] != 0 && G->arc[k][j] < lowcost[j]) {
                lowcost[j] = G->arc[k][j];
                adjvex[j]  = k;
            }
        }
    }
    return sum;
}
