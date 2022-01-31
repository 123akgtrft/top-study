#include <stdio.h>
#include <stdlib.h>

void HeapSort(int*L,int len);
void HeapAdjust(int*L,int head,int tail);
void swap(int*L,int a,int b);

int main(void)
{
    int a[]={2,5,3,8,4,7,9,6,1},len=sizeof(a)/sizeof(int);
    HeapSort(a,len);
    for(int i=0;i<len;i++)
        printf("%d ",a[i]);
    return 0;
}
void HeapAdjust(int*L,int head,int tail){
    int temp=L[head],i;
    for(i=2*head+1;i<=tail;i=2*i+1){//a[i]初始每次都是左支
        if(i<tail&&L[i]<L[i+1])
            i++;
        if(L[i]<=temp)
            break;
        L[head]=L[i];
        head=i;
    }
    L[head]=temp;
}
void swap(int*L,int a,int b){
    int temp=L[a];
    L[a]=L[b];
    L[b]=temp;
}
void HeapSort(int*L,int len){
    int i;
    for(i=len/2-1;i>=0;i--)
        HeapAdjust(L,i,len-1);//构建大顶堆
    for(i=len-1;i>0;i--){
        swap(L,0,i);
        HeapAdjust(L,0,i-1);
    }
}