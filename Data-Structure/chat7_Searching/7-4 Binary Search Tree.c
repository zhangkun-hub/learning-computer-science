/*
二叉排序树(Binary Search Tree，BST)
一、定义：二叉排序树要求满足以下特性：
        1.对于树中任意一个节点，其左子树上所有节点的值都小于该节点的值。
        2.对于树中任意一个节点，其右子树上所有节点的值都大于该节点的值
        3.左右子树本身也都是一棵二叉排序树。
        4.没有键值相等的节点（通常约定）
        (注意：构造二叉排序树的目的，并不是为了排序，而是为了提高查找、插入以及删除关键字的速度)
    
二、重要性质：
    1.一棵二叉树是二叉排序树的充要条件：中序遍历的序列是按照升序进行排列分布的。
    2.结构可变性：同一组数据可以构造出不同形态的BST
    3.查找路径唯一：从根到任一节点的路径是唯一的
    4.二叉排序树的查找操作时间复杂度：平均：O(log n)；最坏：O(n)

三、特点：
    1.优点：结构简单，插入删除灵活，保持了有序性。
    2.缺点：若插入序列有序，会退化成线性链表，查找效率降至O(n)。


四、二叉排序树的查找操作：
    算法步骤：
        (1)从根节点开始比较。
        (2)若等于目标值，查找成功。
        (3)若小于目标值，递归进入左子树查找。
        (4)若大于目标值，递归进入右子树查找。
        (5)遇到空节点则查找失败。


五、二叉排序树的插入操作：
    1.要求：插入新节点时，必须保持BST的性质

    2.作用：
        (1)在已有的二叉排序树上插入新的节点从而构成新的二叉排序树。
        (2)更重要作用：通过给定的数据序列(有序无序均可)生成一棵二叉排序树。
            注意：如果序列有重复值，则生成的二叉排序树与将所有重复值去掉生成的二叉排序树相同

    3.算法步骤：
        (1)若树为空，则创建新节点作为根节点
        (2)若树非空：
            若key < 当前节点值，递归插入左子树
            若key > 当前节点值，递归插入右子树
            若key = 当前节点值，插入失败（关键字已存在）
        (3)创建新节点并挂载到相应位置


五、二次排序的树的删除操作：
    1.删除操作需考虑三种情况，保持BST性质不变：
        情况        描述	                  处理方法	                        
        情况1​       删除叶子节点​	             直接删除，将其父节点对应指针置为NULL 
        情况2​       删除只有一个孩子的节点	     用其孩子节点替代该节点	            
        情况3​       删除有两个孩子的节点	     用前驱或后继替代，再删除前驱/后继	 

    2.关键概念
        前驱：中序遍历序列中，节点的前一个节点
            即左子树中的最大节点（左子树最右下节点）

        后继：中序遍历序列中，节点的后一个节点
            即右子树中的最小节点（右子树最左下节点）

    3.算法步骤
        (1)查找待删除节点及其父节点
        (2)根据节点孩子数处理：
            情况1（叶子节点）：直接删除，父节点对应指针置NULL

            情况2（一个孩子）：
                若只有左孩子：用左孩子替代
                若只有右孩子：用右孩子替代

            情况3（两个孩子）：
                a. 找到该节点的前驱（左子树最大节点）或后继（右子树最小节点）
                b. 用前驱/后继的值替换待删除节点的值
                c. 删除前驱/后继节点（转化为情况1或2）
*/
#include <stdio.h>
#include <stdlib.h>

// ============================== 二叉树的结构和基本操作 ================================
typedef int ElemType; // 定义二叉树节点数据类型

// 定义二叉树节点结构体
typedef struct TreeNode
{
    ElemType data;               // 节点存储的数据（关键字）
    struct TreeNode* lchild;     // 左子节点
    struct TreeNode* rchild;     // 右子节点
} TreeNode;

typedef TreeNode* BiTree;       // 定义二叉树指针类型

// 前序遍历打印二叉树节点值
void preOrder(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    printf("%d ", T->data);   // 访问当前节点
    preOrder(T->lchild);      // 遍历左子树
    preOrder(T->rchild);      // 遍历右子树
}


// =============================== 二叉排序树的查找操作 =================================
/* 
参数：
    T: 当前子树根节点；
    value: 要查找的值；
    parent: 参数节点T的父节点(如果T是整个二叉树的根节点，则其父节点为NULL)；
    pos: 用于返回找到的节点(如果未找到情形，见返回值0的内容；如果pos=NULL，则二叉排序树是空树)
返回值: 
    1 表示找到，并且会将找到的节点赋值给pos
    0 表示未找到，并且会将这个不存在的节点value如果要插入二叉排序树时其所在位置的父节点赋值给pos
*/         
int search_bst(BiTree T, int value, BiTree parent, BiTree* pos)
{
    // 递归到空节点，则表示查找失败，树T不存在value
    if (T == NULL)
    {
        *pos = parent; // 查找失败将父节点返回(单纯查找操作下没用，但配合插入操作很有用)
        return 0;
    }
    
    // 若等于目标值，查找成功
    if (T->data == value)
    {
        *pos = T;   // 返回目标值所在的节点
        return 1;
    }
    // 若小于目标值，递归进入左子树查找
    else if (T->data > value)
    {
        return search_bst(T->lchild, value, T, pos); 
    }
    // 若大于目标值，递归进入右子树查找
    else
    {
        return search_bst(T->rchild, value, T, pos); 
    }
}


