#include <iostream>

#include <ctime>

#include "search.h"

int  last = 0;
void outputData(TElemType* data) {
    if (last >= *data) {
        std::cout << " error: " << *data;
    }
    std::cout << (int)*data << " ";
    last = *data;
}
int record[10];

int main(void) {
    srand(time(0));

    {
        BiTree bitree = NULL;
        for (size_t i = 0; i < 10000; i++) {
            int randomVar = rand() % 10000;
            if (i < sizeof(record) / sizeof(int)) {
                record[i] = randomVar;
            }
            insertBiTree(&bitree, randomVar);
        }
        last = 0;
        inOrderTraverse(bitree, outputData);
        std::cout << std::endl;
        for (int i = 0; i < 10; i++) {
            deleteBiTreeByKey(&bitree, record[i]);
        }
        last = 0;
        inOrderTraverse(bitree, outputData);
        std::cout << std::endl;
    }

    {
        AvlTree avlTree = 0;
        bool    taller  = false;
        for (int i = 0; i < 10000; i++) {
            insertAvlTree(&avlTree, rand(), &taller);
        }
        last = 0;
        inOrderTraverse((BiTree)avlTree, outputData);
    }

    return 0;
}