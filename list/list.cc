
//删除顺序表中的最小元素，并通过引用参数value将其返回，将空位用最后一个元素填补
//删除成功返回ture，否则返回false
bool DeleteMin(sqList &L, ElemTpye &value) {
    if (L.length == 0){
        return false;
    }
    int minIndex = 0;
    for (int i = 0; i < L.length; i++) {
        if (L[i] < L[minIndex]) {
            minIndex = i;
        }
    }
    value = L[i];
    L[i] = L[length - 1];
    L.length -= 1;
    return true;
}



//设计一个高校的算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1)
void reserve(sqList& L) {
    for (int i = 0; i < sqList.length / 2; i++) {
        ElemType temp = L[0];
        L[i] = L[length - i - 1]
        L[length - i - 1] = temp;
    }
}


//对于一个长度为n的顺序表L，编写一个时间复杂度为O(n), 空间复杂度为O（1）的算法，该算法要求删除
//顺序表中所有元素值为x的元素
void eraseValueX(sqList& L) {
    int moveNum = 0;
    for (int i = 0; i < L.length; i++) {
        if (L[i] == x) {
            moveNum++;
        } else {
            L[i - moveNum] = L[i];
        }
    }
    L.length -= moveNum;
}


//从有序顺序表中删除其值再给定值s与t之间的元素，如果s或者t不合理或者表为空
//则返回错误信息并退出
bool eraseValues2t(sqList& L, int min, int max) {
    if (L.length == 0 || max > min) {
        return false;
    }
    int moveCnt = 0;
    for (int i = 0; i < L.length; i++) {
        if (L[i] > min && L[i] < max) {
            moveCnt++;
        } else {
            L[i - moveCnt] = L[i];
        }
    }
    L.length -= moveCnt;
    return true;

}

//从有序表中删除所有值重复的元素
bool earseSame(sqList& L) {
    if (L.length == 0) {
        return false;
    }

    int moveCnt = 0;
    for (int i = i; i < L.length; i++) {
        if (L[i - 1] == L[i]) {
            moveCnt ++;
        } else {
            L[i - moveCnt] = L[i];
        }
    }
    L.length -= moveCnt;
    return true;
}


//将两个有序的顺序表合并成一个新的有序表
bool combine(sqList& L1, sqList& L2, sqList& R) {
    if (L1.length + L2.length > R.maxSize) {
        return false;
    }
    int i1 = 0;
    int i2 = 0;
    int iR = =0;

    while (i1 < L1.length && L2.length) {
        if (L1[i1] < L2[i2]) {
            R[iR] = L1[i1];
            i1 ++;
        } else {
            R[iR] = L1[i2];
            i2 ++;
        }
        iR++
    }

    while (i1 < L1.length) {
        R[iR] = L1[i1];
        i1 ++;
    }

    while (i2 < L2.length) {
        R[iR] = L2i1];
        i2 ++;
    }

    R2.length = L1.length + L2.length;
    return true;
}


//两个顺序表前后紧贴放在内存中，更换他们的顺序
//算法：先将整个数组逆序，然后将数组的前n个和后m个全部翻转
typedef int DataType;
void reverse(DataType* array, int size) {
	for (int i = 0; i < size; i++) {
		DataType temp = array[i];
		array[i] = array[size - i];
		array[size - i] = temp;
	}
}

void exchange(DataType* array, int sizeA, int sizeB) {
	reverse(array, sizeA+sizeB);
	reverse(array, sizeB);
	reverse(array + sizeA, sizeB);
}


//线性表(a1, a2, a3, ..., an)中的元素有序












