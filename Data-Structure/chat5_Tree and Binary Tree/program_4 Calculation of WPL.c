/*
计算树的带权路径长度WPL，代码的关键点：
    1.判断是否是叶子节点————即该节点左孩子和右孩子全为NULL。
    2.确定叶子节点所在层数————即通过program_2的层序遍历方法获取层数。
*/

#include<stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType; 

// 二叉树的链式结构————二叉树节点定义
typedef struct TreeNode{
    ElemType weight; // 存储该节点的权值
    struct TreeNode* lchild;  // 左孩子
    struct TreeNode* rchild;  // 右孩子
}TreeNode;

typedef TreeNode* BiTree; 


// 创建带权值的二叉树（与program_1的前序遍历创建二叉树完全一致，节点赋值除外）
// weight数组对应树的关系：按照前序遍历排列，其中-1表示该节点的左/右孩子为空节点，其他数字为该节点的权值（具体树形状见课程P17的44:04）
int weight[] = {100, 42, 15, -1, -1, 27, -1, -1, 58, 28, 13, 5, -1, -1, 8, -1, -1, 15, -1, -1, 30, -1, -1};
int idx = 0;

void createTree(BiTree* T) // 参数：T是指向BiTree的指针,而BiTree是指向二叉树根节点TreeNode的指针
{
    ElemType ch;
    ch = weight[idx]; 
    idx++;

    if (ch == -1)
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree)malloc(sizeof(TreeNode)); 
        (*T)->weight = ch;                       
        createTree(&(*T)->lchild);             
        createTree(&(*T)->rchild);             
    }           
}


// WPL计算
int wpl(BiTree T) // 参数T：指向二叉树根节点的指针
{
    // 对于空树，wpl值为0
    if (T == NULL)
    {
        return 0;
    }

    // 创建一个简易队列(其中数组元素存储的是树节点指针BiTree类型)
    BiTree queue[MAXSIZE]; 
    int front = 0; // 队头指针
    int rear = 0;  //  队尾指针

    // 初始化wpl与树节点深度depth
    int wpl = 0;
    int depth = 0; // 注意：树节点的深度表示其路径长度，与对应层数关系：depth = 层数 - 1

    // 将根节点T传入队列
    queue[rear] = T;
    rear++;

    // 层序遍历求解wpl，直到队列元素为空，循环停止
    while(rear != front)
    {
        int count = rear - front; // count记录二叉树每层的节点数

        // 遍历二叉树每层的节点，每遍历一个节点，count-1，直到count=0循环停止
        while(count > 0)
        {
            // 定义curr变量并记录二叉树当前层的每个节点
            BiTree curr = queue[front]; 
            front++;

            // 当该层节点curr是叶子节点，则计算其wpl
            if (curr->lchild == NULL && curr->rchild == NULL)
            {
                wpl += depth * curr->weight; 
            }

            // 当该层节点curr的左孩子非空，则添加到队列中
            if (curr->lchild != NULL)
            {
                queue[rear] = curr->lchild;
                rear++;
            }

            // 当该层节点curr的右孩子非空，则添加到队列中
            if (curr->rchild != NULL)
            {
                queue[rear] = curr->rchild;
                rear++;
            }

            // 访问完该层节点curr后，该层节点数减一
            count--;
        }

        // 该层节点全部访问完，开始访问下一层节点时，其深度加一
        depth += 1;
    }
    return wpl;
}

int main()
{
    // 创建一棵二叉树
    BiTree T;
    createTree(&T);

    // 计算WPL
    int w = wpl(T);
    printf("%d\n", w); // 241



    return 0;
}



