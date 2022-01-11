#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
邻接表创建图
*/

#define MAXVEX 100
#define INFINITY 65535
bool visited[MAXVEX];

typedef struct EdgeNode//边表节点
{
    int adjvex;//存储该顶点对应的下标
    int weight;//权重
    struct EdgeNode* next;//指向下一个邻接点
}EdgeNode;

typedef struct VertexNode//顶点表节点
{
    int in;
    char data;//顶点域，存储顶点信息
    EdgeNode*firstedge;//边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct//表示整个图
{
    AdjList adjlist;
    int numVertexes,numEdges;//图中当前节点数和边数
}GraphAdjList;

void CreateALGraph(GraphAdjList*G);
int TopologicalSort(GraphAdjList*G);

int main(void)
{
    GraphAdjList G;
    CreateALGraph(&G);
    TopologicalSort(&G);
    return 0;
}

void CreateALGraph(GraphAdjList*G)
{
    int i,j,k,w;
    EdgeNode *e1,*e2;
    printf("Input the numVertexes and numEdges:");
    scanf("%d %d",&(G->numVertexes),&(G->numEdges));
    for(i=0;i<G->numVertexes;i++){
        printf("第%d个节点名称:",i+1);
        getchar();
        scanf("%c",&(G->adjlist[i].data));
        G->adjlist[i].firstedge=NULL;//将边表置为空
        G->adjlist[i].in=0;
    }
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(vi,vj)上的顶点序号i,j (i,j是顶点的索引):");
        getchar();
        scanf("%d %d",&i,&j);
        e1=(EdgeNode*)malloc(sizeof(EdgeNode));
        e1->adjvex=j;
        e1->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=e1;
        G->adjlist[j].in++;
    }
}
int TopologicalSort(GraphAdjList*G)
{
    EdgeNode*e;
    int i,j,getting;
    int top=0,count=0;
    int*stack=(int*)malloc(sizeof(int)*G->numVertexes);
    for(i=0;i<G->numVertexes;i++)
        if(G->adjlist[i].in==0)
            stack[top++]=i;
    while(top!=0)//当整个图中不存在入度为0的节点时退出
    {
        getting=stack[--top];
        printf("V%c -> ",G->adjlist[getting].data);
        count++;
        for(e=G->adjlist[getting].firstedge;e;e=e->next)
        {
            j=e->adjvex;
            if(!(--G->adjlist[j].in))
            stack[top++]=j;
        }
    }
    if(count<G->numVertexes)
    return 0;
    else
    return 1;
}