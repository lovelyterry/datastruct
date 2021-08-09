#include <iostream>

#include "graph.h"

#define IN INFINITY

#define DEMOARC1                                   \
    {                                              \
        { 0, 10, IN, IN, IN, 11, IN, IN, IN },     \
            { 10, 0, 18, IN, IN, IN, 16, IN, 12 }, \
            { IN, 18, 0, 22, IN, IN, IN, IN, 8 },  \
            { IN, IN, 22, 0, 20, IN, 24, 16, 21 }, \
            { IN, IN, IN, 20, 0, 26, IN, 7, IN },  \
            { 11, IN, IN, IN, 26, 0, 17, IN, IN }, \
            { IN, 16, IN, 24, IN, 17, 0, 19, IN }, \
            { IN, IN, IN, 16, 7, IN, 19, 0, IN },  \
            { IN, 12, 8, 21, IN, IN, IN, IN, 0 },  \
    }

#define DEMOARC2                                 \
    {                                            \
        { 0, 1, 5, IN, IN, IN, IN, IN, IN },     \
            { 1, 0, 3, 7, 5, IN, IN, IN, IN },   \
            { 5, 3, 0, IN, 1, 7, IN, IN, IN },   \
            { IN, 7, IN, 0, 2, IN, 3, IN, IN },  \
            { IN, 5, 1, 2, 0, 3, 6, 9, IN },     \
            { IN, IN, 7, IN, 3, 0, IN, 5, IN },  \
            { IN, IN, IN, 3, 6, IN, 0, 2, 7 },   \
            { IN, IN, IN, IN, 9, 5, 2, 0, 4 },   \
            { IN, IN, IN, IN, IN, IN, 7, 4, 0 }, \
    }

void printVertex(VertexType* vex1, VertexType* vex2) {
    std::cout << "(" << *vex1 << "," << *vex2 << "),";
}

int main() {
    MGraph mG1 = {
        .vexs        = { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
        .arc         = DEMOARC1,
        .numVertexes = 9,
        .numEdges    = 15,
    };
    std::cout << miniSpanTreePrim(&mG1, printVertex) << std::endl;
    std::cout << miniSpanTreeKruskal(&mG1, printVertex) << std::endl;

    MGraph mG2 = {
        .vexs        = { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
        .arc         = DEMOARC2,
        .numVertexes = 9,
        .numEdges    = 16,
    };

    int patharc[MAXVEX]   = { 0 };
    int shortPath[MAXVEX] = { 0 };
    shortestPathDijkstra(&mG2, 0, patharc, shortPath);

    int* pathMatirx[MAXVEX]      = { 0 };
    int* shortPathMatirx[MAXVEX] = { 0 };
    for (int i = 0; i < MAXVEX; i++) {
        pathMatirx[i]      = (int*)malloc(MAXVEX * sizeof(int));
        shortPathMatirx[i] = (int*)malloc(MAXVEX * sizeof(int));
    }
    shortestPathFloyd(&mG2, pathMatirx, shortPathMatirx);
    for (int i = 0; i < MAXVEX; i++) {
        free(pathMatirx[i]);
        free(shortPathMatirx[i]);
    }

    return 0;
}