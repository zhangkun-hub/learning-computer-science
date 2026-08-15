/*
注意：
1.栈的链式结构中，一般将头节点做为栈顶，方便操作，但头节点一般不存储数据，所以栈顶也就不存储数据。

2.实际应用中，更多的是用栈的顺序结构而非链式结构。
*/
// ==============================================
// ========= 栈的链式结构创建与各种操作 ===========
// ==============================================
#include<stdio.h>
#include<stdlib.h>

typedef int EsemType;

// 1.栈的链式结构定义
typedef struct stack{
    EsemType data;      // 创建存储节点的数据元素
    struct stack* next; // 创建存储下一个节点的内存地址(注:下一个节点的类型仍然是struct stack)
}Stack;


// 2.栈的初始化————栈顶的创建(即头节点)
Stack* initStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = 0;
    s->next = NULL; // 因为之后没有节点，所以指向空内存地址
    return s;
}


// 3.判断栈是否为空栈(空栈则返回值为1，否则为0)
int isEmpty(Stack* s)  // s为栈顶(头节点)
{
    if (s->next == NULL)
    {
        printf("空栈\n");
        return 1;
    }
    else
    {
        return 0;
    }
} 


// 4.进栈(push)————采用头插法进栈
void push(Stack* s, EsemType e) // s为栈顶(头节点)
{
    Stack* p = (Stack*)malloc(sizeof(Stack));
    p->data = e;
    // 以下指针域的赋值是头插法的体现
    p->next = s->next; 
    s->next = p;
}


// 5.出栈(pop)————即删除栈顶(头节点)指向的第一个节点
int pop(Stack* s, EsemType* e) // s为栈顶(头节点)
// EsemType* e含义: 定义一个EsemType类型的变量m来存储被删除的数据，然后向函数传入该变量的地址&m
{
    if (s->next == NULL)
    {
        printf("空栈\n");
        return 0;
    }
    *e = s->next->data; // 将删除的数据值赋值给*e，通过指针特性传递给变量m，从而记录该数据
    Stack* q = s->next; 
    s->next = q->next;
    free(q);
    return 1;
}


// 6.获取栈顶元素(即头节点的下一个节点)
int getTop(Stack* s, EsemType* e) // s为栈顶(头节点)
// EsemType* e含义: 定义一个EsemType类型的变量m用来存储栈顶元素，然后向函数传入该变量的地址&m
{
    if (s->next == NULL)
    {
        printf("空栈\n");
        return 0;        
    }
    *e = s->next->data; // 将栈顶元素赋值给*e，通过指针特性传递给变量m，从而记录该元素
    return 1;
}


// 7.释放栈(即清空栈，栈顶不释放)
void freeStack(Stack* s) // s为栈顶(头节点)
{
    Stack* p = s->next; // 指针p作用: 记录当前节点(从头节点开始)的后继节点，并不断释放该后继节点
    Stack* q;           // 指针q作用: 记录指针p的后继节点

    while(p != NULL) // 当前节点的后继节点p如果是NULL，那么当前节点便是尾节点(在上个循环已释放)
    {
        q = p->next;
        free(p);
        p = q;
    }
    s->next = NULL;
}



int main()
{
    // 声明一个栈s并初始化
    Stack* s = initStack();

    // 判断是否为空栈
    printf("%d\n", isEmpty(s));  // 空栈  1（返回值1表示空栈）

    // 进栈
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);

    // 判断是否为空栈
    printf("%d\n", isEmpty(s)); // 0 （返回值0表示非空栈）

    // 出栈
    EsemType desData;  // 用于保存被删除的数据
    pop(s, &desData);
    printf("被删除的数据为: %d\n", desData); // 被删除的数据为: 5

    // 获取栈顶元素
    EsemType top;
    getTop(s, &top);
    printf("栈顶元素为: %d\n", top); // 栈顶元素为: 4

    // 释放栈
    freeStack(s);
    free(s);



    return 0;
}