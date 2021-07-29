#include <cstdio>
#include <cstdlib>
#include <ctime>

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

//打印哈夫曼编码的函数
void printHuffmanCode(HuffmanCode htable, int* w, int n) {
    printf("Huffman code : \n");
    for (int i = 0; i < n; i++) { printf("%d code = %s\n", w[i], htable[i]); }
}

#define BOARD_SIZE 8
//总共8行，数组array[n]用来分别表示第n行放在第几列
static int chessboard[BOARD_SIZE] = { 0 };

int main(void) {
    std::cout << "total: " << calculteQueenSolution(chessboard, BOARD_SIZE) << " solutions." << std::endl;
    {
        int         weight[10] = { 0 };
        HuffmanTree htree;
        HuffmanCode htable;

        srand(time(0));
        for (int i = 0; i < sizeof(weight) / sizeof(int); i++) { weight[i] = rand(); }
        createHuffmanTree(&htree, weight, sizeof(weight) / sizeof(int));
        huffmanCoding(htree, &htable, sizeof(weight) / sizeof(int));
        printHuffmanCode(htable, weight, sizeof(weight) / sizeof(int));
    }

    {
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
    }

    return 0;
}