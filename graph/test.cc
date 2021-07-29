#include <iostream>

#include "graph.h"

#define IN INFINITY

#define DEMOARC                                \
    {                                          \
        {  0, 10, IN, IN, IN, 11, IN, IN, IN },\
        { 10,  0, 18, IN, IN, IN, 16, IN, 12 },\
        { IN, 18,  0, 22, IN, IN, IN, IN,  8 },\
        { IN, IN, 22,  0, 20, IN, 24, 16, 21 },\
        { IN, IN, IN, 20,  0, 26, IN,  7, IN },\
        { 11, IN, IN, IN, 26,  0, 17, IN, IN },\
        { IN, 16, IN, 24, IN, 17,  0, 19, IN },\
        { IN, IN, IN, 16,  7, IN, 19,  0, IN },\
        { IN, 12,  8, 21, IN, IN, IN, IN,  0 },\
    }

int main() {
    MGraph mG = {
        .vexs        = { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
        .arc         = DEMOARC,
        .numVertexes = 9,
        .numEdges    = 39,
    };
    int adjvex[9] = {0};
    std::cout << miniSpanTreePrim(&mG, adjvex) << std::endl;
    for (int i = 0; i < 9; i++) {
        std::cout << "(" << i << "," << adjvex[i] << "),";
    }
    std::cout << std::endl;
    return 0;
}