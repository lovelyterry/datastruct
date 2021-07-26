#include <stdlib.h>

#include "stack.h"

int pushSqStack(SqStack* S, SElemType e) {
    if (S == NULL) { return -1; }

    if (S->top == MAX_STACK_SIZE - 1) { return -1; }
    S->data[++S->top] = e;
    return 0;
}

int popSqStack(SqStack* S, SElemType* e) {
    if (S == NULL || e == NULL) { return -1; }

    if (S->top == -1) { return -1; }
    *e = S->data[S->top--];
    return 0;
}

int pushSqBoubleStack(SqDoubleStack* S, SElemType e, int stackNumber) {
    if (S == NULL) { return -1; }

    if (S->top1 + 1 == S->top2) { return -1; }
    if (stackNumber == 1) {
        S->data[++S->top1] = e;
    } else if (stackNumber == 2) {
        S->data[--S->top2] = e;
    }
    return 0;
}

int popSqBoubleStack(SqDoubleStack* S, SElemType* e, int stackNumber) {
    if (S == NULL || e == NULL) { return -1; }

    if (stackNumber == 1) {
        if (S->top1 == -1) { return -1; }
        *e = S->data[S->top1--];
    } else if (stackNumber == 2) {
        if (S->top2 == MAX_STACK_SIZE) { return -1; }
        *e = S->data[S->top2++];
    }
    return 0;
}

int pushLinkStack(LinkStack* S, SElemType e) {
    if (S == NULL) { return -1; }

    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data      = e;
    node->next      = S->top;
    S->top          = node;
    S->count++;
    return 0;
}

int popLinkStack(LinkStack* S, SElemType* e) {
    if (S == NULL || e == NULL || S->count == 0) { return -1; }

    *e           = S->top->data;
    StackNode* p = S->top;
    S->top       = S->top->next;
    free(p);
    S->count--;
    return 0;
}
