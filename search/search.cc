

int sequentialSearch(int* a, int n, int key) {
    for (int i = 0; i <= n; i++) {
        if (a[i] == key) { return i; }
    }
    return -1;
}

int Sequential_Search2(int* a, int n, int key) {
    int i;
    /* 设置a[0]为关键字值，我们称之为“哨兵” */
    a[0] = key;
    /* 循环从数组尾部开始 */
    i = n;
    while (a[i] != key) {
        i--;
    }
    /* 返回0则说明查找失败 */
    return i;
}
