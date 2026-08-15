/*
拓扑排序(Topological sorting)
一、基本概念：
    1.AOV网：在一个表示工程的有向图中，用顶点表示活动，用弧(即有方向的边)表示活动之间的优先级，
        这样的有向图为顶点表示活动的网，我们称为 AOV 网（Activity On Vertex Network）。

    2.拓扑排序：将AOV网上的所有顶点进行线性排序，使得对于图中的每一条有向边u -> v，顶点u在排序中
        都出现在顶点v之前。

    3.数学形式：给定有向无环图 G=(V,E)，拓扑排序是一个顶点序列 v₁, v₂, ..., vₙ，使得对于任意边 
        (vᵢ, vⱼ) ∈ E，都有 i < j。

二、核心特点
    1. 适用图类型
        必须是有向图：无向图没有拓扑排序的概念
        必须是无环图：有环图无法进行拓扑排序
        DAG（有向无环图）：拓扑排序只适用于DAG

    2. 排序结果特性
        不唯一性：一个DAG可能有多个合法的拓扑排序
        偏序关系：拓扑排序将偏序关系转化为全序关系
        局部性：相邻顶点在排序中不一定相邻

    3. 算法特性
        时间复杂度：通常为 O(V+E)，其中V是顶点数，E是边数
        空间复杂度：O(V) 用于存储入度或递归栈
        稳定性：对于相同的输入，算法可能产生不同的排序（取决于实现）


三、核心价值
    依赖解析：将复杂的依赖关系转化为线性执行顺序
    环检测：通过拓扑排序失败可以检测图中是否存在环
    顺序保证：确保所有依赖关系得到满足

四、应用领域
    编译系统：确定源代码文件的编译顺序
    任务调度：安排具有依赖关系的任务执行顺序
    课程安排：根据先修课程要求安排学习计划
    数据管道：确定数据处理步骤的执行顺序
    项目管理：确定项目活动的先后顺序


五、算法步骤：(需要用到图的邻接表内容)
    核心思想：不断移除入度为0的顶点，并更新相关顶点的入度。
        1. 计算每个顶点的入度
        2. 将所有入度为0的顶点加入队列/栈
        3. 当队列/栈非空时：
            a. 从队列/栈中取出顶点u
            b. 将u加入拓扑排序结果
            c. 对于u的每个邻居v：
                将v的入度减1
                如果v的入度变为0，将v加入队列/栈
        4. 如果排序结果包含所有顶点，则成功；否则，图中存在环
*/
#include <stdio.h>
#include <stdlib.h>


//========================== 各种定义 ===============================
#define MAXSIZE 100       // 最大顶点数
typedef int VertexType;   // 顶点类型
typedef int EdgeType;     // 边的权值类型

// 图的邻接矩阵结构体定义
typedef struct{
    VertexType vertex[MAXSIZE];     
    EdgeType arc[MAXSIZE][MAXSIZE]; 
    int vertex_num;                 
    int edge_num;                   
}Mat_Graph;

// 定义顶点的邻接点结构体
typedef struct EdgeNode{
    int edge_vex;          // 记录某顶点的邻接点(即由边相连的顶点)在顶点数组中的下标
    struct EdgeNode* next; // 指向下一个邻接点(因为一个顶点的邻接点可能不止一个)
}EdgeNode;

// 定义顶点结构体
typedef struct VertextNode{
    int in;            // 顶点的入度
    VertexType data;   // 存储顶点信息    
    EdgeNode* head;    // 从该顶点开始指向第一个邻接点的指针
}VertextNode; 

// 给VertextNode类型的数组起别名为：Adj_List[MAXSIZE]
typedef VertextNode Adj_List[MAXSIZE];

// 图的邻接表结构体
typedef struct{
    Adj_List adj_list; // 邻接表，存储顶点节点的数组。
    int vertex_num;    // 顶点数
    int edge_num;      // 边数
}Adj_Graph;

typedef Adj_Graph* Adj_List_Graph;

// 栈的定义
int top = -1;
int stack[MAXSIZE];

// 入栈
void push(int e)
{
    if (top > MAXSIZE)
    {
        printf("满了\n");
        return;
    }
    top++;
    stack[top] = e;
}

