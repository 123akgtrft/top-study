#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100
#define INFINITY 65535

typedef struct EdgeNode//边表节点
{
    int tailvex;//存储该弧尾对应的下标
    int headvex;//存储该弧头对应的下标
    int weight;//权重
    EdgeNode* headlink;//作为新的弧头
    EdgeNode* taillink;//作为新的弧尾
}EdgeNode;

typedef struct VertexNode//顶点表节点
{
    int data;//顶点域，存储顶点信息
    EdgeNode*firstin;//入边表头指针
    EdgeNode*firstout;//出边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct//表示整个图
{
    AdjList adjlist;
    int numVertexes,numEdges;//图中当前节点数和边数
}GraphAdjList;

void CreateCross(GraphAdjList*G)
{
    int i,j,k;
    EdgeNode *e;
    printf("Input the numVertexes and numEdges:");
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++)//顶点表赋值
    {
        G->adjlist[i].data=i;
        G->adjlist[i].firstin=NULL;//将边表置为空
        G->adjlist[i].firstout=NULL;//将边表置为空
    }
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(vi,vj)上的顶点序号i,j:");
        scanf("%d %d",&i,&j);
        e=(EdgeNode*)malloc(sizeof(EdgeNode));
        e->tailvex=i;
        e->headvex=j;
        e->headlink=G->adjlist[j].firstin;
        e->taillink=G->adjlist[i].firstout;
        /*
        从边表指向顶点表，原因是可能存在一个顶点的入度大于二，这时就需要以一个入度的尾节点作为中转，从而指向下一个入度的尾节点;
        若从顶点表指向边表，则会产生难以处理的情况，因为如果存在中转的情况，在中转的时候必须以某个边表节点指向下一个边表节点，会产生不一致的情况
        */
        G->adjlist[j].firstin=G->adjlist[i].firstout=e;
    }
}