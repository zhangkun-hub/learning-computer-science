/*
队列(Queue)：
一、定义：队列是一种先进先出(First In First Out, FIFO)的线性表，即：
            它只允许在表的一端进行插入，而在另一端删除元素。

    在队列中：
        允许插入的一端称为队尾(rear)，可用变量存储其下标索引，称为队尾指针。
        允许删除的一端称为队头(front)，可用变量存储其下标索引，称为队头指针。

    举例：假设队列为q = (a₁, a₂, …, aₙ)，那么：a₁就是队头元素，aₙ就是队尾元素。

    注意：不含元素的空队列的充要条件为：队头和队尾重合，即 front == rear。
        


二、基本操作(只有两个)：进队和出队，前者是在队尾插入，后者则是删除队头的元素。

    举例：队列中的元素是按照 a₁, a₂, …, aₙ 的顺序进入的，退出队列也只能按照这个次序依次退出。
        也就是说，只有在 a₁, a₂, …, aₙ₋₁ 都离开队列之后，aₙ才能退出队列。


三、队列的两种结构方式：
    1.顺序结构：与线性表的顺序结构(顺序表)一致，所以仍然用数组存储(见该节代码内容)
        注意：
            (1)对于非空队列，一般队头会存储数据，而队尾不存储数据，所以其索引为末尾数据索引+1。
            (2)此处队列的数据索引规定从0开始(当然完全可以规定从1开始)。
            (3)顺序结构中，队头指针和队尾指针不是真的指针、。

    2.链式结构：与线性表的链式结构(链表)一致，所以仍然用节点表示(见3-4节代码内容)
        注意：
            (1)对于非空队列，一般队尾会存储数据，而队头指向头节点，一般不存储数据。
            (2)链式结构中，队头队尾是真指针。
*/
// ================================================
// ========= 队列的顺序结构创建与各种操作 ===========
// ================================================
#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int

// 1.队列的顺序结构定义
typedef struct{
    ElemType* data; // 定义数组指针，指向动态分配的数组空间
    int front;      // top为队头指针(不是指针)，用来保存队头的下标值
    int rear;       // rear为队尾指针(不是指针)，用来保存队尾的下标值
}Queue;


// 2.队列的初始化
Queue* initQueue()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);

    // 最开始是空队列，队头和队尾重合，此处初始化下标记为0(即队列的存储数据下标从0开始)
    Q->front = 0; 
    Q->rear = 0;  
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


// 4.出队————删除队头的元素
int dequeue(Queue* Q, ElemType* e)
// ElemType* e含义: 定义一个ElemType类型的变量m来存储被删除的数据，然后向函数传入该变量的地址&m
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;
    }
    *e = Q->data[Q->front]; // 将删除的队头数据值赋值给*e，通过指针特性传递给m，从而记录该数据
    Q->front++;             // 队头指针向队尾方向移动1格，以达到删除(抛弃)原队头数据的目的
    return 1;
}


// 5.调整队列，使得数据索引从0开始(这在入队操作中必须要用到的函数)
// 注意：当队列已满时函数返回0，否则返回1
int queueFull(Queue* Q)
{
    // 队头索引不在0处并且队尾索引在MAXSIZE以内(for循环内容导致)，则调整队列使得索引从0开始
    if (Q->front > 0 && Q->rear <= MAXSIZE)
    {
        int step = Q->front; // step表示队列的数据索引要移动的步数
        for (int i = Q->front; i < Q->rear; i++)
        {
            Q->data[i - step] = Q->data[i];
        }
        Q->front = 0;
        Q->rear = Q->rear - step;
        return 1;
    }
    // 队头索引在0处且队尾索引在MAXSIZE及以外，则队列已满
    else if (Q->front = 0 && Q->rear >= MAXSIZE)
    {
        printf("队列已满\n");
        return 0;
    }
}


// 6.入队————在队尾添加元素
int equeue(Queue* Q, ElemType e) 
{
    // 注：因为队尾不存储数据，所以其索引是末尾数据索引+1。那么当队列满时，其索引最小为MAXSIZE
    if (Q->rear >= MAXSIZE) 
    {
        // 满足队尾指针条件并不能保证队列已满，因为出队情形，队头索引并不一定为0，所以还要再判断
        if (!queueFull(Q)) // 当队列已满时该函数返回0，未满时会把队列数据移动到队头指向0处
        {
            printf("队列已满\n");
            return 0;
        }
            
    }
    Q->data[Q->rear] = e;
    Q->rear++;
    return 1;
}


// 7.获取队头元素
int getHead(Queue* Q, ElemType* e)
// ElemType* e含义: 定义一个ElemType类型的变量m来存储队头元素，然后向函数传入该变量的地址&m
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;        
    }
    *e = Q->data[Q->front]; // 将队头元素赋值给*e，通过指针特性传递给变量m，从而记录该元素
    return 1;
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