#include <stdio.h>

int FibonacciSearch(int*a,int n,int key);

int main(void)
{
    int a[30]={1,2,3,4,5,7,9,12,13,14,16,22,24,26,28,34},key=22;
    int result=FibonacciSearch(a,15,key);//15是数组内元素数减1
    printf("%d",result);
    return 0;
}

int FibonacciSearch(int*a,int n,int key)
{
    int low,high,mid,i,k;
    int F[20];
    F[0]=0;
    F[1]=1;
    for(i=2;i<20;i++)
    F[i]=F[i-1]+F[i-2];
    low=1;
    high=n;
    k=0;
    while(n>F[k]-1)
    k++;
    for(i=n;i<F[k]-1;i++)
    a[i]=a[n];

    while(low<=high)
    {
        mid=low+F[k-1]-1;
        if(key<a[mid])
        {
            high=mid-1;
            k-=1;
        }
        else if(key>a[mid])
        {
            low=mid+1;
            k-=2;
        }
        else
        {
            if(mid<=n)
                return mid;
            else
                return n;
        }
    }
    return 0;
}