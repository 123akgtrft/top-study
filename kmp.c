#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void GetNext(char* p,int next[]) ;
int KmpSearch(char* s, char* p,int* next)  ;

int main(void)
{
    char* zi="abaabab";
    char* fu="aababaabab";
    int* next=(int*)malloc(sizeof(int)*strlen(zi));
    GetNext(zi,next);
    int a=KmpSearch(fu,zi,next);
    printf("%d",a);
    return 0;
}
int KmpSearch(char* ss, char* p,int* next)
{
    int i = 0;
    int j = 0,a;
    int sign=0,result=1,lens=strlen(ss),lenp=strlen(p);
    char s[10000];
    for(int q=0;q<lens;q++)
        s[q]=ss[q];
    for(a=1;(a-1)*lens<=lenp+lens;a++)
    {
        i=0,j=0;
        for(int w=0;w<lens;w++)
        {
            s[(a-1)*lens+w]=ss[w];
        }
        while (i < a*lens && j < lenp)
        {
            if(a*lens<lenp)
                break;
            if (j == -1 || p[j] == s[i])
            {
                i++;
                j++;
            }
            else
            {
                j = next[j];
            }
        }
        if (j == lenp)
            return a;
    }
    return -1;
    // int i = 0;
    // int j = 0;
    // int sLen = strlen(s);
    // int pLen = strlen(p);
    // while (i < sLen && j < pLen)
    // {
    //     //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
    //     if (j == -1 || s[i] == p[j])
    //     {
    //         i++;
    //         j++;
    //     }
    //     else
    //     {
    //         //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
    //         //next[j]即为j所对应的next值
    //         j = next[j];
    //     }
    // }
    // if (j == pLen)
    //     return i - j;
    // else
    //     return -1;

}
void GetNext(char* p,int next[])
{
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    for(int i=0;i<pLen;i++)
        printf("%d ",next[i]);
}
