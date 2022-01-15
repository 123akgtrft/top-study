#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100

int*etv,*ltv;
int *stack2;
int top2;

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
int TopologicalSort(GraphAdjList*G);//拓扑排序(将入度为0的顶点压入栈)
void CriticalPath(GraphAdjList*G);//求关键路径

int main(void)
{
    GraphAdjList G;
    CreateALGraph(&G);
    CriticalPath(&G);
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
        printf("输入边(vi,vj)上的顶点序号i,j (i,j是顶点的索引)和权值:");
        getchar();
        scanf("%d %d %d",&i,&j,&w);
        e1=(EdgeNode*)malloc(sizeof(EdgeNode));
        e1->adjvex=j;
        e1->weight=w;
        e1->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=e1;
        G->adjlist[j].in++;
    }
}
int TopologicalSort(GraphAdjList*G)
{
    EdgeNode*e;
    int i,j,getting,k;
    int top=0,count=0;
    int*stack=(int*)malloc(sizeof(int)*G->numVertexes);
    for(i=0;i<G->numVertexes;i++)
        if(G->adjlist[i].in==0)
            stack[top++]=i;
    etv=(int*)malloc(sizeof(int)*G->numVertexes);//etv初始化
    for(i=0;i<G->numVertexes;i++)
        etv[i]=0;
    stack2=(int*)malloc(sizeof(int)*G->numVertexes);
    while(top!=0)//当整个图中不存在入度为0的节点时退出
    {
        getting=stack[--top];
        stack2[top2++]=getting;
        count++;
        for(e=G->adjlist[getting].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            if(!(--G->adjlist[k].in))
            stack[top++]=k;
            if((etv[getting]+e->weight>etv[k]))//etv[k]为从源点到k节点的弧中的最大值
            etv[k]=etv[getting]+e->weight;//不断更新最大值
        }
    }
    if(count<G->numVertexes)
    return 0;
    else
    return 1;
}
void CriticalPath(GraphAdjList*G)
{
    EdgeNode*e;
    int i,j,k,gettop;
    int ete,lte;
    TopologicalSort(G);
    ltv=(int*)malloc(sizeof(int)*G->numVertexes);
    for(i=0;i<G->numVertexes;i++)
        ltv[i]=etv[G->numVertexes-1];
    while(top2!=0)
    {
        gettop=stack2[--top2];
        for(e=G->adjlist[gettop].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            if(ltv[gettop]+e->weight>ltv[k])
            ltv[gettop]=ltv[k]-e->weight;
        }
    }
    for(i=0;i<G->numVertexes;i++)
    {
        for(e=G->adjlist[i].firstedge;e;e=e->next)
        {
            k=e->adjvex;
            ete=etv[i];
            lte=ltv[k]-e->weight;
            if(ete==lte)
            printf("<%c,%c> length= %d\n",G->adjlist[i].data,
            G->adjlist[k].data,e->weight);
        }
    }
}