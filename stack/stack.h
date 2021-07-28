#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ADT 栈(stack)
// Data
//     同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
// Operation
//     InitStack(*S):    初始化操作，建立一个空栈S。
//     DestroyStack(*S): 若栈存在，则销毁它。
//     ClearStack(*S):   将栈清空。
//     StackEmpty(S):    若栈为空，返回true，否则返回false。
//     GetTop(S, *e):    若栈存在且非空，用e返回S的栈顶元素。
//     Push(*S, e):      若栈S存在，插入新元素e到栈S中并成为栈顶元素。
//     Pop(*S, *e):      删除栈S中栈顶元素，并用e返回其值。
//     StackLength(S):   返回栈S的元素个数。
// endADT

#define MAX_STACK_SIZE 1000

typedef int SElemType;

typedef struct {
    SElemType data[MAX_STACK_SIZE];
    int       top;
} SqStack;

typedef struct {
    SElemType data[MAX_STACK_SIZE];
    int       top1;
    int       top2;
} SqDoubleStack;

typedef struct StackNode {
    SElemType         data;
    struct StackNode* next;
} StackNode;

typedef struct LinkStack {
    StackNode* top;
    int        count;
} LinkStack;

int pushSqStack(SqStack* S, SElemType e);
int popSqStack(SqStack* S, SElemType* e);

int pushSqBoubleStack(SqDoubleStack* S, SElemType e, int stackNumber);
int popSqBoubleStack(SqDoubleStack* S, SElemType* e, int stackNumber);

int pushLinkStack(LinkStack* S, SElemType e);
int popLinkStack(LinkStack* S, SElemType* e);

#ifdef __cplusplus
}
#endif
