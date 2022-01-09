#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
邻接矩阵创建图,求最小生成树
*/
#define MAXVEX 100
#define INFINITY 65535


typedef struct
{
    char vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;


void CreateMGraph(MGraph*G);//构造邻接矩阵
void MiniSpanTree_Prim(MGraph G);//prim算法求最小生成树


int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G);
    return 0;
}

void CreateMGraph(MGraph*G)//构造邻接矩阵
{
    int i,j,k,w;
    printf("Input the numVertexes and the numEdges:\n"); 
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++){
        printf("第%d个节点名称:",i+1);
        getchar();
        scanf("%c",&G->vexs[i]);
    }
    for(i=0;i<G->numVertexes;i++)
        for(j=0;j<G->numEdges;j++)
            G->arc[i][j]=INFINITY;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引)，和权重:");
        scanf("%d %d %d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}
void MiniSpanTree_Prim(MGraph G)
{
    int min,i,j,k;
    int lowcost[MAXVEX];//保存间边的权值
    int adjvex[MAXVEX];//保存顶点相关下标
    lowcost[0]=0;
    adjvex[0]=0;
    for(i=1;i<G.numVertexes;i++){
        lowcost[i]=G.arc[0][i];
        adjvex[i]=0;
    }
    for(i=1;i<G.numVertexes;i++)
    {
        min=INFINITY;
        j=1,k=0;
        while(j<G.numVertexes)
        {
            if(lowcost[j]!=0&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
            j++;
        }
        printf("( %d , %d )",adjvex[k],k);
        lowcost[k]=0;
        for(j=1;j<G.numVertexes;j++){
            if(lowcost[j]!=0&&G.arc[k][j]<lowcost[j]){
                lowcost[j]=G.arc[k][j];
                adjvex[j]=k;
            }
        }
    }
}
