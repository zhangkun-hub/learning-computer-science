/*
Dijkstra算法代码实现
Floyd算法代码实现
*/
#include <stdio.h>

#define MAXSIZE 100       // 最大顶点数
#define MAXEDGE 200       // 最大边数
#define MAX 0x10000       // 注：这里不用最大值0x7fffffff表示"无边"，是因为有加法运算，而最大值+1的结果是变成最小的负数了
typedef int VertexType;   // 顶点类型
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
    G->edge_num = 16;   // 边数 

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

    // 添加无向且有权图的边
    G->arc[0][1] = 1;  
    G->arc[0][2] = 5;  

    G->arc[1][2] = 3;  
    G->arc[1][3] = 7;  
    G->arc[1][4] = 5;  

    G->arc[2][4] = 1;  
    G->arc[2][5] = 7; 

    G->arc[3][4] = 2;  
    G->arc[3][6] = 3;  

    G->arc[4][5] = 3;  
    G->arc[4][6] = 6; 
    G->arc[4][7] = 9;

    G->arc[5][7] = 5;

    G->arc[6][7] = 2;
    G->arc[6][8] = 7;

    G->arc[7][8] = 4;

    // 无向图的对称矩阵分布
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = i; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//============================= Dijkstra算法 =============================
// 辅助函数choose：选择未访问顶点中distance最小的顶点minPos，作为中间点
int choose(int distance[], int found[], int vertex_num)
{
    int min = MAX;    // 初始化最小距离为极大值
    int minPos = -1;  // 记录具有最小距离的顶点位置

    // 选择源点到所有未访问的顶点i(即found[i]=0)的路径中，距离最小的顶点i作为中间点minPos
    for (int i = 0; i < vertex_num; i++)
    {
        if (distance[i] < min && found[i] == 0)
        {
            min = distance[i]; 
            minPos = i;
        }
    }
    return minPos;
}

// Dijkstra算法
void dijkstra(Mat_Graph G, int begin)  // begin为源点
{
    int found[MAXSIZE];    // found[i]表示顶点i是否已访问，1表示访问，0表示未访问
    int path[MAXSIZE];     // path[i]表示begin->i的最短路径中，i的前驱顶点索引(-1表示begin)
    int distance[MAXSIZE]; // distance[i]表示begin->i的最短路径距离值

    // 初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        found[i] = 0;
        path[i] = -1; 
        distance[i] = G.arc[begin][i];
    }

    // 源点begin的设置
    found[begin] = 1;
    distance[begin] = 0;

    int next;  // 记录中间点
    // 循环G.vertex_num-1次,每次循环便访问一个顶点并作为中间点,使得所有顶点都访问(注:源点已访问)
    for (int i = 1; i < G.vertex_num; i++)
    {
        next = choose(distance, found, G.vertex_num); // 在未访问点中获取中间点
        found[next] = 1;        // 此时中间点便已访问

        // 遍历所有顶点j，通过新路径begin->next->j与原路径begin->j的长短比较来更新最短路径
        for(int j = 0; j < G.vertex_num; j++)
        {
            if (found[j] == 0)
            {
                // 当begin->next->j的路径小于begin->j的路径，就更新j的最短路径
                if (distance[next] + G.arc[next][j] < distance[j])
                {
                    distance[j] = distance[next] + G.arc[next][j];
                    path[j] = next; // 在更新的最短路径下，记录j的前驱为中间点next
                }
            }
        }
    }

    // 将V_begin -> Vi的最短路径的长度与走法都打印下来
    for (int i = 1; i < G.vertex_num; i++)
    {
        // 打印V_begin -> Vi的最短路径长度
        printf("V%d -> V%d : %d\n", begin, i, distance[i]);

        // 打印V_begin -> Vi的最短路径走法，形式为：Vi <- ... <- V_begin
        int j = i;  // j用来记录前驱点
        printf("V%d <- ", i);
        while (path[j] != -1) // 顶点j的前驱为-1(即源点)时循环停止
        {
            printf("V%d <- ", path[j]);
            j = path[j];
        }
        printf("V%d\n", begin);
    }
}



//============================= Floyd算法 =============================
void floyd(Mat_Graph G)
{
    int path[MAXSIZE][MAXSIZE];     // path[i][j]表示i->j的最短路径中，i的后继顶点
    int distance[MAXSIZE][MAXSIZE]; // distance[i][j]表示i->j的最短路径距离值

    // 初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            distance[i][j] = G.arc[i][j];
            path[i][j] = j;
        }
    }
    // i: 起始顶点  k: 中转顶点  j: 终止顶点  
    for (int k = 0; k < G.vertex_num; k++)
    {
        for (int i = 0; i < G.vertex_num; i++)
        {
            for (int j = 0; j < G.vertex_num; j++)
            {
                if (distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    // 打印所有顶点对的最短路径信息
    int k; // 记录i->j的最短路径的中转顶点
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            printf("V%d -> V%d  weight: %d  ", i, j, distance[i][j]);
            k = path[i][j];
            printf("path: V%d", i);
            while (k != j)
            {
                printf(" -> V%d", k);
                k = path[k][j];
            }
            printf(" -> V%d\n", j);
        }
        printf("\n");
    }
}




int main()
{
    // 创建邻接矩阵G
    Mat_Graph G;
    create_graph(&G);

    // Dijkstra算法
    printf("----------Dijkstra算法----------\n");
    int begin = 0; // 以第0顶点为源点
    dijkstra(G, begin);

    // Floyd算法
    printf("----------Floyd算法----------\n");
    floyd(G);
}