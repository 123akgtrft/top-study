#include <stdio.h>

#define MAXVEX 10
#define INFINITY 65535

int P[MAXVEX][MAXVEX];//记录路径下标
int D[MAXVEX][MAXVEX];//记录路径长度

typedef struct
{
    char vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph*G);//构造邻接矩阵
void lowest_path_Floyd(MGraph G);//Floyd算法实现
void print_path(MGraph G);//打印路径

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    lowest_path_Floyd(G);
    print_path(G);
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
            G->arc[i][j]=INFINITY;
            if(i==j)
            G->arc[i][j]=0;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引)和权重 用空格隔开:");
        scanf("%d %d %d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];
    }
}
void lowest_path_Floyd(MGraph G)
{
    int i,j,k;
    for(i=0;i<G.numVertexes;i++){
        for(j=0;j<G.numVertexes;j++){
            P[i][j]=j;
            D[i][j]=G.arc[i][j];
        }
    }
    for(i=0;i<G.numVertexes;i++){
        for(j=0;j<G.numVertexes;j++){
            for(k=0;k<G.numVertexes;k++){
                if(D[i][k]>D[i][j]+D[j][k]){
                    P[i][k]=P[i][j];
                    D[i][k]=D[i][j]+D[j][k];
                }
            }
        }
    }
}
void print_path(MGraph G)
{
    int i,j,k;
    for(i=0;i<G.numVertexes;i++){
        for(j=i+1;j<G.numVertexes;j++){
            printf("V%d-V%d weight:%d",i,j,D[i][j]);
            k=P[i][j];
            while(k!=j)
            {
                printf("->V%d",k);
                k=P[k][j];
            }
            printf("->V%d\n",j);
        }
        printf("\n");
    }
}
