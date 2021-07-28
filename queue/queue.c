#include <stdlib.h>

#include "queue.h"

int lengthSqQueue(SqQueue* Q) {
    if (Q == NULL) { return -1; }
    return (Q->rear - Q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

int enSqQueue(SqQueue* Q, QElemType e) {
    if (Q == NULL) { return -1; }
    if ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front) { return -1; }
    Q->data[Q->rear] = e;
    Q->rear          = (Q->rear + 1) % MAX_QUEUE_SIZE;
    return 0;
}

int deSqQueue(SqQueue* Q, QElemType* e) {
    if (Q == NULL || e == NULL) { return -1; }
    if (Q->front == Q->rear) { return -1; }
    *e       = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
    return 0;
}

int enLinkQueue(LinkQueue* Q, QElemType e) {
    if (Q == NULL) { return -1; }
    QNode* node   = (QNode*)malloc(sizeof(QNode));
    node->data    = e;
    node->next    = NULL;
    Q->rear->next = node;
    Q->rear       = node;
    return 0;
}

int deLinkQueue(LinkQueue* Q, QElemType* e) {
    if (Q == NULL || e == NULL) { return -1; }
    if (Q->front == Q->rear) { return -1; }
    //P为出列的数据
    QNode* p       = Q->front->next;
    *e             = p->data;
    Q->front->next = p->next;
    //如果出列的数据是最后一个数据，则出列后链表为空，此时需要将链表尾部指针指向表头
    if (Q->rear == p) { Q->rear = Q->front; }
    free(p);
    return 0;
}