#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100
#define INFINITY 65535

typedef struct EdgeNode//边表节点
{
    int adjvex;//存储该顶点对应的下标
    int weight;//权重
    struct EdgeNode* next;//指向下一个邻接点
}EdgeNode;

typedef struct VertexNode//顶点表节点
{
    int data;//顶点域，存储顶点信息
    EdgeNode*firstedge;//边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct//表示整个图
{
    AdjList adjlist;
    int numVertexes,numEdges;//图中当前节点数和边数
}GraphAdjList;

void CreateALGraph(GraphAdjList*G)
{
    int i,j,k;
    EdgeNode *e;
    printf("Input the numVertexes and numEdges:");
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++)//顶点表赋值
    {
        G->adjlist[i].data=i;
        G->adjlist[i].firstedge=NULL;//将边表置为空
    }
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(vi,vj)上的顶点序号i,j:");
        scanf("%d %d",&i,&j);
        e=(EdgeNode*)malloc(sizeof(EdgeNode));
        e->adjvex=j;
        e->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=e;
        e=(EdgeNode*)malloc(sizeof(EdgeNode));
        e->adjvex=i;
        e->next=G->adjlist[j].firstedge;
        G->adjlist[j].firstedge=e;
    }
}
int main(void)
{
    GraphAdjList G;
    CreateALGraph(&G);

    return 0;
}