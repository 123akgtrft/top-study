#include <stdio.h>
#include <stdarg.h>

int numbersum(int a,int b,...);

int main(void)
{
    int sum=numbersum(1,2,3,4,5,-99999);
    printf("sum = %d",sum);
    return 0;
}

int numbersum(int a,...)
{
    va_list p;
    int sum=a;
    va_start(p,a);
    int value=0;
    while((value=va_arg(p,int))!=-99999)
    sum+=value;
    va_end(p);
    return sum;
}