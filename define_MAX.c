#include <stdio.h>

#define MAX(m1,m2)({\
    typeof(m1) __m1__ =m1;\
    typeof(m2) __m2__ =m2;\
    (&__m1__==&__m2__);\
    __m1__>__m2__?__m1__:__m2__;\
})


int main()
{
    char a='a',b='b';
    int c=100;
    printf("max of %d and %d is %d \n",a,b,MAX(a,b));
    return 0;
}

