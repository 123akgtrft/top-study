#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
邻接矩阵创建图,深度优先遍历
*/
#define MAXVEX 100
#define INFINITY 65535
bool visited[MAXVEX];

typedef struct
{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph*G);//构造邻接矩阵
void DFS(MGraph*G,int i);//邻接矩阵的深度优先递归算法
void DFSTraverse(MGraph G);//邻接矩阵的深度遍历操作

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    DFSTraverse(G);
    return 0;
}

void CreateMGraph(MGraph*G)//构造邻接矩阵
{
    int i,j,k,w;
    printf("Input the numVertexes and the numEdges:\n"); 
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++){
        printf("第%d个节点名称",i+1);
        scanf("%d",&G->vexs[i]);
    }
    for(i=0;i<G->numVertexes;i++)
        for(j=0;j<G->numEdges;j++)
            G->arc[i][j]=INFINITY;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j和权数:");
        scanf("%d %d %d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}
void DFS(MGraph*G,int i)
{
    int j;
    visited[i]=true;
    printf("%d ",G->vexs[i]);
    for(j=0;j<G->numVertexes;j++)
    if(G->arc[i][j]==1&&G->vexs[j]==false)
    DFS(&G,j);
}
void DFSTraverse(MGraph G)
{
    int i;
    for(i=0;i<G.numVertexes;i++)
    visited[i]=false;
    for(i=0;i<G.numVertexes;i++)
    {
        if(visited[i]==false)
        DFS(&G,i);
    }
}
