#include <stdio.h>
#include <stdlib.h>

#define  MAX 100
#define SMAX 10
typedef char ElemType;

typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqStack;

void initStack(SqStack *s){
    s->base=(ElemType*)malloc(sizeof(ElemType));
    if(!s->base)
    {
        exit(0);
    }
    s->top=s->base;
    s->stackSize=MAX;
}
void push(SqStack *s,ElemType e){
    if(s->top-s->base>=s->stackSize)
    {//扩展栈内存
        s->base=(ElemType*)realloc(s->base,(s->stackSize+SMAX)*sizeof(ElemType));
        if(!s->base)
        {
            exit(0);
        }
        s->stackSize=s->stackSize+SMAX;
        s->top=s->base+s->stackSize;
    }
    *(s->top)=e;
    s->top++;
}
void pop(SqStack *s,ElemType *e)
{
    if(s->base==s->top)
        return;
    *e=*(--(s->top));
}
int Len(SqStack s) {
	return (s.top - s.base);
}

int main(void)
{
    char c,e;
    SqStack s;
    initStack(&s);
	scanf("%c", &c);
    while(c!='#')
    {
        while(c>='a'&&c<='z')
        {
            printf("%c",c);//output 1-number
            scanf("%c",&c);
            if(c<'0'||c>'9')
            {
                printf("");
            }
        }
        if(c==')')
        {
            pop(&s,&e);
            while(e!='(')
            {
                printf("%c",e);//output 3-括号内符号全部输出
                pop(&s,&e);
            }
        }
        else if(c=='+'||c=='-')
        {
           if(!Len(s))
            push(&s,c);
            else{
                do{
                        pop(&s,&e);
                        if(e=='(')
                        {
                            push(&s,e);
                        }
                        else
                        printf("%c",e);//output 2-部分符号全部输出
                    }while(Len(s)&&e!='(');
                push(&s,c);
                }
        }
        else if(c=='*'||c=='/'||c=='('){
            push(&s,c);
        }
        else if(c=='#'){
             break;
        }
        else{
            printf("输入出错");
            return -1;
        }
        scanf("%c",&c);
    }
    while(Len(s))
    {
        pop(&s,&e);
        printf("%c",e);
    }
    return 0;
}