// ======================== 二叉排序树的插入操作(可用来创建BST) ==========================
// 向二叉排序树中插入值value，如果值存在，插入失败，返回0；否则插入成功，返回1
int insert_bst(BiTree* T, int value)
{
    BiTree parent, pos; // parent用于辅助search_bst，pos用于表示插入位置或已存在的位置
    BiTree curr; 

    // 查找插入位置(注意：查找失败时，pos指向的是要插入位置的父节点)
    int status = search_bst(*T, value, NULL, &pos);

    // 树T不存在value情形(即status = 0)
    if(status == 0)
    {
        // 创建新节点curr并赋值value
        curr = (BiTree)malloc(sizeof(TreeNode));
        curr->data = value;
        curr->lchild = NULL;
        curr->rchild = NULL;
        
        // 如果树为空，新节点作为根节点
        if (pos == NULL)
        {
            *T = curr;
        }
        // 插入值value < 当前节点值，插入为左子节点
        else if (value < pos->data)
        {
            pos->lchild = curr;
        }
        // 插入值value > 当前节点值，插入为右子节点
        else
        {
            pos->rchild = curr;
        }
        return 1;
    }
    // 如果树T已存在value，则不插入
    else
    {
        return 0;
    }
}


// =============================== 二叉排序树的删除操作 =================================
/* 
删除操作辅助函数：执行删除的操作（分三种情况）
参数d的取值情况：
    1.当删除的节点是根节点，则d是指向“指向根节点的指针T”的内存地址
    2.当删除的节点不是根节点，d指向要删除节点的父节点的child指针的内存地址，而child指针的值(即*d)
        指向要删除的目标节点的地址
*/
int delete(BiTree* d) 
{
    BiTree temp, record;

    // 情况1：只有左子树或无子节点
    if((*d)->rchild == NULL)
    {
        temp = *d;         // 将要删除的节点地址赋值给temp
        *d = (*d)->lchild; // 将要删除的节点的左孩子节点地址赋值给*d
        free(temp);        // 释放要删除的节点内存空间
    }
    // 情况2：只有右子树
    else if ((*d)->lchild == NULL)
    {
        temp = *d;
        *d = (*d)->rchild; // 将要删除的节点的右孩子节点地址赋值给*d
        free(temp);
    }
    // 情况3：左右子树都有，找左子树中最大的节点替换
    else
    {
        temp = *d;             // temp用来记录左子树中最大的节点(即record)的父节点
        record = (*d)->lchild; // record用来记录左子树中最大的节点
        // 找到左子树中最右下角的节点(最大值)，并用record记录该节点
        while(record->rchild != NULL)
        {
            temp = record;
            record = record->rchild;
        }
        
        // 替换当前值
        (*d)->data = record->data;
        
        // 删除替代节点(即左子树最大值节点)
        if (temp != *d) // 注意：temp = *d表示最大值节点record是要删除节点*d的左孩子
        {
            // 如果最大值节点不是左孩子，将其左子树的根节点接到其父节点temp右孩子处
            temp->rchild = record->lchild;
        }
        else
        {
            // 如果最大值节点是左孩子，将其左子树的根节点接到其父节点temp的左孩子处
            temp->lchild = record->lchild;
        }
        free(record);
    }
    return 1;
}

// 删除操作的调用函数：递归查找并删除目标节点
int delete_bst(BiTree* T, int value)
{
    // 递归到空节点，则表示查找失败，树T不存在要删除的目标节点
    if (*T == NULL)
    {
        printf("not found!\n");
        return 0;
    }
    else
    {
        // 找到value所在位置，调用底层 delete 函数执行删除
        if ((*T)->data == value)
        {
            return delete(T);
        }
        // 要删除的值比当前节点小，往左子树找
        else if ((*T)->data > value)
        {
            return delete_bst(&(*T)->lchild, value);
        }
        // 要删除的值比当前节点大，往右子树找
        else
        {
            return delete_bst(&(*T)->rchild, value);
        }
    }
}



int main(int argc, char const *argv[])
{
    // 准备插入的初始序列
    int treeArr[] = {70, 55, 49, 30, 39, 53, 80, 75, 98, 95};

    // 通过序列treeArr[]与插入操作创建二叉排序树
    BiTree T = NULL;
    for (int i = 0; i < 10; i++)
    {
        insert_bst(&T, treeArr[i]);
    }

    // 通过前序遍历输出二叉排序树内容
    preOrder(T);  // 70 55 49 30 39 53 80 75 98 95
    printf("\n"); 

    // 查找值为 53 的节点
    BiTree searchT; // 记录53所对应的节点
    search_bst(T, 53, NULL, &searchT);  

    // 输出查找到的节点值
    printf("%d\n", searchT->data);  // 53

    // 插入操作
    insert_bst(&T, 99);  // 插入一个新值99
    preOrder(T);  // 70 55 49 30 39 53 80 75 98 95 99
    printf("\n"); 

    // 删除操作
    delete_bst(&T, 49);  // 删除49节点
    preOrder(T);  // 70 55 39 30 53 80 75 98 95 99
    printf("\n"); 


    return 0;
}