#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};

void strbuf_init(struct strbuf *sb, size_t alloc);//缓存区初始化
void strbuf_attach(struct strbuf *sb, void *str, size_t len);//字符串存入缓冲区
void strbuf_release(struct strbuf *sb);//释放这个缓冲区
void strbuf_swap(struct strbuf *a, struct strbuf *b);//交换两个缓冲区的内容
char *strbuf_detach(struct strbuf *sb, size_t *sz);//找出这个缓冲区的内容和大小
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);//比较两个缓冲区的大小
void strbuf_reset(struct strbuf *sb);//清空这个缓冲区

int main(void)
{
    struct strbuf sb;
    struct strbuf ss;
    strbuf_init(&ss,10);
    strbuf_attach(&ss,"xiyou",5);
    // strbuf_init(&sb,10);
    strbuf_attach(&ss,"linux",5);
    // strbuf_swap(&ss,&sb);
    // int len;
    // char*cc=strbuf_detach(&ss,&len);
    // printf("cc=%s\n",ss.buf);
    // printf("len=%d\n",len);
    // printf("cmp=%d\n",strbuf_cmp(&ss,&sb));
    // strbuf_reset(&ss);
    // strbuf_reset(&sb);
    printf("ss=%s",ss.buf);
    strbuf_release(&ss);
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
void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    int max=a->len>b->len?a->len:b->len;
    int templ=a->len;
    a->len=b->len;
    b->len=templ;
    if(a->alloc<=max){
        a->alloc*=2;
        a->buf=(char*)realloc(a->buf,sizeof(char)*a->alloc);
    }
    if(b->alloc<=max)
    {
        b->alloc*=2;
        b->buf=(char*)realloc(b->buf,sizeof(char)*b->alloc);
    }
    char*temp=(char*)malloc(sizeof(char)*max);
    strcpy(temp,a->buf);
    strcpy(a->buf,b->buf);
    strcpy(b->buf,temp);
}
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    *sz=sb->len;
    return sb->buf;
}
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    return first->alloc-second->alloc;
}
void strbuf_reset(struct strbuf *sb)
{
    strcpy(sb->buf,"");
}