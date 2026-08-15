/*
Prim算法：基于顶点，从一点逐步扩展。
Kruskal算法：基于边，按权重排序选择。
*/
#include <stdio.h>

#define MAXSIZE 100       // 最大顶点数
#define MAX 0x7fffffff    // 用int类型的最大值0x7fffffff表示“无穷”，即无边
typedef char VertexType;  // 顶点类型
typedef int EdgeType;     // 边的权值类型

// 图的邻接矩阵结构体定义
typedef struct
{
    VertexType vertex[MAXSIZE];     
    EdgeType arc[MAXSIZE][MAXSIZE]; 
    int vertex_num;                 
    int edge_num;                   
}Mat_Graph;

// 创建邻接矩阵
void create_graph(Mat_Graph* G)
{
    G->vertex_num = 9;  // 顶点数
    G->edge_num = 15;   // 边数 

    // 顶点命名
    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

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

    // 添加无向且有权图的边
    // A-B  A-F
    G->arc[0][1] = 10;  
    G->arc[0][5] = 11;  
    // B-C  B-G  B-I
    G->arc[1][2] = 18;  
    G->arc[1][6] = 16;  
    G->arc[1][8] = 12;  
    // C-D  C-I
    G->arc[2][3] = 22;  
    G->arc[2][8] = 8; 
    // D-E  D-G  D-H  D-I
    G->arc[3][4] = 20;  
    G->arc[3][6] = 24;  
    G->arc[3][7] = 16; 
    G->arc[3][8] = 21; 
    // E-F  E-H
    G->arc[4][5] = 26;  
    G->arc[4][7] = 7;
    // F-G
    G->arc[5][6] = 17;
    // G-H
    G->arc[6][7] = 19;
    // 无向图的对称矩阵分布
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = i; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//============================= prim算法 ===========================
void prim(Mat_Graph* G)
{
    int k;   // k记录权值最小的边的到达点索引
    int min;

    // 创建优先队列(由两个数组共同实现)
    int vex_index[MAXSIZE]; // vex_index[i]表示出发点的索引，下标i表示到达点的索引
    int weight[MAXSIZE];    // weight[i]表示顶点vex_index[i]与顶点i相连边的权值(包括MAX和0)

    // 优先队列初始化(从第0顶点开始)
    vex_index[0] = 0;
    weight[0] = 0;    

    // 将与第0顶点相连的所有边加入优先队列(包括无边的MAX情形)
    for (int i = 1; i < G->vertex_num; i++)
    {
        vex_index[i] = 0;
        weight[i] = G->arc[0][i]; 
    }

    // 循环n-1次，表示最小生成树的n个顶点有n-1条边(此处n = G->vertex_num)
    for (int i = 1; i < G->vertex_num; i++)
    {
        min = MAX;
        k = 0;  
        
        // 从优先队列中取出权值最小的边，并将该边的到达点赋值给k
        for (int j = 0; j < G->vertex_num; j++)
        {
            // 注意：weight[j]表示顶点vex_index[j](即顶点0)与顶点j相连边的权值
            if (weight[j] != 0 && weight[j] < min)
            {
                min = weight[j];
                k = j; 
            }
        }

        // 打印权值最小的边的出发点vex_index[k]和到达点k(注意这些都是对应顶点的下标值)
        printf("(%c, %c)\n", G->vertex[vex_index[k]], G->vertex[k]);

        // 因为最小生成树不能有回路，所以对其他到达点为k的边的权值都设为0
        weight[k] = 0; 

        // 在新出发点k作用下，对优先队列元素进行筛选替换
        for (int j = 0; j < G->vertex_num; j++)
        {
            // 新边 k-j 权值与旧边 vex_index[j]-j 进行比较，小就替换旧边，并将旧出发点也替换为k
            if (weight[j] != 0 && G->arc[k][j] < weight[j])
            {
                weight[j] = G->arc[k][j];
                vex_index[j] = k; 
            }
        }
    }
}



//============================= Kruskal算法 ===========================
#define MAXEDGE 200  // 最大边数

// 边的结构体
typedef struct
{
    int begin;   // 边的出发点索引
    int end;     // 边的到达点索引
    int weight;  // 边的权值
}Edge;

// 将边结构体变量i与j进行交换
void swap(Edge* edges, int i, int j) // Edge* edges是存储边结构体变量的数组
{
    int temp;

    // 将边i和边j的出发点索引进行互换
    temp = edges[i].begin;
    edges[i].begin = edges[j].begin;
    edges[j].begin = temp;

    // 将边i和边j的到达点索引进行互换
    temp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = temp;

    // 将边i和边j的权值进行互换
    temp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = temp;
}

// 对存储边的数组按照权值从小到大排序(这里是比较排序法)
void sortEdges(Edge edges[], int edge_num) // edge_num是数组edges[]中存储边的数量
{
    for (int i = 0; i < edge_num; i++)
    {
        for (int j = i + 1; j < edge_num; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                swap(edges, i, j);
            }
        }
    }
}

// 并查集的查找操作：找到节点index所在集合的根节点（代表元）。
int find(int* parent, int index) // 数组元素parent[i]表示节点i的父节点索引，-1表示根节点
{
    while (parent[index] > -1)  // 当前节点不是根节点
    {
        index = parent[index]; // 向上找父节点
    }
    return index;  // 返回根节点
}

// kruskal算法
void Kruskal(Mat_Graph G)
{
    Edge edges[MAXEDGE]; // 创建存储边结构体变量的数组
    int k = 0;

    // 将加权无向图的所有边存储到数组edges[]中
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] < MAX)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }

    // 对所有边按权值从小到大进行排序
    sortEdges(edges, G.edge_num);

    // 创建数组parent并初始化为-1
    int parent[MAXSIZE];  // 数组元素parent[i]表示节点i的父节点索引，值为-1则表示根节点
    for (int i = 0; i < G.vertex_num; i++)
    {
        parent[i] = -1;
    }

    // 并查集的合并操作：
    // 将边的出发点edges[i].begin和到达点edges[i].end所在的集合(也就是树)进行合并，构成一棵新树
    int n, m; 
    for (int i = 0; i < G.edge_num; i++)
    {
        n = find(parent, edges[i].begin);  // 找到边的出发点edges[i].begin的根n
        m = find(parent, edges[i].end);    // 找到边的到达点edges[i].end的根m
        if(n != m)  // 如果根n和根m不相等(即不在同一个树集合中)
        {
            parent[n] = m;  // 合并：将根n的父节点设为根m，从而构成一棵新树

            // 打印不在同一个树集合的最小权值边(也就是最小生成树的边)
            printf("(%c, %c) %d\n", G.vertex[edges[i].begin], G.vertex[edges[i].end], edges[i].weight);
        }
    }
}



int main()
{
    // 创建邻接矩阵G
    Mat_Graph G;
    create_graph(&G);

    // prim算法
    printf("----------prim算法----------\n");
    prim(&G);

    // Kruskal算法
    printf("----------Kruskal算法----------\n");
    Kruskal(G);


    return 0;
}