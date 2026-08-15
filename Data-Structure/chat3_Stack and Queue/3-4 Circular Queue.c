/*
队列顺序结构的数组改进————循环队列
一、引入原因：
        由3-3知，队列的顺序结构在进行入队操作时，当队头指向的不是0时必须移动队列到0，那么可以想象，
    对存储大量数据的队列来说，如果队头前只有一个空，那么就为那一个空就要移动海量的数据，效率低下。
    要解决这个问题，可以将数组索引的首尾相连形成一个环来解决，具体定义与解决方式见下面。

二、定义：在队列的顺序结构中，数组索引首尾相连形成一个环，即数组最后一个索引的下一个索引就是索引0，
        当然数组首尾的内存地址并不相邻。

三、实现方式：在入队和出队中，对于队头指针和队尾指针的移动，在原操作基础上对整个数组长度取余即可。
    1.原理：通过取余操作可以实现队头队尾的索引循环的操作，这就相当于数组索引首尾相连形成一个环。
        注意：因为取余操作，最终队头和队尾指针值只局限在数组索引的范围内。

    2.代码实现(与前面3-3的代码基本完全一样，只有入队和出队操作有区别)：设数组长度为MAXSIZE
        (1)入队：队尾添加元素时，队尾从之前的Q->rear++变成：Q->rear = (Q->rear + 1) % MAXSIZE   

        (2)出队：队头删除元素时，队头从之前的Q->front++变成：Q->front = (Q->front+1) % MAXSIZE


四、特性：
    1.解决了队列顺序结构中队头不为0时需要移动整个数据填补空缺的操作，提升效率。

    2.为避免跟空队列判定条件冲突，满队列的判断条件为：(Q->rear + 1) % MAXSIZE == Q->front，
        但这就造成了数组空间会留有一个空位无法填充的情形出现，也就是队列满了但数组空间并未满。
*/
// ============================================
// ========= 循环队列的创建与各种操作 ===========
// ============================================
#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int

// ==============与顺序结构完全相同的部分==============
// 1.循环队列的结构定义
typedef struct{
    ElemType* data; 
    int front;      
    int rear;       
}Queue;

// 2.循环队列的初始化
Queue* initQueue()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    Q->front = 0; 
    Q->rear = 0;  
    return Q;
}

// 3.判断循环队列是否为空队列(空队列则返回值为1，否则为0)
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

// 4.获取队头元素
int getHead(Queue* Q, ElemType* e)
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;        
    }
    *e = Q->data[Q->front]; 
    return 1;
}


// ==============与顺序结构有区别的部分==============
// 5.循环队列的入队(相比顺序结构最大的优势，因为无需调整队列，极大提升效率)
int equeue(Queue* Q, ElemType e) 
{
    // 循环队列已满的判断条件(画图来理解,其中为避免跟空队列条件冲突,所以会+1,但造成数组空缺1位)
    if ((Q->rear + 1) % MAXSIZE == Q->front) 
    {
        printf("队列已满\n");
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE; // 与顺序结构有区别的部分
    return 1;
}

// 6.循环队列的出队
int dequeue(Queue* Q, ElemType* e)
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;
    }
    *e = Q->data[Q->front]; 
    Q->front = (Q->front + 1) % MAXSIZE; // 与顺序结构有区别的部分
    return 1;
}




int main()
{
    // 声明一个循环队列Q并初始化
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
    ElemType delData;  // 用于保存被删除的数据
    dequeue(Q, &delData);
    printf("被删除的数据为: %d\n", delData); // 被删除的数据为: 1

    // 获取队头元素
    ElemType head;
    getHead(Q, &head);
    printf("队头元素为: %d\n", head); // 队头元素为: 2


    free(Q);



    return 0;
}