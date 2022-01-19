#include <stdio.h>

void kuaipai(int*,int,int);

int main(void)
{
    int num[]={2,5,24,34,6,45,7,65,75,675,7,6745,7,54,457,77};
    int len=sizeof(num)/sizeof(num[0]);
    kuaipai(num,0,len-1);
    for(int i=0;i<len;i++)
    printf(" %d ",num[i]);
    return 0;
}
void kuaipai(int* num,int kai,int end)
{
    if(kai>=end)
    return;
    int zhou=kai;
    int zhi=zhou+1;
    for(int i=kai+1;i<=end;i++)
    {
        if(num[i]<num[zhou])
        {
            int temp=num[i];
            num[i]=num[zhi];
            num[zhi]=temp;
            zhi++;
        }
    }
        int temp=num[zhi-1];
        num[zhi-1]=num[zhou];
        num[zhou]=temp;
        zhou=zhi-1;
        kuaipai(num,kai,zhou-1);
        kuaipai(num,zhou+1,end);

}