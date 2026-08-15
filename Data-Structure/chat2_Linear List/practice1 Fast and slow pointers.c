/*
链表的练习：查找链表中倒数第k个位置上的节点

O(n)复杂度下的实现方法————双指针(或快慢指针)
    思路：创建两个指针，指针1比指针2先走k个节点，于是称先走的指针1为快指针，而指针2为慢指针。
        此时两个指针同时走过相同节点数，直到快指针指向NULL为止，此时慢指针便指向链表的倒数第
        k个位置上的节点，由此在O(n)复杂度下的完成了要求。
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



// 练习：通过快慢指针查找单链表倒数第k个数据
int findNodeFS(Node* L, int k) // L为头节点，k为要查找的倒数第k个数据
{
    Node* fast = L->next;
    Node* slow = L->next;

    // 快指针fast比慢指针slow先走k步
    for(int i = 0; i < k; i++) 
    {
        fast = fast->next;
    }

    // 两指针一起走，直到快指针fast为空则停止，此时慢指针指向的便是倒数第k个数据
    while(fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    printf("倒数第%d个节点值为: %d\n", k, slow->data);
}


int main()
{
    // 声明链表并初始化
    Node* list = initList();

    // 使用尾插法插入数据与遍历
    Node* tail = get_tail(list);
    tail = insertTail(tail, 10);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);
    tail = insertTail(tail, 40);
    tail = insertTail(tail, 50);
    listNode(list);  // 10 20 30 40 50

    // 练习：查找单链表倒数第3个数据
    findNodeFS(list, 3); // 倒数第3个节点值为: 30

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