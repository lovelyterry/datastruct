#include <cstdio>
#include <cstring>

#include <thread>
#include <algorithm>
#include <ratio>
#include <chrono>
#include <iostream>
#include <string>

#include "sort.h"

#define MAXSIZE 100000L

int templateList[MAXSIZE];
int answer[MAXSIZE];

double sortTest(void (*func)(int data[], int length), int data[], int length) {
    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
    if (func) { func(data, length); }
    std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
    for (int i = 0; i < length; i++) {
        if (data[i] != answer[i]) { return 0; }
    }
    return std::chrono::duration<double, std::milli>(t2 - t1).count();
}

int main(int argc, const char* argv[]) {
    srand(time(0));
    {
        for (int i = 0; i < MAXSIZE; i++) { templateList[i] = rand(); }
        memcpy(&answer, &templateList, sizeof(answer));
        std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
        std::sort(answer, answer + MAXSIZE);
        std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
        printf("std::sort() time cost: %fms\r\n", std::chrono::duration<double, std::milli>(t2 - t1).count());
    }

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("selectSort time cost: %fms\r\n", sortTest(selectSort, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("insertSort time cost: %fms\r\n", sortTest(insertSort, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("shellSort time cost: %fms\r\n", sortTest(shellSort, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("heapSort time cost: %fms\r\n", sortTest(heapSort, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("mergeSortIterative time cost: %fms\r\n", sortTest(mergeSortIterative, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("quickSortIterative time cost: %fms\r\n", sortTest(quickSortIterative, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("quickSortRecursive time cost: %fms\r\n", sortTest(quickSortRecursive, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("insertSortHalf time cost: %fms\r\n", sortTest(insertSortHalf, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("mergeSortRecursive time cost: %fms\r\n", sortTest(mergeSortRecursive, data, MAXSIZE));
        free(data);
    }).detach();

    std::thread([&]() {
        int* data = (int*)malloc(MAXSIZE * sizeof(int));
        memcpy(data, &templateList, MAXSIZE * sizeof(int));
        printf("bubbleSort time cost: %fms\r\n", sortTest(bubbleSort, data, MAXSIZE));
        free(data);
    }).join();

    return 0;
}
