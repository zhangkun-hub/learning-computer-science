/*
一、图的深度优先遍历(Depth-first traversal, DFS)：
    思想：从给定顶点开始，只要访问的顶点的左边跟其他顶点有连接，就访问下一个顶点，依次进行下去，
        直到左边再无连接或左边顶点已经访问过，此时再访问该顶点的右边相连的顶点。

    注意：以上是采用左边方向进行深度探索，但深度优先思想跟方向无关，可以选择任何方向的边进行深度探索


二、图的广度优先遍历(Breadth-first traversal, BFS)：
    思想：从一个顶点开始，先访问该顶点(即第一层的节点)；然后访问该顶点的所有相连的顶点(类似于树的
        孩子节点)，这些顶点构成第二层节点；接着再访问第一层节点所有相连着的顶点(已访问过的不算)，
        由此构成第三层节点。依次进行下去，直到所有顶点访问完毕，这就是广度优先遍历的思想。

    注意：广度优先遍历需要用到队列。
*/
#include <stdio.h>

#define MAXSIZE 100
typedef char VertexType; // 顶点类型
typedef int EdgeType;    // 边的权值类型(0或1)

// 图的邻接矩阵结构体定义
typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Graph;

// visited[]数组的第i个元素表示第i个顶点是否在dfs遍历中已经访问过，如果没有赋值0，否则赋值1
int visited[MAXSIZE];

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
            G->arc[i][j] = 0;
        }
    }

    // 添加无向且无权图的边
    // A-B  A-F
    G->arc[0][1] = 1;  
    G->arc[0][5] = 1;  
    // B-C  B-G  B-I
    G->arc[1][2] = 1;  
    G->arc[1][6] = 1;  
    G->arc[1][8] = 1;  
    // C-D  C-I
    G->arc[2][3] = 1;  
    G->arc[2][8] = 1; 
    // D-E  D-G  D-H  D-I
    G->arc[3][4] = 1;  
    G->arc[3][6] = 1;  
    G->arc[3][7] = 1; 
    G->arc[3][8] = 1; 
    // E-F  E-H
    G->arc[4][5] = 1;  
    G->arc[4][7] = 1;
    // F-G
    G->arc[5][6] = 1;
    // G-H
    G->arc[6][7] = 1;
    // 无向图的对称矩阵分布
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

// ===================== 深度优先遍历(Depth-first traversal, DFS) =========================
void dfs(Mat_Graph G, int i)  // 参数i表示第i个顶点
{
    // 访问第i个顶点
    printf("%c ", G.vertex[i]);
    visited[i] = 1;   // 第i个顶点已访问，则赋值为1

    // 循环所有顶点j
    for (int j = 0; j < G.vertex_num; j++)
    {
        // 如果顶点i与顶点j有边相连，并且顶点j未被访问过，则递归调用dfs访问顶点j
        if (G.arc[i][j] == 1 && visited[j] == 0)
        {
            dfs(G, j);
        }
    }
}


// ==================== 广度优先遍历(Breadth-first traversal, BFS) ========================
// 1.创建队列(广度优先遍历需要，里面存储顶点的下标值)
int front = 0;      // 队头指针
int rear = 0;       // 队尾指针
int queue[MAXSIZE]; // 队列数组

// 2.进行bfs遍历
void bfs(Mat_Graph G)
{
    // 最先访问第0个顶点
    int i = 0;
    printf("%c ", G.vertex[i]);
    visited[i] = 1;   // 顶点i已访问，赋值1
    queue[rear] = i;  // 将第0个顶点下标入队
    rear++;           // 队尾指针+1

    // 当队列不为空时，一直循环
    while (front != rear)
    {
        // 将队头元素(即顶点下标)出队，并赋值给i
        i = queue[front];
        front++;

        // 遍历所有顶点
        for (int j = 0; j < G.vertex_num; j++)
        {
            // 如果顶点i与顶点j有边相连，并且顶点j未被访问过，则访问顶点j并入队
            if (G.arc[i][j] == 1 && visited[j] == 0)
            {
                printf("%c ", G.vertex[j]);
                visited[j] = 1;  // 顶点j已访问，赋值1
                queue[rear] = j;
                rear++;
            }
        }
    }
    printf("\n");
}




int main()
{
    // 创建邻接矩阵G
    Mat_Graph G;
    create_graph(&G);

    // 一、深度优先遍历(Depth-first traversal, DFS)
    // 1.visited[]数组初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        visited[i] = 0;
    }
    // 2.dfs遍历
    printf("深度优先遍历结果：");
    dfs(G, 0);  // 深度优先遍历结果：A B C D E F G H I
    printf("\n");


    // 二、广度优先遍历(Breadth-first traversal, BFS)
    // 1.visited[]数组初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        visited[i] = 0;
    }
    // 2.bfs遍历
    printf("广度优先遍历结果：");
    bfs(G);    // 广度优先遍历结果：A B F C I E G D H



    return 0;
}