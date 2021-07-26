#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//基于“插入”思想的排序
void insertSort(int data[], int length);
void insertSortHalf(int data[], int length);
void shellSort(int data[], int length);
//基于“交换”思想的排序
void bubbleSort(int data[], int length);
void quickSortRecursive(int data[], int length);
void quickSortIterative(int data[], const int length);
//基于“选择”思想的排序
void selectSort(int data[], int length);
void heapSort(int data[], int length);
//基于“归并”思想的排序
void mergeSortIterative(int data[], int length);
void mergeSortRecursive(int data[], int length);

#ifdef __cplusplus
}
#endif
