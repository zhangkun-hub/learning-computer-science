/*
栈(stack)：
一、定义：栈是限定仅在表尾进行插入或删除操作的线性表(其中不含元素的称为空栈)。
        即栈的修改按照后进先出的原则进行。因此栈又称为后进先出(Last In First Out, LIFO)的线性表。
        
    在栈中，其表尾端有其特殊含义，称为栈顶(top)，相应地，表头端称为栈底(bottom)。


二、基本操作(只有两个)：进栈(push)和出栈(pop)，前者相当于插入，后者则是删除最后插入的元素。

    举例：假设S=(a1,a2,…,an)，则称a1为栈底元素，an为栈顶元素。栈中元素按a1,a2,…,an的次序进栈，
        出栈的第一个元素应为栈顶元素。
    
三、栈的两种结构方式：
    1.顺序结构：与线性表的顺序结构(顺序表)一致，所以仍然用数组存储(见该节代码内容)
        注意：
            1.可用变量存储栈顶的下标索引，称为栈顶指针(但不是指针)。
            2.此处栈的数据索引规定从0开始(当然完全可以规定从1开始)

    2.链式结构：与线性表的链式结构(链表)一致，所以仍然用节点表示(见3-2节代码内容)
        注意：
            1.栈的链式结构中，一般将头节点做为栈顶，方便操作，所以一般栈顶不存储数据。
            2.实际应用中，更多的是用栈的顺序结构而非链式结构。
*/
// ==============================================
// ========= 栈的顺序结构创建与各种操作 ===========
// ==============================================
#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int

// 1.栈的顺序结构定义
typedef struct{
    ElemType* data; // 定义数组指针，指向动态分配的数组空间
    int top;        // top用来保存栈顶元素的下标值(就像指着栈顶一样，又称栈顶指针，但不是指针)
}Stack;


// 2.栈的初始化
Stack* initStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    s->top = -1; // 最开始是空栈，栈顶的下标为-1(注意：此处栈的存储数据下标从0开始)
    return s;
}


// 3.判断栈是否为空栈(空栈则返回值为1，否则为0)
int isEmpty(Stack* s)
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 1;
    }
    else
    {
        return 0;
    }
} 


// 4.进栈(push)
int push(Stack* s, ElemType e)
{
    if (s->top >= MAXSIZE - 1)
    {
        printf("栈已满\n");
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
}


// 5.出栈(pop)
int pop(Stack* s, ElemType* e)
// ElemType* e含义: 定义一个ElemType类型的变量m来存储被删除的数据，然后向函数传入该变量的地址&m
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 0;
    }
    *e = s->data[s->top]; // 将删除的数据值赋值给*e，通过指针特性传递给变量m，从而记录该数据
    s->top--;
    return 1;
}


// 6.获取栈顶元素
int getTop(Stack* s, ElemType* e)
// ElemType* e含义: 定义一个ElemType类型的变量m来存储栈顶元素，然后向函数传入该变量的地址&m
{
    if (s->top == -1)
    {
        printf("空栈\n");
        return 0;        
    }
    *e = s->data[s->top]; // 将栈顶元素赋值给*e，通过指针特性传递给变量m，从而记录该元素
    return 1;
}


int main()
{
    // 声明一个栈s并初始化
    Stack* s = initStack();
    printf("初始化成功，目前栈顶为: %d\n", s->top); // 初始化成功，目前栈顶为: -1
    printf("目前占用内存%zu字节\n", sizeof(s->data)); // 目前占用内存8字节

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
    ElemType delData;  // 用于保存被删除的数据
    pop(s, &delData);
    printf("被删除的数据为: %d\n", delData); // 被删除的数据为: 5

    // 获取栈顶元素
    ElemType top;
    getTop(s, &top);
    printf("栈顶元素为: %d\n", top); // 栈顶元素为: 4


    free(s);



    return 0;
}