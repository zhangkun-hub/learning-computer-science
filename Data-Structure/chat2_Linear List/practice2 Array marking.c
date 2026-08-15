/*
题目：用单链表保存n个整数(n为正整数)，节点结构为[data][link]，且|data|<=n。要求对链表中data的
    绝对值相等的节点，仅保留第一次出现的节点而删除其余绝对值相等的节点。

思路：数组标记法
    步骤1: 由于题目约束|data|≤n(n为链表节点数的上限)，可创建一个大小为n+1的数组visited，存储的值
        只有0或1(即布尔数组)，用于标记某个绝对值是否已出现过(出现过为1，否则为0)。

        注：由步骤2的思路可以理解为什么要创建n+1长度的数组visited，因为其第x个索引的x表示链表可能的
            某一个数据绝对值(+1是因为数组索引从0开始)

    步骤2: 遍历单链表时，对当前节点的data取绝对值得到absData：
        (1)若visited[absData]为0，说明是该绝对值首次出现，标记visited[absData]=1并保留该节点，
            继续遍历下一个节点。

        (2)若visited[absData]为true，说明该绝对值已出现过，删除当前节点(通过调整前驱节点的
            next指针跳过当前节点)，并释放内存。
*/
#include<stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;      
    struct node* next;  
}Node;

// 单链表初始化————头节点的创建
Node* initList();

// 尾插法
Node* get_tail(Node* L);                  // 步骤1：先获取尾节点地址
Node* insertTail(Node* tail, ElemType e); // 步骤2：开始尾插

// 单链表的遍历
void listNode(Node* L);

// 获取单链表的长度(包括头节点)
int listLength(Node* L);

// 单链表的释放(即清空链表，头节点不释放)
void freeList(Node* L);



// 练习：通过数组标记法删除绝对值相同的节点
int removeNode(Node* L, int n) // L为头节点，n为链表中绝对值最大的数
{
    Node* p = L;
    int* q = (int*)malloc(sizeof(int) * (n+1)); // q为数组标记法中的数组指针
    int index;   // 作为数组q的索引使用

    // 遍历数组q，并初始化值为0
    for (int i = 0; i < n+1; i++)
    {
        *(q + i) = 0; 
    }

    // 遍历链表，通过数组标记法删除绝对值相同的节点
    while(p->next != NULL)
    {
        // 将链表数据绝对值当作数组p的索引index
        index = abs(p->next->data); 

        // 判断q[index]是否为0，若为0则变为1，若不为0，则删除该索引所对应的节点
        if(*(q + index) == 0)
        {
            *(q + index) = 1;
            p = p->next;
        }
        else
        {
            Node* temp = p->next;
            p->next = temp->next;
            free(temp);
        }
    }
    free(q);
}



int main()
{
    // 声明链表并初始化
    Node* list = initList();

    // 使用尾插法插入数据与遍历
    Node* tail = get_tail(list);
    tail = insertTail(tail, 21);
    tail = insertTail(tail, -15);
    tail = insertTail(tail, 15);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, -15);
    listNode(list); // 21 -15 15 7 -15

    // 练习：删除绝对值相同的节点
    removeNode(list, 21); 
    listNode(list); // 21 -15 7

    // 释放单链表
    freeList(list);
    printf("%d\n", listLength(list)); // 1(因为头节点不释放，而链表长度包括头节点，所以为1)

    // 删除头节点
    free(list);

    return 0;

}




// 单链表初始化————头节点的创建
Node* initList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL; 
    return head;
}

// 尾插法
// 步骤1：先获取尾节点地址
Node* get_tail(Node* L)   
{
    Node* p = L;
    while(p->next != NULL) 
    {
        p = p->next;
    }
    return p;
}

// 步骤2：开始尾插
Node* insertTail(Node* tail, ElemType e)   
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}

// 单链表的遍历
void listNode(Node* L) 
{
    Node* p = L->next;
    while(p != NULL) 
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 获取单链表的长度(包括头节点)
int listLength(Node* L) 
{
    Node* p = L;
    int len = 0; 
    while(p != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

// 单链表的释放(即清空链表，头节点不释放)
void freeList(Node* L) 
{
    Node* p = L->next; 
    Node* q;           

    while(p != NULL) 
    {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}