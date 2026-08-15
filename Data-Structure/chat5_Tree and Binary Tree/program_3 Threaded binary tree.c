/*
线索二叉树(Threaded binary tree)的代码程序：
创建方式：
        在某种确定的遍历顺序(前序/中序/后序)下，会得到二叉树的线性排序，然后将普通二叉树中的某节点的
    空指针指向该节点的前驱(left空指针)节点和后继节点(right空指针)，从而使得遍历二叉树时可以不使用
    递归或栈，也能快速找到任意节点的前驱和后继。此外，线索二叉树还需要创建头节点，见注意2、3的内容。

    注意：
        1.虽然所有指针都利用上了，但对于某一节点，你无法分清左右指针指向的究竟是孩子节点还是
            前驱/后继节点，这就造成了混乱。

            解决方式：给结构体节点增加左右标签(ltag/rtag)，分别标注左右指针指向的到底是什么。
                比如：设置tag值为1表示指向线索，0表示指向孩子节点。

        2.头节点不存储树的数据，其左指针指向二叉树的根节点(对应的左标签为0)，右指针指向某种遍历顺序
            后的最后一个节点(对应的左标签为1)。

        3.在某种遍历顺序形成的序列中，第一个节点的左指针和最后一个节点的右指针指向头节点。
*/
#include<stdio.h>
#include <stdlib.h>

typedef char ElemType; 

// 1. 线索二叉树的链式结构————线索二叉树节点定义
typedef struct ThreadNode{
    ElemType data;
    // 左右指针
    struct ThreadNode* lchild; // 左指针，指向左孩子/前驱节点
    struct ThreadNode* rchild; // 右指针，指向右孩子/后继节点
    // 左右标签
    int ltag;  // 左标签，标签值为0表示左指针指向左孩子，1表示左指针指向前驱节点
    int rtag;  // 右标签，标签值为0表示右指针指向右孩子，1表示右指针指向后继节点
}ThreadNode;

typedef ThreadNode* ThreadTree; // 给ThreadNode*起别名为ThreadTree，此时ThreadTree是指针类型


// 2. 线索二叉树的创建
// 2.1 创建普通二叉树，前序思想创建：按根节点 → 左子树 → 右子树的顺序
char str[] = "ABDH##I##EJ###CF##G##"; 
int idx = 0;     // 记录字符串str的索引编号
ThreadTree prev; // 前驱指针，记录上一个访问的树节点(通过该指针的记录，节点右指针可以指向前驱节点)

void createTree(ThreadTree* T)  // 参数：T是指向线索二叉树根节点指针的指针
{
    ElemType ch;
    ch = str[idx]; 
    idx++;
    
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (ThreadTree)malloc(sizeof(ThreadNode)); // 给树节点ThreadNode分配堆内存地址
        (*T)->data = ch;                   // 给树节点ThreadNode赋值ch
        createTree(&(*T)->lchild);         // 递归调用自身，创建左子树
        (*T)->ltag = (*T)->lchild ? 0 : 1; // 三元表达式给ltag赋值,左子树不为NULL->0,为NULL->1
        createTree(&(*T)->rchild);         // 递归调用自身，创建右子树
        (*T)->rtag = (*T)->rchild ? 0 : 1; // 三元表达式给rtag赋值,右子树不为NULL->0,为NULL->1
    }
}

// 中序线索化函数：建立前驱/后继关系
void threading(ThreadTree T) // 参数T：指向二叉树根节点的指针
{
    if (T != NULL) // 注：T为空则函数直接结束，那么T的上一个节点就是叶子节点
    {
        threading(T->lchild);  // 递归线索化左子树

        // 如果当前节点T左指针是空，建立前驱线索
        if (T->ltag == 1)
            T->lchild = prev;

        // 如果当前节点T的前驱节点prev非空并且其rtag=1，建立prev的后继线索指向T
        if (prev && prev->rtag == 1)
            prev->rchild = T;

        prev = T;             // 更新prev为当前节点
        threading(T->rchild); // 递归线索化右子树
    }
}

// 2.2 二叉树线索化(中序遍历顺序)：创建头节点，调用线索化函数进行线索化过程
void inOderThreading(ThreadTree* T, ThreadTree* head)
// 参数：T是指向二叉树根节点指针的指针，head是指向头节点指针的指针
{
    // 创建头节点并初始化
    *head = (ThreadTree)malloc(sizeof(ThreadNode)); // 给头节点分配堆内存空间
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head;  // 初始化右指针指向自己

    // 空树情形
    if (*T == NULL)
    {
        (*head)->lchild = *head; 
    }
    // 非空树情形，进行线索化
    else
    {
        (*head)->lchild = *T;  // 头节点左指针指向根节点
        prev = *head;          // 初始化前驱指针，指向头节点(因为遍历的第一个节点前驱指向头节点)
        threading(*T);         // 中序线索化整个树(函数见上面)，此时前驱指针指向最后一个节点

        // 补全中序线索化的最后一个节点的后继线索
        prev->rchild = *head;
        prev->rtag = 1;
        (*head)->rchild = prev;  // 头节点的右指针指向中序遍历下的最后一个节点
    }
}


// 3. 二叉树的中序遍历(非递归实现)
void inOrder(ThreadTree head) // 参数head：线索二叉树的头节点
{
    ThreadTree curr = head->lchild;  // 从头节点的左孩子即根节点开始
    while (curr != head)
    {
        // 沿着左孩子一直走到底，直到某节点的ltag=0为止
        while (curr->ltag == 0)
            curr = curr->lchild;

        // 访问当前节点
        printf("%c ", curr->data);

        // 顺着线索一直向右访问所有后继，直到某节点的rtag=0或rchild为头节点为止
        while (curr->rtag == 1 && curr->rchild != head)
        {
            curr = curr->rchild;
            printf("%c ", curr->data);
        }

        // 进入当前节点的右子树
        curr = curr->rchild;
    }
}


int main()
{
    ThreadTree T, head;          // 定义树变量T与头节点变量head
    createTree(&T);              // 创建普通二叉树
    inOderThreading(&T, &head); // 执行线索化处理
    printf("中序遍历结果："); 
    inOrder(head);   // H D I B J E A F C G


    return 0;
}