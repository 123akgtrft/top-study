#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node Node;
struct Node
{
    int value;
    Node *left;
    Node *right;
    int lsign;
    int rsign;
};

Node* pre=NULL;

Node* create();//创建根节点(按照原顺序)
void Threading(Node* root);//线索化(以中序线索化为例)
void list(Node* root);//遍历方式
void ThreadingList(Node*head);//线索化遍历
void freeNode(Node*root);//释放内存
 
int main(void)
{
     int n=0;
    Node*root=NULL;
    root=create();
    pre=root;
    Threading(root);
    //list(root);
    ThreadingList(root);
    freeNode(root);
    return 0;
}
 

Node* create()
{
    int n;
    Node* root=NULL;
    printf("Input the value(quit when you input -1):");
    scanf("%d",&n);
    if(n==-1)
    return root;
    else{
        root=(Node*)malloc(sizeof(Node));
        root->value=n;
        root->lsign=0;
        root->rsign=0;
        root->left=create();
        root->right=create();
        return root;
    }
}

void Threading(Node* root)
{//以中序线索化为例
    if(root)
    {
        Threading(root->left);
        if(!root->left)
        {
            root->lsign=1;
            root->left=pre;
        }
        if(!pre->right)
        {
            pre->right=root;
            pre->rsign=1;
        }
        pre=root;
        Threading(root->right);
    }
}

void list(Node* root)
{//中序遍历(前序，后序与此类似)
    if(!root)
    return;
    list(root->left);
    printf("%d ",root->value);
    
    list(root->right);
}

void ThreadingList(Node* root)
{
    Node*p=root;
    while(p!=NULL)
    {
        while(p->lsign==0)
            p=p->left;
        printf("%d ",p->value);
        while(p->rsign==1)
        {
            p=p->right;
            printf("%d ",p->value);
        }
        p=p->right;
    }
}

void freeNode(Node*root)
{
    if(root!=NULL)
    {   
        if(root->lsign==0)//不通过前驱和后继
        freeNode(root->left);
        if(root->rsign==0)//不通过前驱和后继
        freeNode(root->right);
        free(root);
        root=NULL;
    }
}