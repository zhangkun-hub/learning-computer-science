// ==========================================
// ========= 单链表的创建与各种操作 ===========
// ==========================================
#include<stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 1.单链表的节点格式定义
typedef struct node{
    ElemType data;      // 创建存储节点的数据元素
    struct node* next;  // 创建存储下一个节点的内存地址(注意:下一个节点的类型仍然是struct node)
}Node;

// 2.单链表初始化————头节点的创建
Node* initList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL; // 因为之后没有节点，所以指向空内存地址
    return head;
}


// 3.单链表的数据添加
// 3.1 头插法：每一次插入新数据时，都把新数据对应的新节点直接连在头节点的后面，而其他数据依次往后挪
// 特点：数据插入的顺序跟对应链表的顺序是相反的
void insertHead(Node* L, ElemType e) // L是头节点指针，e是要添加的数据
{
    Node* p = (Node*)malloc(sizeof(Node)); // 创建新节点Node的指针Node* p
    p->data = e;        // 给新节点p的数据域存储数据e
    p->next = L->next;  // 给新节点p的指针域p->next赋值头节点L的指针域L->next
    L->next = p;        // 给头节点L的指针域L->next赋值新节点p的内存地址
}


// 3.2 尾插法：在链表的最后一个节点添加一个新节点(可解决数据插入顺序跟对应链表的顺序是相反的问题)
// 步骤1：先获取尾节点地址
Node* get_tail(Node* L)   // L是头节点指针
{
    Node* p = L;
    while(p->next != NULL) // 当节点p的指针域p->next为空(即p是尾节点)，循环停止
    {
        p = p->next;
    }
    return p;
}
// 步骤2：开始尾插
Node* insertTail(Node* tail, ElemType e)   // tail是步骤1获取的尾节点指针
{
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    // 返回插入的新的尾节点p，这样之后再插入就无需经过步骤1的操作了
    return p;
}


// 4.单链表的遍历
void listNode(Node* L) // L是头节点指针
{
    Node* p = L->next;
    while(p != NULL) // 循环结束条件：p是最后一个节点的指针域(其指向的是NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


// 5.单链表的插入
int insertNode(Node* L, int pos, ElemType e) // L是头节点，pos是要插入的位置，e是插入的数据
{
    // 创建节点p用来保存插入位置的前驱节点
    Node* p = L;
    
    // 遍历链表找到插入位置的前驱节点并赋值给p
    int i = 0; // i表示节点p对应链表节点的索引，其中0对应头节点
    while(i < pos - 1) // 前驱节点的位置为pos-1(注意：链表存储数据是从1开始)
    {
        p = p->next;
        i++;
        // 当链表尾节点在前驱节点pos-1之前(不包括pos-1)，则插入位置pos有错，返回0
        if(p == NULL) 
        {
            return 0;
        }
    }

    // 要插入的新节点q
    Node* q = (Node*)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}


// 6.单链表的节点删除
int deleteNode(Node* L, int pos) // L是头节点，pos是要删除的位置
{
    // 创建节点p用来保存要删除节点的前驱节点
    Node* p = L;
    // 遍历链表，找到要删除节点的前驱(与插入操作完全一样)
    int i = 0;        
    while(i < pos-1)  
    {
        p = p->next;
        i++;
        if(p == NULL)
        {
            return 0;
        }
    }
    // 判断要删除的节点是否存在，不存在则说明位置pos有问题
    if(p->next == NULL)
    {
        printf("要删除的位置错误\n");
        return 0;
    }
    // 删除pos位置的节点
    Node* q = p->next; // q指向要删除的节点
    p->next = q->next; // 让删除节点q的前驱节点p指向q的后继
    free(q);           // 释放要删除节点的内存空间
    return 1;
}


// 7.获取单链表的长度(包括头节点)
int listLength(Node* L) // L是头节点
{
    Node* p = L;
    int len = 0; // len可以理解为节点p对应链表节点的索引(0对应头节点),而尾节点索引值+1就是链表的长度(+1是因为包括头节点)
    while(p != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}


// 8.单链表的释放(即清空链表，头节点不释放)
void freeList(Node* L) // L是头节点
{
    Node* p = L->next; // 指针p作用: 记录当前节点(从头节点开始)的后继节点，并不断释放该后继节点
    Node* q;           // 指针q作用: 记录指针p的后继节点

    while(p != NULL) // 当前节点的后继节点p如果是NULL，那么当前节点便是尾节点(在上个循环已释放)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}




int main()
{
    // 1 and 2 声明链表并初始化
    Node* list = initList();
    Node* list2 = initList();

    // 3.1 使用头插法插入数据
    insertHead(list2, 10);
    insertHead(list2, 20);
    insertHead(list2, 30);

    // 4.链表的遍历
    listNode(list2); // 30 20 10(可以看到头插法插入的顺序跟链表的顺序相反)

    // 3.2 使用尾插法插入数据与遍历
    Node* tail = get_tail(list);
    tail = insertTail(tail, 10);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);
    tail = insertTail(tail, 40);
    tail = insertTail(tail, 50);
    listNode(list);  // 10 20 30 40 50(可以看到尾插法插入的顺序跟链表顺序一致)

    // 5.单链表的插入
    insertNode(list, 3, 100);
    listNode(list);  // 10 20 100 30 40 50

    // 6.单链表的删除
    deleteNode(list, 3);
    listNode(list);  // 10 20 30 40 50

    // 7.获取单链表的长度(包括头节点)
    printf("%d\n", listLength(list)); // 6

    // 8.释放单链表
    freeList(list);
    freeList(list2);
    printf("%d\n", listLength(list));  // 1(因为头节点不释放，而链表长度包括头节点，所以为1)
    printf("%d\n", listLength(list2)); // 1

    // 9.删除头节点
    free(list);
    free(list2);



    return 0;

}

