/*
单链表的应用————反转链表
一、含义：即保持头节点不变，将头节点后的节点顺序反转，然后头节点指向尾节点，而第一个节点指向NULL。

二、实现思路：三指针法
        创建三个指针first、second和third，其中first指向NULL，second指向节点1(非头节点)，third
    指向节点2，然后将seocnd的指针域指向first，接着依次挪这三个指针，再将seocnd的指针域指向first，
    通过循环重复上述操作，到最后second指向NULL为止循环结束，然后给first补上一个头节点。
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



// 练习：通过三指针法反转链表
Node* reverseList(Node* head)   // head为头节点
{
    // 创建三个指针first、second和third
    Node* first = NULL;
    Node* second = head->next;
    Node* third;

    // 反转链表节点指针域的指向并移动三指针，直到second指针为空结束(此时first便为原链表的尾节点)
    while(second != NULL)
    {
        third = second->next; // 移动third指针
        second->next = first; // 反转链表节点指针域的指向(即second对应节点指向前一个节点first)
        first = second;       // 移动first指针
        second = third;       // 移动second指针
    }

    // 创建新的头节点hd并指向反转后的链表第一个节点first
    Node* hd = initList();  
    hd->next = first;

    // 注意：旧链表只剩头链表和第一个节点，并且第一个节点是新链表的尾节点(存在共用情形)
    return hd;
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

    // 练习：反转链表
    Node* list2 = reverseList(list); 
    listNode(list);  // 21(旧链表只剩头链表和第一个节点,并且第一个节点是新链表的尾节点(共用情形))
    listNode(list2); // -15 7 15 -15 21(新链表已经反转)

    // 释放单链表
    freeList(list2);
    printf("%d\n", listLength(list2));  // 1

    // 删除头节点
    free(list);
    free(list2);

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