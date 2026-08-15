/*
具体的代码程序1————深度优先遍历(DFS)
一、前序遍历(Preorder)：
    1.访问顺序：根节点 → 左子树 → 右子树
    2.具体过程：
            先访问根节点。然后访问左分支上遇到的每一个节点，持续这一过程，直到遇到空节点为止。这时，
        返回到最近的有右孩子的祖先节点，并从该节点的右孩子开始继续上述遍历过程。

二、中序遍历(Inorder Traversal)：
    1.访问顺序：左子树 → 根节点 → 右子树
    2.具体过程：
            从根节点开始，先向树的左下方移动，直到遇到空节点为止，然后访问空节点的父节点。接着继续
        遍历该节点的右子树，当右子树遍历完或没有右子树可以遍历，则继续遍历该节点的上一层节点，持续
        下去直到根节点的所有左子树访问完，然后访问根节点，最后按同样的方式访问根节点的右子树。

三、后序遍历(Postorder Traversal)：
    1.访问顺序：左子树 → 右子树 → 根节点
    2.具体过程：
            从根节点出发，先访问节点的左右儿子，再对该节点进行访问。这就意味着节点的儿子将在该节点
        之前输出。
*/ 
#include<stdio.h>
#include <stdlib.h>

typedef char ElemType; 

// 1.二叉树的链式结构————二叉树节点定义
typedef struct TreeNode{
    ElemType data;
    struct TreeNode* lchild; // 左孩子
    struct TreeNode* rchild; // 右孩子
}TreeNode;

// 给二叉树节点指针类型TreeNode*起别名为BiTree，其创建的变量(比如T)表示指向二叉树的根节点的指针。
typedef TreeNode* BiTree; 


// 2.用前序遍历思想创建一棵树：按根节点 → 左子树 → 右子树的顺序
// str对应树的关系：按照前序遍历排列，每个字母为节点存储内容，而#表示该节点的左/右孩子为空节点（具体树形状见课程P14的17:00）
char str[] = "ABDH#K###E##CFI###G#J##"; 
int idx = 0;    // 记录字符串str的索引编号

void createTree(BiTree* T) // 参数：T是指向BiTree的指针,而BiTree是指向二叉树根节点TreeNode的指针
// 参数的意义：如果参数为BiTree T，那么函数结束后创建的二叉树T就会释放，相当于什么都没创建；
// 而参数BiTree* T，就可以通过传入二叉树的内存地址，来创建二叉树，函数结束后创建的二叉树仍存在。
{
    ElemType ch;
    ch = str[idx]; // ch记录当前节点str[idx]
    idx++;

    // 判断节点ch是否为空，若为#则表示空
    if (ch == '#')
    {
        *T = NULL;
    }
    // 若ch不为#，则创建ch对应的树节点TreeNode(用指针*T指向)
    else
    {
        *T = (BiTree)malloc(sizeof(TreeNode)); // 给树节点TreeNode分配堆内存地址
        (*T)->data = ch;                       // 给树节点TreeNode赋值ch
        createTree(&(*T)->lchild);             // 递归调用自身，创建左子树
        createTree(&(*T)->rchild);             // 递归调用自身，创建右子树
    }           
}


// 3.二叉树的前序遍历
void preOrder(BiTree T) // 参数T：指向二叉树根节点TreeNode的指针
{
    if (T == NULL)
    {
        return;   // return的作用：立即终止函数，即写在return后面的函数体内容全部都无法执行
    }
    // "前序"的体现：处理当前节点 -> 递归遍历左子树 -> 递归遍历右子树
    printf("%c ", T->data); // 访问当前节点并打印节点的数据。
    preOrder(T->lchild);    // 递归调用自身，遍历左子树
    preOrder(T->rchild);    // 递归调用自身，遍历右子树
}


// 4.二叉树的中序遍历
void inOrder(BiTree T) // 参数T：指向二叉树根节点TreeNode的指针
{
    if (T == NULL)
    {
        return;   // return的作用：立即终止函数，即写在return后面的函数体内容全部都无法执行
    }
    // "中序"的体现：递归遍历左子树 -> 处理当前节点 -> 递归遍历右子树
    inOrder(T->lchild);     // 递归调用自身，遍历左子树
    printf("%c ", T->data); // 访问当前节点并打印节点的数据。
    inOrder(T->rchild);     // 递归调用自身，遍历右子树
}


// 5.二叉树的后序遍历
void postOrder(BiTree T) // 参数T：指向二叉树根节点TreeNode的指针
{
    if (T == NULL)
    {
        return;   // return的作用：立即终止函数，即写在return后面的函数体内容全部都无法执行
    }
    // "后序"的体现：递归遍历左子树 -> 递归遍历右子树 -> 处理当前节点 
    postOrder(T->lchild);    // 递归调用自身，遍历左子树
    postOrder(T->rchild);    // 递归调用自身，遍历右子树
    printf("%c ", T->data);  // 访问当前节点并打印节点的数据。
}



int main()
{
    // 创建二叉树，其中树的形貌见36行字符串char str[]的内容
    BiTree T;
    createTree(&T);

    // 前序遍历
    printf("前序遍历: ");
    preOrder(T);    // A B D H K E C F I G J
    printf("\n");

    // 中序遍历
    printf("中序遍历: ");
    inOrder(T);     // H K D B E A I F C G J
    printf("\n");

    // 后序遍历
    printf("后序遍历: ");
    postOrder(T);   // K H D E B I F J G C A 
    printf("\n");

    return 0;
}