// 出栈
int pop()
{
    if (top == -1)
    {
        printf("空的\n");
        return 0;
    }
    int elem = stack[top];
    top--;
    return elem;
}

// 判断栈是否为空
int is_empty()
{
    if (top == -1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//========================== 邻接矩阵与邻接表的建立 ===============================
// 创建邻接矩阵
void create_graph(Mat_Graph* G)
{
    G->vertex_num = 14;  // 顶点数
    G->edge_num = 20;    // 边数 

    // 顶点命名
    for (int i = 0; i < G->vertex_num; i++)
    {
        G->vertex[i] = i;
    }

    // 初始化邻接矩阵
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    // 添加有向图的边
    G->arc[0][4] = 1;  
    G->arc[0][5] = 1;  
    G->arc[0][11] = 1; 
    G->arc[1][2] = 1; 
    G->arc[1][4] = 1; 
    G->arc[1][8] = 1; 
    G->arc[2][5] = 1; 
    G->arc[2][6] = 1; 
    G->arc[2][9] = 1; 
    G->arc[3][2] = 1; 
    G->arc[3][13] = 1; 
    G->arc[4][7] = 1; 
    G->arc[5][8] = 1; 
    G->arc[5][12] = 1; 
    G->arc[6][5] = 1; 
    G->arc[8][7] = 1; 
    G->arc[9][10] = 1; 
    G->arc[9][11] = 1; 
    G->arc[10][13] = 1; 
    G->arc[12][9] = 1; 
}

// 邻接矩阵转换成邻接表
void create_adj_graph(Mat_Graph G, Adj_List_Graph* ALG) // ALG是指向邻接表结构体Adj_Graph的二级指针
{
    EdgeNode* e; // 定义邻接点结构体来记录每个顶点的邻接点

    // 给邻接表结构体Adj_Graph分配内存空间
    *ALG = (Adj_List_Graph)malloc(sizeof(Adj_Graph));
    (*ALG)->vertex_num = G.vertex_num;
    (*ALG)->edge_num = G.edge_num;
    
    // 邻接表结构体的邻接表adj_list进行初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        (*ALG)->adj_list[i].in = 0;  // 初始入度均为0
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].head = NULL;
    }

    // 通过头插法给每个顶点分配相应的邻接点EdgeNode，并计算该邻接点的入度
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] == 1)
            {
                e = (EdgeNode*)malloc(sizeof(EdgeNode));
                e->edge_vex = j;
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
}


//========================== 拓扑排序 ===============================
void topological_sort(Adj_List_Graph ALG) // ALG是指向邻接表结构体Adj_Graph的一级指针
{
    EdgeNode* e; // 记录每个顶点的邻接点结构体
    int curr;    // 记录每次出栈的元素
    int k;       // 记录邻接点的索引

    // 将所有入度为0的顶点入栈
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (ALG->adj_list[i].in == 0)
        {
            push(i);
        }
    }
    // 栈不为空就一直循环
    while (is_empty() != 0)
    {
        // 出栈并打印出栈的顶点curr，然后记录该顶点的邻接点
        curr = pop();                                
        printf("V%d -> ", ALG->adj_list[curr].data); 
        e = ALG->adj_list[curr].head;                

        // 遍历curr的所有邻接点
        while(e != NULL)
        {
            // 将curr的邻接点k的入度减一
            k = e->edge_vex;
            ALG->adj_list[k].in--; 

            // 减一后k的入度如果为0，则入栈
            if (ALG->adj_list[k].in == 0)
            {
                push(k);
            }
            // 获取下一个邻接点
            e = e->next;
        }
    }
    printf("^\n");
}


int main()
{
    // 建立邻接矩阵和邻接表
    Mat_Graph G;
    Adj_List_Graph ALG;
    create_graph(&G);
    create_adj_graph(G, &ALG);

    // 拓扑排序
    topological_sort(ALG);
    // V3 -> V1 -> V2 -> V6 -> V0 -> V4 -> V5 -> V8 -> V7 -> V12 -> V9 -> V10 -> V13 -> V11 -> ^

    return 0;
}