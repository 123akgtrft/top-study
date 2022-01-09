#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100
#define INFINITY 65535

typedef struct
{
    int begin;
    int end;
    int weight;
}Edge;

typedef struct
{
    Edge edges[MAXVEX];
    int numEdges;
    int numVertexes;
}MGraph;

int cmp(const void*a,const void*b);
void CreeateMGraph(MGraph*G);//构造边集数组
int find(int*parents,int f);
void MiniSpanTree_Kruskal(MGraph G);//Kruskal算法生成最小生成树

int main(void)
{
    MGraph G;
    CreeateMGraph(&G);
    MiniSpanTree_Kruskal(G);
    return 0;
}

int cmp(const void*a,const void*b)
{
    return ((Edge*)a)->weight-((Edge*)b)->weight;
}
void CreeateMGraph(MGraph*G)
{
    int i,j,k,w;
    printf("Input the numVertexes and the numEdges:\n"); 
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numEdges;i++)
        G->edges[i].weight=INFINITY;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引)，和权重:");
        scanf("%d %d %d",&i,&j,&w);
        G->edges[k].begin=i;
        G->edges[k].end=j;
        G->edges[k].weight=w;
    }
    qsort(G->edges,G->numEdges,sizeof(Edge),cmp);
}
int find(int*parents,int f)
{
    while(parents[f]>0)
        f=parents[f];
    return f;
}
void MiniSpanTree_Kruskal(MGraph G)
{
    int i,n,m;
    int parents[MAXVEX];//判断边与边是否形成回路
    for(i=0;i<G.numVertexes;i++)
        parents[i]=0;
    for(i=0;i<G.numEdges;i++)
    {
        n=find(parents,G.edges[i].begin);
        m=find(parents,G.edges[i].end);
        if(n!=m)
        {
            parents[n]=m;
            printf("(%d, %d) %d",G.edges[i].begin,G.edges[i].end,G.edges[i].weight);
        }
    }
}
