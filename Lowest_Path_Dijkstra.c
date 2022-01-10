#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
Dijkstra算法,求最短路径
*/
#define MAXVEX 9
#define INFINITY 65535

int lowest_path[MAXVEX];//存储最短路径的下标
int lowest_sum[MAXVEX];//存储到各点最短路径的权值和
int visited[MAXVEX];

typedef struct
{
    char vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph*G);//构造邻接矩阵
void lowest_path_Dijkstra(MGraph G);//Dijkstra算法求最短路径
void print_result();//输出结果

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    lowest_path_Dijkstra(G);
    print_result(G);
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
        for(j=0;j<G->numVertexes;j++)
        {
            G->arc[i][j]=INFINITY;
            if(i==j)
            G->arc[i][j]=0;
        }
            
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引)和权重:");
        scanf("%d %d %d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}
void lowest_path_Dijkstra(MGraph G)
{
    int i,j,min,k,step;
    lowest_path[0]=0;
    lowest_sum[0]=0;
    visited[0]=1;//i已经选入
    step=0;//记录前驱
    for(i=1;i<G.numVertexes;i++)//初始化
    {
        lowest_path[i]=0;
        lowest_sum[i]=G.arc[0][i];
        visited[i]=0;//i未选入
    }
    for(i=0;i<G.numVertexes;i++)
    {
        min=INFINITY;
        for(j=0;j<G.numVertexes;j++)
        {
            if(visited[j]==0&&lowest_sum[j]<min)
            {
                min=lowest_sum[j];
                k=j;
            }
        }
        //lowest_path[k]=step;//设置k的前驱为step
        //step=k;//当前循环的k成为下一循环的前驱
        visited[k]=1;
        for(j=0;j<G.numVertexes;j++)
        {
            if(visited[j]==1)
            continue;
            if(lowest_sum[j]>lowest_sum[k]+G.arc[k][j])
            {
                lowest_sum[j]=lowest_sum[k]+G.arc[k][j];
                lowest_path[j]=k;//遇到更短的路径，改变j的前驱为k
            }
        }
    }
}
void print_result(MGraph G)
{
    int n;
    for(int i=0;i<G.numVertexes;i++)
    printf("从V0顶点到 V%d 顶点的最短路径长度为 %d\n",i,lowest_sum[i]);
    while(1)
    {
        printf("你想去那个节点:(输入-1结束)");
        scanf("%d",&n);
        if(n==-1)
        break;
        printf("V%d ",n);
        if(n==0)
        continue;
        while(lowest_path[n]!=0)
        {
            printf("V%d ",lowest_path[n]);
            n=lowest_path[n];
        }
        printf("V0\n",n);
    }
}