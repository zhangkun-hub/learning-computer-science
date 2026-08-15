/*
关键路径(Critical path)
一、基本概念：
    1.AOE网：在一个表示工程的带权有向图中，用顶点表示事件，用有向边表示活动，用边上的权值表示活动
        的持续时间，这种有向图的边表示活动的网，我们称为AOE网（Activity On Edge Network）。  
            注：AOE网中所有事件(顶点)按照拓扑排序方式进行排序，表示事件的先后发生顺序。

    2.最早开始时间(etv)：AOE网中，在不影响后续活动的前提下，事件可以开始的最早时间。
        计算思路：AOE网中将所有入度为0的事件(顶点)的etv设为0，然后按照有向边上的活动持续时间依次
            计算每个后续事件的开始时间，其中入度大于1的事件会有多条路径汇入，其开始时间不唯一，选
            值最大的开始时间(也就是最晚的开始时间)，通过这计算的事件开始时间就是其对应的etv了。

    3.最晚开始时间(ltv)：AOE网中，在不影响项目总工期的前提下，事件必须开始的最晚时间。
        计算思路：见第四部分算法步骤的内容。

    4.总浮动时间：事件可以延迟而不影响项目总工期的时间。
        计算思路：ltv - etv

    5.关键活动：总浮动时间为0的事件

    6.关键路径：由关键活动组成的路径


二、关键路径的特点
    决定项目工期：关键路径是AOE网中从开始到结束的最长路径，决定了项目的最短完成时间
    资源敏感性：关键活动上的资源分配直接影响项目进度
    动态性：当非关键活动延迟超过其浮动时间时，可能成为新的关键活动
    多条关键路径：一个项目可能有多条关键路径
    零浮动时间：关键活动的总浮动时间为零


三、核心价值
    确定最短工期：科学计算项目理论最短完成时间
    识别关键活动：明确哪些活动直接影响项目工期
    优化资源配置：将资源优先分配给关键活动
    支持决策制定：为赶工、快速跟进等决策提供依据


四、算法步骤：
    步骤1：构建活动网络图
        1. 确定所有活动及其持续时间
        2. 确定活动之间的依赖关系
        3. 构建有向无环图：
            - 顶点表示事件（活动开始或结束）
            - 边表示活动，权重为活动持续时间
        4. 添加虚拟起点和终点（如果需要）

    步骤2：计算最早开始时间（etv）
        1. 对图进行拓扑排序
        2. 初始化所有顶点的最早开始时间为0
        3. 按照拓扑顺序遍历每个顶点u：
            对于u的每个有向边的后继顶点v：etv[v] = max(etv[v], etv[u] + w(u, v))

    步骤3：计算最晚开始时间（ltv）
        1. 初始化所有顶点的最晚开始时间为一个极大值（如无穷大）
        2. 将所有汇点(即出度为0的点)的最晚开始时间初始化为：该汇点的最早开始时间
        3. 按照逆拓扑顺序遍历每个顶点v：
            对于v的每个有向边的前驱顶点u：ltv[u] = min(ltv[u], ltv[v] - w(u, v))

    步骤4：计算浮动时间
        对于每个顶点（事件）u：总浮动时间 = etv[u] - ltv[u]

    步骤5：识别关键路径
        1. 总浮动时间为0的活动是关键活动
        2. 所有关键活动组成的路径是关键路径
*/
#include <stdio.h>
#include <stdlib.h>


//========================== 各种定义 ===============================
#define MAXSIZE 100       // 最大顶点数
#define MAX 0x7fffffff    // 用int类型的最大值0x7fffffff表示“无穷”，即无边
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
    int weight;            // 边的权值
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


//========================== 邻接矩阵与邻接表的建立 ===============================
// 创建邻接矩阵
void create_graph(Mat_Graph* G)
{
    G->vertex_num = 10;  // 顶点数
    G->edge_num = 13;    // 边数 

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
            if (i == j)
            {
                G->arc[i][j] = 0;   // 矩阵对角线设为0
            }
            else
            {
                G->arc[i][j] = MAX; // 初始值均设置为无穷大MAX
            }
            
        }
    }

    // 添加有向且带权图的边
    G->arc[0][1] = 3;  
    G->arc[0][2] = 4;  
    G->arc[1][3] = 5; 
    G->arc[1][4] = 6; 
    G->arc[2][3] = 8; 
    G->arc[2][5] = 7; 
    G->arc[3][4] = 3; 
    G->arc[4][6] = 9; 
    G->arc[4][7] = 4; 
    G->arc[5][7] = 6; 
    G->arc[6][9] = 2; 
    G->arc[7][8] = 5; 
    G->arc[8][9] = 3; 
}

