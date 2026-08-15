/*
单向循环链表(注意：循环链表可以有支线，不一定是尾节点指向头节点形成单纯的一个环)：
一、创建思路：
    步骤1: 仍然按照单链表的类型格式与初始化过程创建头节点。
    
    步骤2: 按照单链表尾插法插入节点数据，其中要被尾节点指针域指向的节点要创建新节点来单独记录。

    步骤3: 将单链表的尾节点的指针域指向步骤2中创建的新节点，从而形成一个单向循环链表。


二、单向循环链表注意事项：
    当链表遍历时,在单链表中判别条件为p!=NULL 或 p->next!=NULL，而循环单链表的判别条件为：
                    p != L 或 p->next != L   # 其中L为尾节点所连接的节点
*/
// =========================================================================
// ========= 单向循环链表的创建与判断链表是否有环和寻找环的入口的操作 ===========
// =========================================================================
#include<stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;      
    struct node* next;  
}Node;

// 单向循环链表初始化————头节点的创建(与单链表完全相同)
Node* initList();

// 单向循环链表的尾插法(与单链表完全相同)
Node* get_tail(Node* L);                  // 步骤1：先获取尾节点地址
Node* insertTail(Node* tail, ElemType e); // 步骤2：开始尾插



// 练习1：判断链表是否有环的操作
// 思路：通过快慢指针方法，让快指针每次比慢指针多走一步，最后如果他们相遇则存在环，否则不存在。
int isCycle(Node* head) // head是单向循环链表的头节点
{
    Node* fast = head;
    Node* slow = head;
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next; // 快指针比慢指针多走一步操作
        slow = slow->next;
        if(fast == slow) 
        {
            printf("有环\n");
            return 1;
        }
    }
    printf("没有环\n");
    return 0;
}


// 练习2: 寻找环的入口
// 思路: 先求出环的节点数n,然后从头开始,让快指针先走n步,再让两指针一起走直到相遇,相遇处便是环的入口
Node* findBegin(Node* head)
{
    // 先重复练习1，按照判断链表是否有环的操作让快慢指针在环内相遇
    Node* fast = head;
    Node* slow = head;
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next; // 快指针比慢指针多走一步操作
        slow = slow->next;

        // if成立则快慢指针在环内相遇
        if(fast == slow) 
        {
            // 求出环的节点数count
            int count = 1;
            while(fast->next != slow)
            {
                count++;
                fast = fast->next;
            }

            // 将快慢指针重新放到头节点处
            fast = head;
            slow = head;

            // 将快指针先移动count步(即环的节点数)
            for(int i = 0; i < count; i++)
            {
                fast = fast->next;
            }

            // 将快慢指针一起移动，直到相遇，相遇点便是环的入口
            while(fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;
}



int main()
{
    // 单向循环链表的创建
    // 步骤1: 按单链表完全相同的方式创建头节点
    Node* list = initList();

    // 步骤2: 按单链表完全相同的方式使用尾插法插入数据
    Node* tail = get_tail(list);
    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    Node* three = tail; // 创建节点three来记录第三个节点
    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, 8);

    // 步骤3: 将尾节点的指针域指向第三个节点，形成一个环，从而构成单向循环链表
    tail->next = three;


    // 练习1：判断链表是否有环的操作
    isCycle(list); // 有环

    // 练习2：寻找环的入口
    Node* p = findBegin(list);
    printf("%d\n", p->data); // 3


    return 0;

}



// 单向循环链表初始化————头节点的创建(与单链表完全相同)
Node* initList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL; 
    return head;
}

// 单向循环链表的尾插法(与单链表完全相同)
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

