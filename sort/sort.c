#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sort.h"

//基于“插入”思想的排序
void insertSort(int data[], int length) {
    //初始认为序列中只有一个有序元素
    for (int i = 1; i < length; i++) {
        //如果新插入的元素比最后一个元素大,则直接认为插入完成，否则逐步向前查找并移动元素
        if (data[i] < data[i - 1]) {
            //i是新元素的索引
            int newElement = data[i];
            int j          = i - 1;
            for (; j >= 0 && data[j] > newElement; j--) { data[j + 1] = data[j]; }
            data[j + 1] = newElement;
        }
    }
}

void insertSortHalf(int data[], int length) {
    //初始认为序列中只有一个有序元素
    for (int i = 1; i < length; i++) {
        int start = 0;
        int end   = i - 1;
        int temp  = data[i];
        //采用折半查找法判断插入位置，最终变量 start 表示插入位置
        while (start <= end) {
            int mid = (start + end) / 2;
            if (data[mid] > temp) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        //有序表中插入位置后的元素统一后移
        for (int j = i; j > start; j--) { data[j] = data[j - 1]; }
        data[start] = temp;  //插入元素
    }
}

void shellSort(int data[], int length) {
    int dlta = length;
    do {
        dlta = dlta / 3 + 1;
        //这里其实就是增量为dlta的插入排序
        for (int i = dlta; i < length; i++) {
            //如果某个元素大于dlta后的元素, 则交换这两个元素的位置
            if (data[i] < data[i - dlta]) {
                //i是新元素的索引
                int newElement = data[i];
                int j          = i - dlta;
                for (; j >= 0 && data[j] > newElement; j -= dlta) { data[j + dlta] = data[j]; }
                //插入完成
                data[j + dlta] = newElement;
            }
        }
    } while (dlta > 1);
}

//基于“交换”思想的排序
void bubbleSort(int data[], int length) {
    //用于标识一次冒泡过程中是否有元素进行位置交换，如果没有，则认为排序已经完成
    bool swapFlag = true;
    for (int i = 0; i < length && swapFlag; i++) {
        swapFlag = false;
        //从最后一个元素开始，依次喝前一个元素进行比较，如果大小不对则交换顺序
        for (int j = length - 1; j > i; j--) {
            if (data[j] < data[j - 1]) {
                int temp    = data[j];
                data[j]     = data[j - 1];
                data[j - 1] = temp;
                swapFlag    = true;
            }
        }
    }
}

static void quickSortRecursiveImpl(int data[], int start, int end) {
    if (start >= end) { return; }
    int i = start;
    int j = end;
    int k = data[start];
    while (i < j) {
        while (i < j && data[j] >= k) { j--; }
        if (i < j) { data[i++] = data[j]; }
        while (i < j && data[i] <= k) { i++; }
        if (i < j) { data[j--] = data[i]; }
    }
    data[i] = k;
    quickSortRecursiveImpl(data, start, i - 1);
    quickSortRecursiveImpl(data, i + 1, end);
}

void quickSortRecursive(int data[], int length) {
    quickSortRecursiveImpl(data, 0, length - 1);
}

struct Range {
    int start, end;
};

static struct Range newRange(int s, int e) {
    struct Range r;
    r.start = s;
    r.end   = e;
    return r;
}

void quickSortIterative(int data[], const int length) {
    if (length <= 0) { return; }
    //stack[]模拟堆栈,depth为数量,stack[depth++]为push,stack[--depth]为pop且取得元素
    struct Range* stack = (struct Range*)malloc(length * sizeof(struct Range));
    int           depth = 0;

    stack[depth++] = newRange(0, length - 1);
    while (depth) {
        struct Range range = stack[--depth];
        if (range.start >= range.end) { continue; }
        int i = range.start;
        int j = range.end;
        int k = data[range.start];
        while (i < j) {
            while (i < j && data[j] >= k) { j--; }
            if (i < j) { data[i++] = data[j]; }
            while (i < j && data[i] <= k) { i++; }
            if (i < j) { data[j--] = data[i]; }
        }
        data[i]        = k;
        stack[depth++] = newRange(range.start, i - 1);
        stack[depth++] = newRange(i + 1, range.end);
    }
    free(stack);
}

//基于“选择”思想的排序
void selectSort(int data[], int length) {
    //用于标识一次遍历过程中最小值的索引
    int minIndex = 0;
    for (int i = 0; i < length; i++) {
        minIndex = i;
        for (int j = i + 1; j < length; j++) {
            //寻找最小值的标识
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (i != minIndex) {
            int temp       = data[i];
            data[i]        = data[minIndex];
            data[minIndex] = temp;
        }
    }
}

//调整以start为起点,end为终点的堆为大顶有序堆
static void heapAdjust(int data[], volatile int start, const int end) {
    //先保存顶节点的值，之后的操作中会被覆盖
    const int topNode = data[start];

    for (int i = 2 * start + 1; i <= end; i = 2 * i + 1) {
        //判断是左节点(2*start + 1)大还是右节点(2*start + 2)大，i为大节点的索引
        if (i < end && data[i] < data[i + 1]) { ++i; }
        //如果顶节点大于较大的子节点，则无需交换，直接退出循环
        if (topNode >= data[i]) { break; }
        //将父节点的数据设置为较大子节点的数据
        data[start] = data[i];
        //将较大子节点设置为较大子节点，继续寻找最大值，直到结尾
        start = i;
    }
    //将子节点中的最小值赋值为顶节点的值
    data[start] = topNode;
}

void heapSort(int data[], int length) {
    //编号为0~(length/2-1)的节点都有子节点，从(length/2-1)开始，
    //依次调整，将待排序序列构建成一个大顶堆
    for (int i = length / 2 - 1; i >= 0; i--) {
        heapAdjust(data, i, length - 1);
    }
    //通过不断地筛选出最大值，同时不断地进行筛选剩余元素
    for (int i = length - 1; i > 0; i--) {
        //将堆顶记录和当前未经排序子序列的最后一个记录交换
        int temp = data[i];
        data[i]  = data[0];
        data[0]  = temp;
        heapAdjust(data, 0, i - 1);
    }
}

//基于“归并”思想的排序
void mergeSortIterative(int data[], int length) {
    int* source = data;
    int* dest   = (int*)malloc(length * sizeof(int));
    //将src中的元素merge到dest中
    for (int seg = 1; seg < length; seg *= 2) {
        for (int start = 0; start < length; start += 2 * seg) {
            int k      = start;
            int start1 = start;
            int end1   = start + seg < length ? start + seg : length;
            int start2 = end1;
            int end2   = start + 2 * seg < length ? start + 2 * seg : length;
            while (start1 < end1 && start2 < end2) { dest[k++] = source[start1] < source[start2] ? source[start1++] : source[start2++]; }
            while (start1 < end1) { dest[k++] = source[start1++]; }
            while (start2 < end2) { dest[k++] = source[start2++]; }
        }
        //交换src和dest的指针
        int* temp = source;
        source    = dest;
        dest      = temp;
    }
    //这里的src已经又和dest交换过了，其实就是dest
    if (source != data) {
        for (int i = 0; i < length; i++) { data[i] = source[i]; }
        dest = source;
    }
    free(dest);
}

static void mergeSortRecursiveImpl(int data[], int reg[], int start, int end) {
    if (start >= end) { return; }
    int mid    = (end + start) / 2;
    int start1 = start;
    int end1   = mid;
    int start2 = mid + 1;
    int end2   = end;
    mergeSortRecursiveImpl(data, reg, start1, end1);
    mergeSortRecursiveImpl(data, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2) { reg[k++] = data[start1] < data[start2] ? data[start1++] : data[start2++]; }
    while (start1 <= end1) { reg[k++] = data[start1++]; }
    while (start2 <= end2) { reg[k++] = data[start2++]; }
    for (k = start; k <= end; k++) { data[k] = reg[k]; }
}

void mergeSortRecursive(int data[], int length) {
    int* reg = (int*)malloc(length * sizeof(int));
    mergeSortRecursiveImpl(data, reg, 0, length - 1);
    free(reg);
}
