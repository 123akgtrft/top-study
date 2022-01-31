#include <stdio.h>
#include <stdlib.h>

void merge(int*a,int start,int end,int start1,int end1);
void msort(int*a,int len);
void mergepass(int*a,int s,int len);

int main(void)
{
    int a[]={3,6,4,9,5,8,12,34,76,24,15,99,7,2,1,0},len=sizeof(a)/sizeof(a[0]);
    msort(a,len);
    for(int i=0;i<len;i++)
        printf("%d ",a[i]);
    return 0;
}
void msort(int*a,int len){
    int s=1;
    while(2*s<=len){
        mergepass(a,s,len);
        s*=2;
    }
    if(s<len){
        merge(a,0,s-1,s,len-1);
    }
}
void mergepass(int*a,int s,int len){
    int i,j;
    for(i=0,j=0;j<len/(2*s);j++,i+=2*s){
        merge(a,i,i+s-1,i+s,i+2*s-1);
    }
    // if(i+2*s<len){
    //     merge(a,i,i+s-1,i+s,len-1);
    // }
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