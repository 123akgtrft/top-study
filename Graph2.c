#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
邻接矩阵创建图,深度优先遍历，广度优先遍历
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

typedef struct
{
    int data[MAXVEX];
    int front;
    int rear;
}Queue;

void CreateMGraph(MGraph*G);//构造邻接矩阵
void DFS(MGraph*G,int i);//邻接矩阵的深度优先递归算法
void DFSTraverse(MGraph G);//邻接矩阵的深度遍历操作
void InitQueue(Queue*Q);//初始化队列
void EnQueue(Queue*Q,char i);//入队列
void DeQueue(Queue*Q,char*i);//出队列，并将其值赋给i
bool QueueEmpty(Queue Q);//检查队列是否为空
void BFSTraverse(MGraph*G);//邻接矩阵的广度优先遍历

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
        printf("输入边(i,j)的下标i,j (i,j是顶点的索引) 和权数:");
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
void InitQueue(Queue*Q)
{
    Q->rear=0;
    Q->front=0;
}
void EnQueue(Queue*Q,char i)
{
    if((Q->rear)+1%MAXVEX==Q->front){
        printf("队列已满");
        return;
    }
    Q->data[Q->rear]=i;
    Q->rear=(Q->rear+1)%MAXVEX;
}
void DeQueue(Queue*Q,char*i)
{
    if((Q->rear-Q->front+MAXVEX)%MAXVEX==0){
        return;//队列空时不做提示
    }
    *i=Q->data[Q->front];
    Q->front=(Q->front+1)%MAXVEX;
}
bool QueueEmpty(Queue Q)
{
    if((Q.rear-Q.front+MAXVEX)%MAXVEX==0){
        return true;
    }
    return false;
}
void BFSTraverse(MGraph*G)
{
    int i,j;
    Queue Q;
    InitQueue(&Q);
    for(i=0;i<G->numVertexes;i++)
    visited[i]=false;

    if(visited[0]==false)
    {
        printf("%c\t",G->vexs[0]);
        EnQueue(&Q,G->vexs[0]);
        visited[0]=true;
        while(!QueueEmpty(Q))//当队列为空时，循环终止
        {
            DeQueue(&Q,&i);
            for(j=0;j<G->numVertexes;j++)
            {
                if(G->arc[i][j]==1&&visited[j]==false)
                {
                    printf("%c\t",G->vexs[j]);
                    EnQueue(&Q,G->vexs[j]);
                    visited[j]=true;
                }
            }
        }
    }
}
