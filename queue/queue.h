#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ADT 队列(Queue)
// Data
//     同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
// Operation
//     InitQueue(*Q):    初始化操作，建立一个空队列Q。
//     DestroyQueue(*Q): 若队列Q存在，则销毁它。
//     ClearQueue(*Q):   将队列Q清空。
//     QueueEmpty(Q):    若队列Q为空，返回true，否则返回false。
//     GetHead(Q, *e):   若队列Q存在且非空，用e返回队列Q的队头元素。
//     EnQueue(*Q, e):   若队列Q存在，插入新元素e到队列Q中并成为队尾元素。
//     DeQueue(*Q, *e):  删除队列Q中队头元素，并用e返回其值。
//     QueueLength(Q):   返回队列Q的元素个数
// endADT

typedef int QElemType;

#define MAX_QUEUE_SIZE 1000

typedef struct {
    QElemType data[MAX_QUEUE_SIZE];
    int       front;
    int       rear;
} SqQueue;

typedef struct QNode {
    QElemType     data;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front;
    QNode* rear;
} LinkQueue;

int lengthSqQueue(SqQueue* Q);
int enSqQueue(SqQueue* Q, QElemType e);
int deSqQueue(SqQueue* Q, QElemType* e);

int enLinkQueue(LinkQueue* Q, QElemType e);
int deLinkQueue(LinkQueue* Q, QElemType* e);

#ifdef __cplusplus
}
#endif
