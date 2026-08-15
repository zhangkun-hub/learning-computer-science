// =============================================================
// ========= 堆内存下创建顺序表（实际开发中更有用的方式） ==========
// =============================================================
#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100（具体含义见C-learning的9-7）
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int

// 1.线性表的顺序结构定义
// 堆内存下的定义方式（更常用）
typedef struct{
    ElemType* data; // 定义数组指针，指向动态分配的数组空间
    int length;     // length表示顺序表中元素的个数
}SeqList;
// 特别注意：ElemType* data只是定义了指针，并没有实际分配数组空间，这要在顺序表的初始化中进行分配
// 原因：控制结构和数据存储分离，更灵活。


// 2.顺序表的初始化
// 堆内存的操作（更常用）
SeqList* initList()
{
    // 为SeqList结构体类型分配堆内存空间，并由指针L来指向。
    // 注意: SeqList结构体内只包含一个指针data和一个int，并无数组空间。
    SeqList* L = (SeqList*)malloc(sizeof(SeqList)); 
    // 为实际存储数据的数组来分配堆内存空间，并由指针data来指向。
    L->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    L->length = 0;  // 刚开始顺序表无元素，所以长度为0。

    return L;
}


// 特别注意：以下操作在不论在栈内存还是堆内存代码完全一致不做任何修改！！！
// 3.在顺序表尾部添加元素
int appendElem(SeqList* L, ElemType e)  // e表示向顺序表L中添加的元素(所有元素类型必须一致)
{
    // 判断顺序表是否饱和了
    if(L->length >= MAXSIZE)
    {
        printf("顺序表已满\n");
        return 0;
    }
    // 添加元素
    L->data[L->length] = e;  // 向顺序表添加e这个元素
    L->length++;             // 添加后，顺序表的元素个数+1
    return 1;    // 返回1表示成功，返回0表示失败(常用的表示成功失败的写法)
}


// 4.顺序表的遍历操作
void listElem(SeqList* L)
{
    for(int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}


// 5.顺序表的插入元素操作
int insertElem(SeqList* L, int pos, ElemType e) // pos是插入顺序表的位置(注意：从1开始)
{
    // 判断顺序表是否饱和了
    if(L->length >= MAXSIZE)
    {
        printf("顺序表已满\n");
        return 0;
    }
    // 判断是否插入错误位置(即pos是否小于1或大于length)
    if(pos < 1 || pos > L->length)
    {
        printf("插入位置错误\n");
        return 0;
    }
    // 满足条件执行插入操作
    if(pos >= 1 && pos <= L->length)
    {
        // 将所有pos之后的元素往后移一位
        for(int i = L->length-1; i >= pos-1; i--)
        {
            L->data[i+1] = L->data[i];
        }
        L->data[pos-1] = e; // 在pos位置处插入元素e
        L->length++;        // 插入后，顺序表的长度+1
    }
    return 1;
}


// 6.顺序表的删除操作
int deleteElem(SeqList* L, int pos, ElemType* e) // pos是删除数据的位置
// ElemType* e含义: 定义一个ElemType类型的变量m用来存储被删除的数据，然后向函数传入该变量的地址&m
{
    // 判断是否是空表
    if(L->length == 0)
    {
        printf("空表\n");
        return 0;
    }
    // 判断是否删除错误位置(即pos是否小于1或大于length)
    if(pos < 1 || pos > L->length)
    {
        printf("删除数据位置错误\n");
        return 0;
    }    
    *e = L->data[pos-1]; // 将删除的数据值赋值给*e，通过指针特性传递给变量m，从而记录该数据内容
    // 将pos之后的数据均向前一位进行覆盖，从而达到删除数据的操作
    // (注意：最后一个数据不用管，因为删除后length长度-1，从而不影响以后的增删改查操作)
    if(pos >= 1 && pos < L->length)
    {
        for(int i = pos; i < L->length; i++)
        {
            L->data[i-1] = L->data[i];
        }
    }
    L->length--;  // 删除后，顺序表的长度-1
    return 1;
}


// 7.顺序表的查找操作
int findElem(SeqList* L, ElemType e)
{
    // 遍历整个顺序表看看有没有与e相等的元素，有就返回该元素的位置，没有就返回0
    for(int i = 0; i < L->length; i++)
    {
        if(L->data[i] == e)
        {
            return i + 1;
        }
    }
    return 0;
}



int main()
{
    // 声明一个顺序表list并初始化
    SeqList* list = initList();
    printf("初始化成功，目前长度占用%d\n", list->length); // 初始化成功，目前长度占用0
    printf("目前占用内存%zu字节\n", sizeof(list->data)); // 目前占用内存8字节

    // 在顺序表尾部添加元素
    appendElem(list, 88);
    appendElem(list, 45);
    appendElem(list, 43);
    appendElem(list, 17);

    // 遍历整个顺序表(注意：顺序表的长度由length决定而不是由数组决定)
    listElem(list); // 88 45 43 17

    // 在第2个位置插入数据18（注意：顺序表的元素位置是从1开始）
    insertElem(list, 2, 18);
    listElem(list); // 88 18 45 43 17 

    // 删除第2个位置的数据，并保存该删除的数据
    ElemType delData;  // 用于保存被删除的数据
    deleteElem(list, 2, &delData);
    listElem(list); // 88 45 43 17
    printf("被删除的数据为：%d\n", delData); // 被删除的数据为：18
    
    // 查找数据有没有在顺序表中
    printf("%d\n", findElem(list, 40)); // 0（即没有40这个数据在顺序表中）
    printf("%d\n", findElem(list, 43)); // 3

    // 顺序表的修改操作：(无需设置函数，直接进行修改)
    // 修改第i个位置的值为e：顺序表名->data[i+1] = e; 例如修改第2个元素为18
    printf("%d\n", list->data[3] = 18); // 18

    free(list);



    return 0;
}