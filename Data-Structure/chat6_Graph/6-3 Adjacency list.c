/*
邻接表(Adjacency list)
一、结构：为每个顶点建立一个单链表（或数组、动态数组）。这个链表存储了所有与该顶点直接相连的
        邻接点的信息。
    1.对于无权图，链表节点通常只包含邻接点的编号。
    2.对于带权图，链表节点还需额外包含边的权值。
    3.对于无向图，除了从顶点指向邻接点的出边形式(即邻接表)，还有从各个顶点指向该顶点的入边形式
        (即逆邻接表)。

二、代码实现：
        需要用三个不同的结构体实现，其中一个表示该顶点的邻接点所构成的边的结构体，另一个表示顶点与
    指向第一个邻接点的结构体(并定义存储该顶点的数组)，最后一个用来表示整个图的邻接表结构体。
    具体图像见视频p19，具体代码见下面。

三、特点与性质：
    1.空间利用率高，存储所有顶点和边，空间复杂度为O(n+e)，其中n为顶点数，e为边数。特别适合稀疏图。
    2.表示方式不唯一，取决于顶点编号顺序和边的插入顺序。
    3.对于有向图，可以方便地分出边表（邻接表）和入边表（逆邻接表）。

四、优点：
    1.节省存储空间，尤其对于稀疏图。
    2.遍历邻接点高效：查找顶点v的所有邻接点，只需遍历它的链表，时间复杂度为O(degree(v))。
    3.添加顶点灵活：容易动态添加新的顶点。

五、缺点：
    1.查询边效率较低：判断顶点 i到 j是否有边，需要遍历 i的邻接表，最坏情况 O(n)。
    2.删除边操作稍慢：需要在链表中查找并删除节点。
    3.实现相对复杂：需要维护多个链表结构。

六、应用场景：
    1.绝大多数稀疏图的存储，这是最常用、最经典的存储方式。
    2.需要频繁遍历某个顶点所有邻居的算法，如广度优先搜索、深度优先搜索、Dijkstra算法等。
    3.顶点数量动态变化的图。
*/
// ===============================================================================
// 以下代码包含了有向图、无向图、带权图和无权图情形，但可以运行的代码是无向图的无权图情形
// ===============================================================================
#include<stdio.h>
#include <stdlib.h>

#define MAXVEX 100 // 最大顶点数


// 定义顶点的邻接点结构体
typedef struct EdgeNode{
    int adjvex;            // 记录某顶点的邻接点(即由边相连的顶点)在顶点数组中的下标
    // int weight;            // 记录边的权值 
    struct EdgeNode* next; // 指向下一个邻接点(因为一个顶点的邻接点可能不止一个)
}EdgeNode;


// 定义顶点结构体
typedef struct VertexNode{
    char data;                // 存储顶点信息(这里用字符代替)
    EdgeNode* firstedge;      // 从该顶点开始指向第一个邻接点的指针
}VertexNode, AdjList[MAXVEX]; // AdjList[MAXVEX]表示对存储结构体VertexNode的数组的起别名


// 图的邻接表结构体
typedef struct{
    AdjList adjList; // 邻接表，存储顶点节点的数组。该结构等价于VertexNode adjList[MAXVEX]
    int numVertexes; // 顶点数
    int numEdges;    // 边数
}GraphAdjList;


// 创建邻接表(无向图与有向图只在该函数的from->to与to->from部分有区别，其他完全没区别)
void createGraph(GraphAdjList* G)
{
    G->numVertexes = 4; // 4个顶点
    G->numEdges = 5;    // 5条边

    // 顶点命名(V0 ~ V3)
    for (int i = 0; i < G->numVertexes; i++)
    {
        G->adjList[i].data = '0' + i;
        G->adjList[i].firstedge = NULL;
    }

    // 边集合，即哪两个顶点之间有边的连接(注意有向图必须按照边的方向来存储两顶点)
    int edges[5][2] = {
        {0, 1}, {0, 2}, {0, 3},
        {1, 2}, {2, 3}
    };

    // // 边集合(带权图情形，其中中括号第三个值就是该边的权值)
    // int edges[5][3] = {
    //     {0, 3, 30}, 
    //     {1, 0, 50}, 
    //     {1, 2, 20},
    //     {2, 0, 60}, 
    //     {2, 1, 40}
    // };

    // 遍历边集合，将顶点结构体VertexNode与其对应的邻接点结构体EdgeNode按链表头插法方式相连
    for (int i = 0; i < G->numEdges; i++)
    {
        int from = edges[i][0];   // 记录第i条边的一端顶点下标
        int to = edges[i][1];     // 记录第i条边的另一端顶点下标
        // int weight = edges[i][2]; // 记录第i条边的权值

        // from -> to (对于有向图的正邻接表，只有 from -> to，而无 to -> from)
        EdgeNode* e1 = (EdgeNode*)malloc(sizeof(EdgeNode)); // 创建邻接点结构体EdgeNode
        e1->adjvex = to;       // 记录顶点from的邻接点to
        // e1->weight = weight;   // 将from与邻接点to对应的边权值赋值给该邻接点结构体中
        e1->next = G->adjList[from].firstedge; 
        G->adjList[from].firstedge = e1;        

        // to -> from (对于有向图的逆邻接表，只有 to -> from，而无 from -> to)
        EdgeNode* e2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        e2->adjvex = from;
        // e2->weight = weight;
        e2->next = G->adjList[to].firstedge;
        G->adjList[to].firstedge = e2;
    }
}


// 打印邻接表
void printGraph(GraphAdjList G)
{
    printf("图的邻接表如下：\n");
    for (int i = 0; i < G.numVertexes; i++)
    {
        // 打印顶点V0 ~ Vn与连接邻接点的符号 ->
        printf("V%c -> ", G.adjList[i].data);
        EdgeNode* p = G.adjList[i].firstedge;

        // 打印顶点Vi的邻接点
        while (p){
            printf("%d -> ", p->adjvex);
            p = p->next;
        }

        printf("^\n"); // 顶点的所有邻接点打印完，以^结尾
    }  
}



int main()
{
    GraphAdjList G;
    createGraph(&G);
    printGraph(G);

    return 0;
}