// 邻接矩阵转换成邻接表
void create_adj_graph(Mat_Graph G, Adj_List_Graph* ALG)
{
    EdgeNode* e;

    *ALG = (Adj_List_Graph)malloc(sizeof(Adj_Graph));
    (*ALG)->vertex_num = G.vertex_num;
    (*ALG)->edge_num = G.edge_num;
    
    for (int i = 0; i < G.vertex_num; i++)
    {
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].head = NULL;
    }

    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] != 0 && G.arc[i][j] < MAX)
            {
                e = (EdgeNode*)malloc(sizeof(EdgeNode));
                e->edge_vex = j;
                e->weight = G.arc[i][j];
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
}


//========================== 关键路径 ===============================
void critical_path(Adj_List_Graph ALG)
{
    EdgeNode* e;      // 记录每个顶点的邻接点结构体
    int etv[MAXSIZE]; // etv[i]表示事件(顶点)i的etv值
    int ltv[MAXSIZE]; // ltv[i]表示事件(顶点)i的ltv值
    int curr;         // 记录每次出栈的元素
    int k;            // 记录邻接点的索引

    // 创建栈1用来进行拓扑排序
    int top = -1;
    int stack[MAXSIZE];

    // 创建栈2用来进行逆拓扑排序(也就是将栈1依次出栈的元素依次放入栈2中)
    int top2 = -1;
    int stack2[MAXSIZE];

    // 将所有入度为0的顶点入栈1
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (ALG->adj_list[i].in == 0)
        {
            top++;
            stack[top] = i;
        }
    }

    // 初始化所有事件的etv为0
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        etv[i] = 0;
    }

    // 栈1不为空就一直循环
    while (top != -1)
    {
        // 出栈并打印出栈的事件curr，然后将其入栈2
        curr = stack[top];
        top--;
        top2++;
        stack2[top2] = curr;

        e = ALG->adj_list[curr].head; // 记录事件curr的邻接点

        // 遍历curr的所有邻接点
        while (e != NULL)
        {
            // 将curr的邻接点k的入度减一
            k = e->edge_vex;
            ALG->adj_list[k].in--;

            // 减一后k的入度如果为0，则入栈1
            if (ALG->adj_list[k].in == 0)
            {
                top++;
                stack[top] = k;
            }
            // 计算k的etv：etv[k] = max(etv[k], etv[curr] + w(curr, k))
            if (etv[curr] + e->weight > etv[k])
            {
                etv[k] = etv[curr] + e->weight;
            }
            // 获取下一个邻接点
            e = e->next;
        }
    }
    // 打印所有事件的etv值
    printf("etv: ");
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        printf("%d -> ", etv[i]);
    }
    printf("End\n");

    // 初始化所有事件的ltv：设置为最后一个顶点的etv
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        ltv[i] = etv[ALG->vertex_num - 1]; 
    }

    // 栈2不为空就一直循环(以下与栈1的操作基本一致)
    while (top2 != -1)
    {
        curr = stack2[top2];
        top2--;
        e = ALG->adj_list[curr].head; 

        while (e != NULL)
        {
            k = e->edge_vex; // 注意：事件curr是事件k的前驱顶点

            // 事件curr的ltv计算：ltv[curr] = min(ltv[curr], ltv[k] - w(curr, k))
            if (ltv[k] - e->weight < ltv[curr])
            {
                ltv[curr] = ltv[k] - e->weight;
            }
            e = e->next;
        }
    }

    // 打印所有事件的ltv值
    printf("ltv: ");
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        printf("%d -> ", ltv[i]);
    }
    printf("End\n");

    // 获取所有关键活动
    for (int i = 0; i < ALG->vertex_num; i++)
    {
        if (etv[i] == ltv[i])
        {
            printf("V%d -> ", i);
        }
    }
    printf("End\n");
}



int main()
{
    // 建立邻接矩阵和邻接表
    Mat_Graph G;
    Adj_List_Graph ALG;
    create_graph(&G);
    create_adj_graph(G, &ALG);

    // 关键路径
    critical_path(ALG);

    return 0;
}