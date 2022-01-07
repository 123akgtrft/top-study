#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
邻接表创建图，深度优先遍历，广度优先遍历
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
    char data;//顶点域，存储顶点信息
    EdgeNode*firstedge;//边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct//表示整个图
{
    AdjList adjlist;
    int numVertexes,numEdges;//图中当前节点数和边数
}GraphAdjList;

typedef struct
{
    int data[MAXVEX];
    int front;
    int rear;
}Queue;

void CreateALGraph(GraphAdjList*G);//邻接表创建图
void DFS(GraphAdjList G,int i);//邻接表深度优先遍历递归算法
void DFSTraverse(GraphAdjList G);//邻接表的深度遍历操作
void InitQueue(Queue*Q);//初始化队列
void EnQueue(Queue*Q,int i);//入队列
void DeQueue(Queue*Q,int*i);//出队列，并将其值赋给i
bool QueueEmpty(Queue Q);//检查队列是否为空
void BFSTraverse(GraphAdjList*G);//邻接矩阵的广度优先遍历

int main(void)
{
    GraphAdjList G;
    CreateALGraph(&G);
    printf("深度优先遍历:\n");
    DFSTraverse(G);
    printf("\n广度优先遍历:\n");
    BFSTraverse(&G);
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
        e2=(EdgeNode*)malloc(sizeof(EdgeNode));
        e2->adjvex=i;
        e2->next=G->adjlist[j].firstedge;
        G->adjlist[j].firstedge=e2;
    }
}
void DFS(GraphAdjList G,int i)
{
    int w;
    EdgeNode*p;
    visited[i]=true;
    printf("%c\t",G.adjlist[i].data);
    p=G.adjlist[i].firstedge;
    while(p!=NULL)
    {
        w=p->adjvex;
        if(!visited[w])
            DFS(G,w);
        p=p->next;
    }
}
void DFSTraverse(GraphAdjList G)
{
    int i;
    for(i=0;i<G.numVertexes;i++)
        visited[i]=false;
    for(i=0;i<G.numVertexes;i++)
    if(visited[i]==false)
        DFS(G,i);
}
void InitQueue(Queue*Q)
{
    Q->rear=0;
    Q->front=0;
}
void EnQueue(Queue*Q,int i)
{
    if((Q->rear)+1%MAXVEX==Q->front){
        printf("队列已满");
        return;
    }
    Q->data[Q->rear]=i;
    Q->rear=(Q->rear+1)%MAXVEX;
}
void DeQueue(Queue*Q,int*i)
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
void BFSTraverse(GraphAdjList*G)
{
    int i;
    Queue Q;
    EdgeNode*p;
    InitQueue(&Q);
    for(i=0;i<G->numVertexes;i++)
    visited[i]=false;

    for(i=0;i<G->numVertexes;i++)//每次从一个边表节点开始遍历
    {
        if(visited[i]==false)
        {
            printf("%c\t",G->adjlist[i].data);
            EnQueue(&Q,i);
            visited[i]=true;
            while(!QueueEmpty(Q))//当队列为空时，循环终止
            {
                DeQueue(&Q,&i);
                p=G->adjlist[i].firstedge;
                while(p)
                {
                    if(visited[p->adjvex]==false)
                    {
                        printf("%c\t",G->adjlist[p->adjvex].data);
                        EnQueue(&Q,p->adjvex);
                        visited[p->adjvex]=true;
                    }
                    p=p->next;
                }
            }
        }
    }
    
}
