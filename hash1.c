#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 12
#define NULLKEY -32768
typedef struct
{
    int**elem;
    int*count;
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
    int keys[]={12,67,56,16,25,37,22,29,15,47,48,34,11,13,26,35};
    int searchkey=16,addr;
    for(int i=0;i<m;i++)
        HashInsert(&H,keys[i]);
    int result=HashSearch(H,searchkey,&addr);
    if(result==0)
        printf("散列表中没有%d\n",searchkey);
    else
         printf("它的位置是%d\n",addr);
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<H.count[i];j++){
    //         printf("H->elem[%d][%d] = %d  ",i,j,H.elem[i][j]);
    //     }printf("\n");
    // }
    return 0;
}

void HashInit(Hash*H){
    m=HASHSIZE;
    H->count=(int*)malloc(sizeof(int)*m);
    H->elem=(int**)malloc(sizeof(int*)*m);
    for(int i=0;i<m;i++)
    {
        H->count[i]=0;
        H->elem[i]=malloc(sizeof(int));
    }
}
int HashCome(int key){
    return key%m;
}
void HashInsert(Hash*H,int key){
    int addr=HashCome(key);
    if(H->count[addr]>=1){
        H->count[addr]++;
        H->elem[addr]=realloc(H->elem[addr],H->count[addr]*sizeof(int));
        H->elem[addr][H->count[addr]-1]=key;
    }
    else{
        H->elem[addr][H->count[addr]++]=key;
    }
}
int HashSearch(Hash H,int key,int*addr){
    *addr=HashCome(key);
    for(int i=0;i<H.count[*addr];i++)
    {
        if(H.elem[*addr][i]==key)
        return 1;
    }
    return 0;
}