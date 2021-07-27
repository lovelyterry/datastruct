#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "tree.h"


//先序遍历插入数据
//A B D H # # I # # E J # # # C F # # G # #
void createBiTree(BiTree* T) {
    char ch = '\0';
    std::cin >> ch;
    if (ch == '#') {
        (*T) = NULL;
    } else {
        (*T)       = (BiTree)malloc(sizeof(BiTree));
        (*T)->data = ch;
        createBiTree(&(*T)->lchild);
        createBiTree(&(*T)->rchild);
    }
}

void outputData(TElemType* data) {
    std::cout << static_cast<char>(*data) << " ";
}


int main(void) {
    BiTree root = NULL;
    createBiTree(&root);
    if (root == NULL) {
        return 0;
    }

    preOrderTraverse(root, outputData);
    std::cout << std::endl;

    inOrderTraverse(root, outputData);
    std::cout << std::endl;

    postOrderTraverse(root, outputData);
    std::cout << std::endl;

    floorOrderTraverse(root, outputData);
    std::cout << std::endl;

    return 0;
}
