#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data data;
struct data
{
    int value;
    data* pnext;
    data* plast;
};

data* create(int n);
data* swapPairs(data* head);


int main(void)
{
    data*head=create(6);
    swapPairs(head);
    return 0;
}
data* create(int n)
{
    data *head=NULL,*p=NULL,*l=NULL;
    for(int i=0;i<=n;i++)
    {
        if(i==0){
            p=(data*)malloc(sizeof(data));
            head=p;
            head->plast=NULL;
        }
        else{
            p=(data*)malloc(sizeof(data));
            l->pnext=p;
            p->plast=l;
            printf("输入第%d个数:",i);
            scanf("%d",&p->value);
        }
        l=p;
        p->pnext=NULL;
    }
    return head;
}
data* swapPairs(data* head){
    /*
    假设链表数据为1,2,3,4,5,6
    注释掉的内容为自己第一次写错的
    */
    // data*temp,*note1,*note2;
    // temp=head;
    // head=head->pnext;
    data ya;//定义一个哑节点
    ya.pnext=head;
    data*temp,*note1,*note2;
    temp=&ya;//ya.next会随着temp->next的改变而改变，ya.next指向2
    while(temp->pnext!=NULL&&temp->pnext->pnext!=NULL)
    {
        note1=temp->pnext;
        note2=temp->pnext->pnext;
        temp->pnext=note2;
        note1->pnext=note2->pnext;//如果按照注释里的写法，temp为1,hand为2，此时note1与hand重合，因此hand->next被改成了5
        note2->pnext=note1;
        temp=note1;
    }
    return head;
}
