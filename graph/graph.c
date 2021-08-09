#include "graph.h"
#include "queue/queue.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
int miniSpanTreePrim(MGraph* G, void (*operate)(VertexType* vex1, VertexType* vex2)) {
    //用于记录最小生成树的权值和
    int sum = 0;
    //用于临时存放某一顶点到最小生成树的权值(距离)(如果是0,则表示已经被纳入最小生成树中(已经在A类中))
    int lowcost[MAXVEX];
    //adjvex记录某一顶点(即数组索引对应的顶点)和“已经归纳进最小生成树中的顶点”中的哪个相连时权值最小，也就是最后要求的结果
    int adjvex[MAXVEX] = { 0 };
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
        if (operate) { operate(&(G->vexs[k]), &(G->vexs[adjvex[k]])); }
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

//对边集数组Edge结构的定义
typedef struct Edge {
    int begin;
    int end;
    int weight;
} Edge;

//邻接矩阵转换成边集数组
static int transMGraph2EdgeArray(MGraph* G, Edge* edges) {
    int edgeCnt = 0;
    //由于是无向图，，邻接矩阵是一个对称矩阵，因此只需要遍历邻接矩阵的上半个三角形
    for (int i = 0; i < G->numVertexes; i++) {
        for (int j = i + 1; j < G->numVertexes; j++) {
            if (G->arc[i][j] != INFINITY) {
                edges[edgeCnt].begin  = i;
                edges[edgeCnt].end    = j;
                edges[edgeCnt].weight = G->arc[i][j];
                edgeCnt++;
            }
        }
    }
    //对边集数组进行排序(选择排序凑合着用)
    for (int i = 0; i < edgeCnt; i++) {
        int minIndex = i;
        for (int j = i + 1; j < edgeCnt; j++) {
            if (edges[j].weight < edges[minIndex].weight) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Edge t          = edges[i];
            edges[i]        = edges[minIndex];
            edges[minIndex] = t;
        }
    }
    return edgeCnt;
}

//依次查找某个顶点的在现有生成树中所连接的最后一个顶点
static int findLastVertex(int* parent, int vertex) {
    while (parent[vertex] > 0) { vertex = parent[vertex]; }
    return vertex;
}

//将所有边按照权值的大小进行升序排序，然后从小到大一一判断，条件为：如果这个边不会与之前选择的所有边组成回路，就可以作为最小生成树的一部分；反之，舍去。直到具有 n 个顶点的连通网筛选出来 n-1 条边为止。筛选出来的边和所有的顶点构成此连通网的最小生成树。
//判断是否会产生回路的方法为：在初始状态下给每个顶点赋予不同的标记，对于遍历过程的每条边，其都有两个顶点，判断这两个顶点的标记是否一致，如果一致，说明它们本身就处在一棵树中，如果继续连接就会产生回路；如果不一致，说明它们之间还没有任何关系，可以连接。
//Kruskal算法生成最小生成树
int miniSpanTreeKruskal(MGraph* G, void (*operate)(VertexType* vex1, VertexType* vex2)) {
    //用于记录最小生成树的权值和
    int sum = 0;
    //定义边集数组
    Edge* edges   = malloc(G->numEdges * sizeof(Edge));
    int   edgeCnt = transMGraph2EdgeArray(G, edges);
    //定义一数组用来判断边与边是否形成环路
    int parent[MAXVEX] = { 0 };

    //循环每一条边
    for (int i = 0; i < edgeCnt; i++) {
        int n = findLastVertex(parent, edges[i].begin);
        int m = findLastVertex(parent, edges[i].end);
        //假如n与m不等，说明此边没有与现有生成树形成环路
        if (n != m) {
            if (operate) { operate(&(G->vexs[edges[i].begin]), &(G->vexs[edges[i].end])); }
            sum += edges[i].weight;
            //将此边的结尾顶点放入下标为起点的parent中,表示此顶点已经在生成树集合中
            parent[n] = m;
        }
    }
    free(edges);
    return sum;
}

//Dijkstra算法
//求有向网G的v0顶点到其余顶点v最短路径patharc[v]及带权长度shortPathTable[v]
//patharc[v]的值为前驱顶点下标(最短的路径只有一条)，shortPathTable[v]表示v0到v的最短路径长度和。
void shortestPathDijkstra(MGraph* G, int v0, int patharc[], int shortPath[]) {
    //final[w]表示是否已经求得顶点v0至vw的最短路径，已经求得的的标记为1
    int final[MAXVEX] = { 0 };
    //v0至v0不需要求路径
    final[v0] = 1;
    //初始化数据，从邻接矩阵中得到各个顶点到v0的距离v0,且所有点的前驱都是v0
    for (int v = 0; v < G->numVertexes; v++) {
        shortPath[v] = G->arc[v0][v];
        patharc[v]   = v0;
    }

    //开始主循环，依次求得v0到某个v顶点的最短路径，总共G->numVertexes个顶点，但是需要求G->numVertexes-1次
    for (int v = 1; v < G->numVertexes; v++) {
        //寻找离v0最近的未找过的联通的顶点，存放在k中
        int min = INFINITY;
        int k   = 0;
        for (int w = 0; w < G->numVertexes; w++) {
            if (!final[w] && shortPath[w] < min) {
                k   = w;
                min = shortPath[w];
            }
        }
        //k点到v0的最短路径找到了
        final[k] = 1;

        //修正当前最短路径及距离(看看经过这个点后，v0到达其他顶点的距离[v0->k->w]是不是会变小)
        for (int w = 0; w < G->numVertexes; w++) {
            //[v0->k] =  min; [k->w] = G->arc[k][w]
            if (!final[w] && (min + G->arc[k][w] < shortPath[w])) {
                //说明找到了更短的路径，修改shortPathTable[w]和patharc[w]
                shortPath[w] = min + G->arc[k][w];
                //w点通过k点后距离v0点的距离最近，所以令k为w的前驱
                patharc[w] = k;
            }
        }
    }
}

//Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
//遍历所有的顶点K,判断经过顶点 K 是否存在一条可行路径比直达的路径的权值小，如果式子成立，此时只需要更新记录的权值和即可。
//其中pathMatirx二维数组存放各对顶点的最短路径经过的顶点，shortPathMatirx二维数组存储各个顶点之间的权值
void shortestPathFloyd(MGraph* G, int* pathMatirx[], int* shortPathMatirx[]) {
    for (int v = 0; v < G->numVertexes; ++v) {
        for (int w = 0; w < G->numVertexes; ++w) {
            shortPathMatirx[v][w] = G->arc[v][w];
            pathMatirx[v][w]      = w;
        }
    }
    for (int k = 0; k < G->numVertexes; ++k) {
        for (int v = 0; v < G->numVertexes; ++v) {
            for (int w = 0; w < G->numVertexes; ++w) {
                if (shortPathMatirx[v][k] + shortPathMatirx[k][w] < shortPathMatirx[v][w]) {
                    shortPathMatirx[v][w] = shortPathMatirx[v][k] + shortPathMatirx[k][w];
                    pathMatirx[v][w]      = pathMatirx[v][k];
                }
            }
        }
    }
}

//拓扑排序，若GL无回路，则输出拓扑排序序列并返回true，若有回路返回false
//对有向无环图进行拓扑排序，只需要遵循两个原则：
//在图中选择一个没有前驱的顶点 V；
//从图中删除顶点 V 和所有以该顶点为尾的弧。
//在编写程序解决拓扑排序的问题时，大致思路为：首先通过邻接表将 AOV 网进行存储，由于拓扑排序的整个过程中，都是以顶点的入度为依据进行排序，所以需要根据建立的邻接表统计出各顶点的入度。在得到各顶点的入度后，首先找到入度为 0 的顶点作为拓扑排序的起始点，然后查找以该顶点为起始点的所有顶点，如果入度为 1，说明如果删除前一个顶点后，该顶点的入度为 0，为拓扑排序的下一个对象。
bool topologicalSort(GraphAdjList* GL, void (*operate)(VertexType* data)) {
    //用于统计输出顶点的个数
    int  count = 0;
    int  top   = 0;
    int* stack = (int*)malloc(GL->numVertexes * sizeof(int));

    //将入度为0的节点入栈
    for (int i = 0; i < GL->numVertexes; i++) {
        if (GL->adjList[i].in == 0) { stack[++top] = i; }
    }
    while (top != 0) {
        int gettop = stack[top--];
        if (operate) operate(&(GL->adjList[gettop].data));
        count++;
        //依次查找跟该顶点相链接的顶点，如果初始入度为1，当删除前一个顶点后，该顶点入度为0
        for (EdgeNode* e = GL->adjList[gettop].firstedge; e != NULL; e = e->next) {
            if (!(--GL->adjList[e->adjvex].in)) { stack[++top] = e->adjvex; }
        }
    }
    free(stack);
    //如果count小于顶点数，说明存在环
    if (count < GL->numVertexes) { return false; }
    return true;
}

//求关键路径，GL为有向网，输出GL的各项关键活动
//对于所有的边来说，如果它的最早开始时间等于最晚开始时间，称这条边所代表的活动为关键活动。由关键活动构成的路径为关键路径。
void criticalPath(GraphAdjList* GL) {
    int count = 0;
    //拓扑排序时需要用到的栈
    int  top   = 0;
    int* stack = (int*)malloc(GL->numVertexes * sizeof(int));
    //用于存储拓扑序列的栈
    int topTopological = 0;
    //用于stackTopological的指针
    int* stackTopological = (int*)malloc(GL->numVertexes * sizeof(int));
    //最早发生时间
    int* etv = (int*)malloc(GL->numVertexes * sizeof(int));
    for (int i = 0; i < GL->numVertexes; i++) { etv[i] = 0; }
    //将入度为0的节点入栈
    for (int i = 0; i < GL->numVertexes; i++) {
        if (0 == GL->adjList[i].in) { stack[++top] = i; }
    }
    while (top != 0) {
        int gettop = stack[top--];
        count++;
        //将顶点放入拓扑排序栈中
        stackTopological[++topTopological] = gettop;
        //e是和gettop这个顶点相连的边
        for (EdgeNode* e = GL->adjList[gettop].firstedge; e; e = e->next) {
            //遍历该与该顶点相连的顶点，放入栈中，用于下一次循环
            if (!(--GL->adjList[e->adjvex].in)) { stack[++top] = e->adjvex; }
            //如果当前顶点的最早发生时间加上路径的权重大于路径相连的顶点的最找发生时间，则更新相连顶点的最早发生时间
            if (etv[e->adjvex] < (etv[gettop] + e->weight)) { etv[e->adjvex] = etv[gettop] + e->weight; }
        }
    }
    free(stack);
    //如果count小于顶点数，说明存在环
    if (count >= GL->numVertexes) {
        //最迟发生时间
        int* ltv = (int*)malloc(GL->numVertexes * sizeof(int));
        //初始化每个节点的最迟发生时间都时最后一个节点的最早发生时间
        for (int i = 0; i < GL->numVertexes; i++) { ltv[i] = etv[GL->numVertexes - 1]; }
        while (topTopological != 0) {
            //将拓扑排序后的树出栈
            int gettop = stackTopological[topTopological--];
            //e是和gettop这个顶点相连的边
            for (EdgeNode* e = GL->adjList[gettop].firstedge; e; e = e->next) {
                if (ltv[gettop] > ltv[e->adjvex] - e->weight) { ltv[gettop] = ltv[e->adjvex] - e->weight; }
            }
        }

        //遍历数组,输出结果
        for (int j = 0; j < GL->numVertexes; j++) {
            for (EdgeNode* e = GL->adjList[j].firstedge; e; e = e->next) {
                //最早发生时间和最迟发生时间相同，则该点在关键路径上
                if (etv[j] == ltv[e->adjvex] - e->weight) { printf("<v%f,v%f> length: %f , ", GL->adjList[j].data, GL->adjList[e->adjvex].data, e->weight); }
            }
        }
        free(ltv);
    }
    free(etv);
    free(stackTopological);
}