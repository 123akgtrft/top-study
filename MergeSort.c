#include <stdio.h>
#include <stdlib.h>

void msort(int*a,int start,int end);
void merge(int*a,int start,int end,int start1,int end1);

int main(void)
{
    int a[]={3,6,4,9,5,8,7,2,1,0},len=sizeof(a)/sizeof(a[0]);
    msort(a,0,len-1);
    for(int i=0;i<len;i++)
        printf("%d ",a[i]);
    return 0;
}
void msort(int*a,int start,int end){
    if(start<end){
        int mid=(start+end)/2;
        int*b=a+(mid-start+1);
        msort(a,start,mid);
        msort(a,mid+1,end);
        merge(a,start,mid,mid+1,end);
    }
}
void merge(int*a,int start,int end,int start1,int end1){
    int i,j,count=0;
    int*temp=(int*)malloc(sizeof(int)*(end1-start+1));
    for(i=start,j=start1;i<=end&&j<=end1;){
        if(a[i]<=a[j]){
            temp[count++]=a[i++];
        }
        else{
            temp[count++]=a[j++];
        }
    }
    if(i>end){
        while(j<=end1)
            temp[count++]=a[j++];
    }
    if(j>end){
        while(i<=end)
            temp[count++]=a[i++];
    }
    for(i=0,j=start;i<count;i++,j++)
    a[j]=temp[i];
}