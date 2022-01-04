#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};

void strbuf_init(struct strbuf *sb, size_t alloc);//缓存区初始化
void strbuf_attach(struct strbuf *sb, void *str, size_t len);//字符串存入缓冲区
struct strbuf* strbuf_split_buf(const char *str, size_t len, char terminator, int max,int*returnSIze);
//字符串分割,returnSize表示分割出的个数,max表示最多分出多少个
bool strbuf_is(struct strbuf *sb,char*s);//判断该缓存区是否由指定字符串开头
char* strbuf_copy_part(struct strbuf*sb,int begin,int end);//拷贝缓冲区一段字符串
void strbuf_release(struct strbuf *sb);//释放这个缓冲区

int main(void)
{
    struct strbuf sb;
    strbuf_init(&sb,10);
    strbuf_attach(&sb,"chenchen lovely",15);
    int returnSize;
    bool a=strbuf_is(&sb,"chen");
    if(a==true)
    printf("Yes,it is start with chen\n");
    else
    printf("No,it don't start with chen\n");
    struct strbuf* result=strbuf_split_buf("aaa,sss,ddd,fff,ggg",19,',',5,&returnSize);
    for(int i=0;i<returnSize;i++)
    printf("第%d个%s\n",i+1,result[i].buf);
    char*b=strbuf_copy_part(&sb,4,13);
    printf("strbuf_copy_part的结果是%s\n",b);
    strbuf_release(&sb);
    return 0;
}

void strbuf_init(struct strbuf*sb,size_t alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(sizeof(char)*alloc);
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len)
{
    while(sb->len+len>sb->alloc){
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc)*2);
    }
    sb->len+=len;
    strcat(sb->buf,str);
}
struct strbuf *strbuf_split_buf(const char *str, size_t len, char terminator, int max,int*returnSize)
{
    struct strbuf*ans=(struct strbuf*)malloc(sizeof(struct strbuf)*max);
    int i=0,j=0,w;
    *returnSize=0;
    char temp[100];
    while(i<len)
    {
        w=0;
        while(str[i]!=terminator&&i<len)
        {
            temp[w++]=str[i++];
        }
        temp[w]='\0';
        ans[j].buf=(char*)malloc(sizeof(char)*(w+1));
        strcpy(ans[j].buf,temp);
        i++;
        j++;
        if(j>=max)
        break;
    }
    *returnSize=j;
    return ans;
}
bool strbuf_is(struct strbuf *sb,char*s)
{
    int i=0,len=strlen(s);
    while(i<len)
    {
        if(sb->buf[i]!=s[i])
        return false;
        i++;
    }
    return true;
}
char* strbuf_copy_part(struct strbuf*sb,int begin,int end)
{
    int i,count=0;
    char*copy=(char*)malloc(sizeof(char)*(end-begin));
    for(i=begin;i<end;i++)
    copy[count++]=sb->buf[i];
    return copy;
}


void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}
