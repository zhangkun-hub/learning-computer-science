/*
图的顺序存储结构————邻接矩阵(Adjacency matrix)
一、结构：使用一个n*n的二维数组matrix来表示具有n个顶点的图。
    1.无向图(是对称矩阵)：
        (1)对于无权图，matrix[i][j] = 1表示顶点i到j之间有边，0表示无边。
        (2)对于带权图，matrix[i][j]存储边的权值，用一个特殊值（如∞）表示无边，但对角线权值为0。

    2.有向图：
        (1)对于无权图，matrix[i][j] = 1表示从顶点i指向j的方向上有边，0表示该方向上无边。
        (2)对于带权图，matrix[i][j]存储方向边的权值，用一个特殊值（如 ∞）表示无边。

二、特点与性质：
    1.直观易理解，逻辑关系一目了然。
    2.空间复杂度高，为O(n²)，与边数无关。对于顶点多、边少的稀疏图，空间浪费严重。
    3.可以方便地表示自环（查看对角线元素）。
    4.对于无向图，矩阵是对称的，可以采用压缩存储。

三、优点：
    1.查询效率高：判断任意两个顶点间是否有边，或获取边的权值，时间复杂度为O(1)。
    2.操作简便：添加或删除一条边非常快，只需修改一个数组元素。
    3.便于计算：某些基于矩阵运算的图算法（如计算传递闭包）实现方便。

四、缺点：
    1.空间占用大：是其主要缺点，不适用于顶点数巨大的稀疏图。
    2.添加/删除顶点开销大：需要重新分配和复制整个矩阵。
    3.遍历邻接点效率低：要找出顶点 v的所有邻接点，需要扫描一整行，耗时O(n)，即使它只有
        很少的邻居。

五、应用场景：
    1.顶点数量相对较少（n不大）的稠密图。
    2.需要频繁判断任意两个顶点间是否存在边的场景。
    3.适合进行矩阵运算的图算法。

六、代码表示：见下面邻接矩阵结构体
*/
#include <stdio.h>

#define MAXSIZE 100       // 最大顶点数
#define Max 0x7fffffff    // 用int类型的最大值0x7fffffff表示“无穷”，即无边，并命名为Max
typedef char VertexType;  // 顶点类型
typedef int EdgeType;     // 边的权值类型

// 图的邻接矩阵结构体定义
typedef struct
{
    VertexType vertex[MAXSIZE];     // 顶点数组
    EdgeType arc[MAXSIZE][MAXSIZE]; // 邻接矩阵(二维数组)
    int vertex_num;                 // 顶点个数
    int edge_num;                   // 边的条数
}Mat_Graph;

// 创建邻接矩阵
void create_graph(Mat_Graph* G)
{
    G->vertex_num = 4; // 顶点数，用V0~V3表示顶点
    G->edge_num = 5;   // 边数 

    // 顶点命名
    G->vertex[0] = '0';
    G->vertex[1] = '1';
    G->vertex[2] = '2';
    G->vertex[3] = '3';

    //=================无权图的赋值==============
    // 初始化邻接矩阵
    // for (int i = 0; i < G->vertex_num; i++)
    // {
    //     for (int j = 0; j < G->vertex_num; j++)
    //     {
    //         G->arc[i][j] = 0;
    //     }
    // }

    // // 添加无向图的边(是对称矩阵)
    // G->arc[0][1] = 1;  G->arc[1][0] = 1;  // V0-V1
    // G->arc[0][2] = 1;  G->arc[2][0] = 1;  // V0-V2
    // G->arc[0][3] = 1;  G->arc[3][0] = 1;  // V0-V3
    // G->arc[1][2] = 1;  G->arc[2][1] = 1;  // V1-V2
    // G->arc[2][3] = 1;  G->arc[3][2] = 1;  // V2-V3

    // 添加有向图的边
    // G->arc[0][3] = 1;  // V0 -> V3
    // G->arc[1][0] = 1;  // V1 -> V0
    // G->arc[1][2] = 1;  // V1 -> V2
    // G->arc[2][0] = 1;  // V2 -> V0
    // G->arc[2][1] = 1;  // V2 -> V1


    //=================有权图的赋值==============
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
                G->arc[i][j] = Max; // 初始值均设置为无穷大MAX
            }
        }
    }

    // // 添加无向图的边(是对称矩阵)
    // G->arc[0][1] = 3;  G->arc[1][0] = 3;    // V0-V1
    // G->arc[0][2] = 0;  G->arc[2][0] = 0;    // V0-V2
    // G->arc[0][3] = 2;  G->arc[3][0] = 2;    // V0-V3
    // G->arc[1][2] = -1;  G->arc[2][1] = -1;  // V1-V2
    // G->arc[2][3] = 5;  G->arc[3][2] = 5;    // V2-V3

    // 添加有向图的边
    G->arc[0][3] = 3;  // V0 -> V3
    G->arc[1][0] = 5;  // V1 -> V0
    G->arc[1][2] = 2;  // V1 -> V2
    G->arc[2][0] = 6;  // V2 -> V0
    G->arc[2][1] = 4;  // V2 -> V1
}

// 遍历邻接矩阵
void print_matrix(Mat_Graph G)
{
    printf("邻接矩阵表示如下：\n");
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            // // 无权图的操作
            // printf("%d ", G.arc[i][j]);

            // 有权图的操作
            if (G.arc[i][j] == Max)
                printf("Max ");
            else
                printf("%3d ", G.arc[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    Mat_Graph G;      // 创建一个邻接矩阵结构体
    create_graph(&G); // 初始化邻接矩阵
    print_matrix(G);  // 遍历输出邻接矩阵


    return 0;
}
