/*
注意：
1.队列的链式结构中，对于非空队列，一般队尾会存储数据，而队头指向头节点，一般不存储数据。

2.链式结构中，队头队尾是真指针。
*/
// ================================================
// ========= 队列的链式结构创建与各种操作 ===========
// ================================================
#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;

// 1.队列的链式结构定义
// 1.1 链式结构的节点定义
typedef struct QueueNode{
    ElemType data;          // 创建存储节点的数据元素
    struct QueueNode* next; // 创建存储下一个节点的内存地址
}QueueNode;

// 1.2 真正表达队列的结构体定义(因为存储的队头队尾指针是队列的核心，队列各种操作都是基于此进行)
typedef struct{
    QueueNode* front; // 队头指针
    QueueNode* rear;  // 队尾指针
}Queue;


// 2.队列的初始化————队头的创建(即头节点)
Queue* initQueue()
{
    // 节点的初始化————头节点的创建
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = 0;
    node->next = NULL; // 因为之后没有节点，所以指向空内存地址

    // 队列结构体的初始化
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = node;   // 队头指向头节点(始终)
    Q->rear = node;    // 队尾指向头节点(空队列时)
    return Q; 
}


// 3.判断队列是否为空队列(空队列则返回值为1，否则为0)
int isEmpty(Queue* Q)  
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 1;
    }
    else
    {
        return 0;
    }
} 


// 4.入队————采用尾插法添加元素(因为rear指向尾节点，所以无需遍历操作)
void equeue(Queue* Q, ElemType e) 
{
    // 创建新的尾节点并添加元素e
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = e;
    node->next = NULL;

    Q->rear->next = node; // 队尾指针指向的原尾节点与新尾节点相连
    Q->rear = node;       // 队尾指针指向新尾节点
}


// 5.出队————即删除队头(头节点)指向的第一个节点
int dequeue(Queue* Q, ElemType* e) 
// ElemType* e含义: 定义一个ElemType类型的变量m来存储被删除的数据，然后向函数传入该变量的地址&m
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;
    }
    QueueNode* node = Q->front->next; // node为要删除的节点
    *e = node->data; // 将删除的数据值赋值给*e，通过指针特性传递给变量m，从而记录该数据
    Q->front->next = node->next; // 将队头节点与node的下一个节点相连

    // 处理要删除的节点是尾节点情形
    if (Q->rear == node)
    {
        Q->rear = Q->front; // 尾节点删除后，队尾指针指向队头节点
    }
    free(node);
    return 1;
}


// 6.获取队头元素(即队头指向的下一个节点)
int getTop(Queue* Q, ElemType* e) 
// ElemType* e含义: 定义一个ElemType类型的变量m用来存储队头元素，然后向函数传入该变量的地址&m
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;        
    }
    *e = Q->front->next->data; // 将队头元素赋值给*e，通过指针特性传递给变量m，从而记录该元素
    return 1;
}


// 7.释放队列(即清空队列，队头不释放)
void freeStack(Queue* Q) 
{
    QueueNode* p = Q->front->next; // 指针p: 记录当前节点(从头节点开始)的后继节点，并不断释放p
    QueueNode* q;                  // 指针q: 记录指针p的后继节点

    while(p != NULL) // 当前节点的后继节点p如果是NULL，那么当前节点便是尾节点(在上个循环已释放)
    {
        q = p->next;
        free(p);
        p = q;
    }
    Q->rear = Q->front;
    Q->front->next = NULL;
}



int main()
{
    // 声明一个队列Q并初始化
    Queue* Q = initQueue();

    // 判断是否为空队列
    printf("%d\n", isEmpty(Q));  // 空队列  1（返回值1表示空队列）

    // 入队
    equeue(Q, 1);
    equeue(Q, 2);
    equeue(Q, 3);
    equeue(Q, 4);
    equeue(Q, 5);

    // 判断是否为空队列
    printf("%d\n", isEmpty(Q)); // 0 （返回值0表示非空队列）

    // 出队
    ElemType desData;  // 用于保存被删除的数据
    dequeue(Q, &desData);
    printf("被删除的数据为: %d\n", desData); // 被删除的数据为: 1

    // 获取队头元素
    ElemType top;
    getTop(Q, &top);
    printf("队头元素为: %d\n", top); // 队头元素为: 2

    // 释放队列
    freeStack(Q);   // 清空队列
    free(Q->front); // 释放头节点
    free(Q);        // 释放队列Q



    return 0;
}