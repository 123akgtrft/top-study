#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100
#define INFINITY 65535

typedef struct
{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph*G);//构造邻接矩阵

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    printf("%c ",G.vexs[0]);
    return 0;
}

void CreateMGraph(MGraph*G)
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