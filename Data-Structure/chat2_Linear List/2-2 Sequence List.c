/*
顺序表(sequence list)：
一、线性表的顺序表示：指的是用一组地址连续的存储单元依次存储线性表的数据元素(即数组存储)。
        假设线性表的每个元素需占用m个存储单元，并以所占的第一个单元的存储地址作为数据元素的
    存储位置。则线性表中第i+1个数据元素的存储位置LOC(ai+1)和第i个数据元素的存储位置LOC(ai)
    之间满足下列关系：
                            LOC(ai+1)=LOC(ai)+m
    一般来说，线性表的第i个数据元素ai的存储位置为：
                            LOC(ai)=LOC(a1)+(i−1)×m
    式中 LOC(a1)是线性表的第一个数据元素a1的存储位置，通常称做线性表的起始位置或基地址。

二、顺序表定义：线性表的这种机内表示称做线性表的顺序存储结构或顺序映像(sequential mapping)，
        通常，称这种存储结构的线性表为顺序表。

三、特点：为表中相邻的元素ai和ai+1赋以相邻的存储位置LOC(ai)和LOC(ai+1)。
        换句话说，以元素在计算机内“物理位置相邻”来表示线性表中数据元素之间的逻辑关系。每一个
    数据元素的存储位置都和线性表的起始位置相差一个和数据元素在线性表中的位序成正比的常数。
    由此，只要确定了存储线性表的起始位置，线性表中任一数据元素都可随机存取，所以线性表的
    顺序存储结构是一种随机存取的存储结构。

四、顺序表的建立：可以由一个结构体完整的表示。
    注：建立与各种操作见下面代码(以下是栈内存下的操作，单纯学习用，实际中都以2-3的堆内存操作)

五、顺序表的优缺点：
    1.优点：
        (1)随机访问效率极高(O(1)复杂度，是其最大的优势): 
            通过基地址和下标，可以在常数时间内访问任何元素。这使得它非常适合查找、排序等操作

        (2)内存局部性好，缓存命中率高：
            由于数据连续存储，一次可以加载一块数据到CPU高速缓存，后续访问速度极快。

        (3)结构简单，实现容易：逻辑和物理顺序一致，代码易于编写和调试。

    2.缺点：
        (1)大小固定或调整成本高：
            静态分配: 创建时就需要指定最大容量，容易造成空间浪费(用不完)或溢出(不够用)。

            动态分配: 虽然可以扩容(如C++的vector)，但扩容时通常需要申请一块更大的连续内存，
                并将原有数据全部复制过去，这是一个O(n)​的耗时操作。

        (2)插入和删除效率低(O(n))：
            插入/删除一个元素，需要移动其后方所有元素以保持连续性，平均需要移动一半的元素。
*/
// =========================================================================
// ========= 栈内存下建立顺序表(只用于学习，实际中都以2-3的堆内存操作) ==========
// =========================================================================
#include<stdio.h>

#define MAXSIZE 100   // 通过宏定义，将MAXSIZE设置成100（具体含义见C-learning的9-7）
typedef int ElemType; // 给int类型起别名ElemType，使得以后如果改为其他类型，只需修改此处int

// 1.线性表的顺序结构定义
// 栈内存下的定义
typedef struct{
    ElemType data[MAXSIZE];   // 创建长度为MAXSIZE、类型为ElemType的data数组
    int length;               // length表示顺序表中元素的个数
}SeqList;  


// 2.顺序表的初始化
// 栈内存的操作
void initList(SeqList* L)
{
    L->length = 0;  // 刚开始顺序表无元素，所以长度为0。
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
        // 将所有pos之后(包括pos位置)的元素往后移一位
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
int deleteElem(SeqList* L, int pos, ElemType* e)  // pos是删除数据的位置
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
    // (注意:最后一个数据不用管(包括是pos情形),因为删除后length长度-1,从而不影响以后的增删改查操作)
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
    // 声明一个顺序表并初始化
    SeqList list;
    initList(&list); 
    printf("初始化成功，目前长度占用%d\n", list.length); // 初始化成功，目前长度占用0
    printf("目前占用内存%zu字节\n", sizeof(list.data)); // 目前占用内存400字节

    // 在顺序表尾部添加元素
    appendElem(&list, 88);
    appendElem(&list, 45);
    appendElem(&list, 43);
    appendElem(&list, 17);

    // 遍历整个顺序表(注意：顺序表的长度由length决定而不是由数组决定)
    listElem(&list); // 88 45 43 17

    // 在第2个位置插入数据18（注意：顺序表的元素位置是从1开始）
    insertElem(&list, 2, 18);
    listElem(&list); // 88 18 45 43 17 

    // 删除第2个位置的数据，并保存该删除的数据
    ElemType delData;  // 用于保存被删除的数据
    deleteElem(&list, 2, &delData);
    listElem(&list); // 88 45 43 17
    printf("被删除的数据为：%d\n", delData); // 被删除的数据为：18
    
    // 查找数据有没有在顺序表中
    printf("%d\n", findElem(&list, 40)); // 0（即没有40这个数据在顺序表中）
    printf("%d\n", findElem(&list, 43)); // 3

    // 顺序表的修改操作：(无需设置函数，直接进行修改)
    // 修改第i个位置的值为e：顺序表名.data[i+1] = e; 例如修改第2个元素为18
    printf("%d\n", list.data[3] = 18); // 18



    return 0;
}