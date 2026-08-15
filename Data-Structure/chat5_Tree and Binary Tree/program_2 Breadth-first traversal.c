/*
广度优先遍历(BFS)：广度优先，通过队列实现
具体种类：层序遍历(Level Order Traversal)：访问顺序：从上到下，从左到右逐层访问
    原理(具体见下面代码实现)：
        从根节点开始，逐层访问
        使用队列辅助实现
*/
#include<stdio.h>
#include <stdlib.h>

//=============== 队列的创建与各种操作(选用循环队列) ===================
#define MAXSIZE 100
typedef char TreeType;  // 给字符char起别名为TreeType

// 二叉树链式结构————二叉树节点定义
typedef struct TreeNode{
    TreeType data;
    struct TreeNode* lchild; // 左孩子
    struct TreeNode* rchild; // 右孩子
}TreeNode;

typedef TreeNode* ElemType; // 因为队列存储的都是树节点指针，所以队列数据类型设置为TreeNode*

// 队列的顺序结构定义
typedef struct 
{
    ElemType* data;
    int front;
    int rear;
}Queue;

// 队列的初始化
Queue* initQueue()
{
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    Q->front = 0; 
    Q->rear = 0;  
    return Q;
}

// 判断队列是否为空队列(空队列则返回值为1，否则为0)
int isEmpty(Queue* Q)
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 1;
    }
    else
    {
        return 0;
    }
} 

// 入队————在队尾添加元素
int equeue(Queue* Q, ElemType e) 
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) 
    {
        printf("队列已满\n");
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE; 
    return 1;
}

// 出队————删除队头的元素
int dequeue(Queue* Q, ElemType* e)
{
    if (Q->front == Q->rear)
    {
        printf("空队列\n");
        return 0;
    }
    *e = Q->data[Q->front]; 
    Q->front = (Q->front + 1) % MAXSIZE; 
    return 1;
}

// 获取队列元素数量
int queueSize(Queue* Q)
{
    if (!isEmpty(Q))
    {
        // 注意：循环队列的队尾指针rear可能在队头指针front的前面，解决办法为下面return的公式：
        // 当rear > front时：(rear - front + MAXSIZE) % MAXSIZE = rear - front
        // 当rear < front时：(rear - front + MAXSIZE) % MAXSIZE = rear - front + MAXSIZE
        return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
    }
    else
    {
        return 0;
    }
}



//================== 二叉树的创建与层序遍历获取二叉树深度 ==================
// 1.给二叉树节点指针类型TreeNode*起别名为BiTree
typedef TreeNode* BiTree; 

// 2.用前序遍历思想创建一棵树：按根节点 → 左子树 → 右子树的顺序
char str[] = "ABDH#K###E##CFI###G#J##"; 
int idx = 0;    

void createTree(BiTree* T)
{
    TreeType ch;
    ch = str[idx]; // ch记录当前节点str[idx]
    idx++;

    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree)malloc(sizeof(TreeNode)); // 给树节点TreeNode分配堆内存地址
        (*T)->data = ch;                       // 给树节点TreeNode赋值ch
        createTree(&(*T)->lchild);             // 递归调用自身，创建左子树
        createTree(&(*T)->rchild);             // 递归调用自身，创建右子树
    }
}


// 3.通过层序遍历得到二叉树的深度depth
int maxDepth(TreeNode* root) // 参数root：指向树的根节点的指针
{
    // 根节点为空则返回0
    if (root == NULL)
    {
        return 0;
    }

    int depth = 0;          // depth用来记录二叉树的深度
    Queue* q = initQueue(); // 创建并初始化队列
    equeue(q, root);        // 将根节点入队

    // 当队列q不为空(函数值为0)，则进行循环；当队列q为空(函数值为1)，则退出循环
    while (!isEmpty(q))
    {
        int count = queueSize(q);  // 获取当前队列q的数据长度(对应二叉树当前层的节点数)

        // 遍历二叉树每层的节点，每遍历一个节点，count-1，直到count=0循环停止
        while (count > 0)
        {
            TreeNode* curr;    // curr记录二叉树当前层的每个节点
            dequeue(q, &curr); // 出队，并将出队元素赋值给curr

            // 如果树节点curr的左孩子不为空，则入队
            if (curr->lchild != NULL)
            {
                equeue(q, curr->lchild);
            }
            // 如果树节点curr的右孩子不为空，则入队
            if (curr->rchild != NULL)
            {
                equeue(q, curr->rchild);
            }
            count--; // 已访问完节点curr，则记录的数目count-1
        }
        depth++;  // 当前层元素全部遍历完，树的深度加1(注意depth从0开始计数) 
    }
    return depth;
}




int main()
{
    // 创建二叉树，其中树的形貌见36行字符串char str[]的内容
    BiTree T;
    createTree(&T);

    // 层序遍历获取二叉树的深度
    int depth = maxDepth(T);    
    printf("二叉树T的深度: %d\n", depth); // 二叉树T的深度: 5


    return 0;
}