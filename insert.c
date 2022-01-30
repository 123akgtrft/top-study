#include <stdio.h>

void InsertSort(int*a,int len);

int main(void)
{
    int a[]={2,9,3,7,4,6,0,1},len=sizeof(a)/sizeof(int);
    InsertSort(a,len);
    for(int i=0;i<len;i++)
    printf("%d ",a[i]);
    return 0;
}
void InsertSort(int*a,int len){
    int count=0,i,j,temp;
    while(count<len){
        for(i=0;i<=count;i++){
            if(a[count+1]<a[i]){
                temp=a[count+1];
                for(j=count;j>=i;j--){
                    a[j+1]=a[j];
                }
                a[i]=temp;
            }
        }
        count++;
    }
}