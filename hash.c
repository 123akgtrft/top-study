#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 12
#define NULLKEY -32768
typedef struct
{
    int*elem;
    int count;
}Hash;
int m=0;

void HashInit(Hash*H);
int HashCome(int key);
void HashInsert(Hash*H,int key);
int HashSearch(Hash H,int key,int*addr);//addr为key的Hash地址

int main(void)
{
    Hash H;
    HashInit(&H);
    int keys[12]={12,67,56,16,25,37,22,29,15,47,48,34};
    int searchkey=16,addr;
    for(int i=0;i<m;i++)
        HashInsert(&H,keys[i]);
    int result=HashSearch(H,searchkey,&addr);
    if(result==0)
        printf("散列表中没有%d\n",searchkey);
    else
        printf("它的位置是%d\n",addr);
    for(int i=0;i<m;i++)
        printf("H->elem[%d] = %d\n",i,H.elem[i]);
    return 0;
}

void HashInit(Hash*H){
    m=HASHSIZE;
    H->count=m;
    H->elem=(int*)malloc(sizeof(int)*m);
    for(int i=0;i<m;i++)
    {
        H->elem[i]=NULLKEY;
    }
}
int HashCome(int key){
    return key%m;
}
void HashInsert(Hash*H,int key){
    int addr=HashCome(key);
    while(H->elem[addr]!=NULLKEY){
        addr=(addr+1)%m;
    if(addr==HashCome(key))
        return;
    }
    H->elem[addr]=key;
}
int HashSearch(Hash H,int key,int*addr){
    *addr=HashCome(key);
    while(H.elem[*addr]!=key){
        *addr=(*addr+1)%m;
        if(*addr==HashCome(key))
            return 0;
    }
    return 1;
}