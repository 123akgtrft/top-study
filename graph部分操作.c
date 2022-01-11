#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
邻接矩阵创建图,Warshall算法求可达性矩阵
*/
#define MAXVEX 100
#define INFINITY 65535

bool visited[MAXVEX];

typedef struct
{
    char vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph*G);//构造邻接矩阵
void Warshall(MGraph*G);//求可达性矩阵，并打印
bool is_digraph(MGraph G);//有向图返回true,无向图返回false
bool is_reach(MGraph G,int begin,int end);//判断begin顶点和end顶点之间是否有路(不限方向)


int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    //Warshall(&G);
    bool result=is_reach(G,3,1);
    printf(" %d ",result);
    return 0;
}

void CreateMGraph(MGraph*G)//构造邻接矩阵
{
    int i,j,k,w;
    printf("Input the numVertexes and the numEdges:\n"); 
    scanf("%d %d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++){
        printf("第%d个节点名称",i+1);
        getchar();
        scanf("%c",&G->vexs[i]);
    }
    for(i=0;i<G->numVertexes;i++)
        for(j=0;j<G->numEdges;j++)
            G->arc[i][j]=0;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引):");
        scanf("%d %d",&i,&j);
        G->arc[i][j]=1;
        //G->arc[j][i]=G->arc[i][j];
    }
}
void Warshall(MGraph*G)
{
    int i,j,k;
    for(j=0;j<G->numVertexes;j++){
        for(i=0;i<G->numVertexes;i++){
            if(G->arc[j][i]==1){
                for(k=0;k<G->numVertexes;k++){
                    if(G->arc[k][j]==1){
                        G->arc[k][i]=1;
                    }
                }
            }
        }
    }
    for(j=0;j<G->numVertexes;j++){
        for(i=0;i<G->numVertexes;i++){
            printf("%d ",G->arc[j][i]);
        }printf("\n");
    }
}
bool is_digraph(MGraph G)
{
    int i,j;
    for(i=0;i<G.numVertexes-1;i++){
        for(j=i+1;j<G.numVertexes;j++){
            if(G.arc[i][j]!=G.arc[j][i])
            return true;//为有向图
        }
    }
    return false;//为无向图
}
bool is_reach(MGraph G,int begin,int end)
{
    Warshall(&G);
    if(G.arc[begin][end]||G.arc[end][begin])
    return true;
    else
    return false;
}
