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
void strbuf_grow(struct strbuf *sb, size_t extra);
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
void strbuf_addch(struct strbuf *sb, char c);
void strbuf_addstr(struct strbuf *sb, const char *s);	
void strbuf_addbuf(struct strbuf *sb, struct strbuf *sb2);
static inline void strbuf_setlen(struct strbuf *sb, size_t len);	
static inline size_t strbuf_avail(const struct strbuf *sb);
void strbuf_insert(struct strbuf *sb, size_t pos, void *data, size_t len);
void strbuf_rtrim(struct strbuf *sb);
void strbuf_ltrim(struct strbuf *sb);
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len);
void strbuf_release(struct strbuf *sb);//释放这个缓冲区

int main(void)
{
    struct strbuf sb;
    struct strbuf ss;
    strbuf_init(&sb,10);
    strbuf_init(&ss,10);
    strbuf_attach(&sb,"    xiyou",9);
    strbuf_attach(&ss,"lalala          ",16);
    strbuf_add(&sb,"linux     ",10);
    strbuf_addstr(&sb," kangning       ");
    
    strbuf_addbuf(&sb,&ss);
    int len=strbuf_avail(&ss);
    printf("len=%d\n",len);
    printf("sb = %s\n",sb.buf);
    
    strbuf_insert(&sb,4," haha ",6);
    strbuf_ltrim(&sb);
    strbuf_rtrim(&sb);
    strbuf_remove(&sb,5,9);
    printf("result=%s",sb.buf);
    strbuf_release(&sb);
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
    sb->len+=len;
    while(sb->len>sb->alloc){
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    }
    strcat(sb->buf,str);
}
void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    sb->len+=extra;
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    sb->len+=len;
    if(sb->len>=sb->alloc)
    {
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    }
    strcat(sb->buf,data);
}
void strbuf_addch(struct strbuf *sb, char c)
{
    sb->len+=1;
    if(sb->len>=sb->alloc)
    {
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    }
    strcat(sb->buf,c);
}
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    sb->len+=strlen(s);
    if(sb->len>=sb->alloc)
    {
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    }
    strcat(sb->buf,s);
}
void strbuf_addbuf(struct strbuf *sb, struct strbuf *sb2)
{
    sb->len+=sb2->len;
    if(sb->len>=sb->alloc)
    {
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    }
    strcat(sb->buf,sb2->buf);
}
static inline void strbuf_setlen(struct strbuf *sb, size_t len)
{
    sb->len=len;
}
static inline size_t strbuf_avail(const struct strbuf *sb)
{
    return sb->alloc-sb->len;
}
void strbuf_insert(struct strbuf *sb, size_t pos,void *data, size_t len)
{
    sb->len+=len;
    if(sb->len>=sb->alloc)
    {
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
    }
    char*temp=(char*)malloc(sizeof(char)*(sb->len));
    int i=0;
    strncpy(temp,sb->buf,pos);
    strcat(temp,data);
    strcat(temp,sb->buf+pos);
    strcpy(sb->buf,temp);
}
void strbuf_ltrim(struct strbuf *sb)
{
    int count=0;
    while(sb->buf[count]==' ')
    {
        count++;
        (sb->len)--;
    }
    char*temp=(char*)malloc(sizeof(char)*sb->len);
    strcpy(temp,sb->buf+count);
    strcpy(sb->buf,temp);
}
void strbuf_rtrim(struct strbuf *sb)
{
    int count=sb->len-1;
    while(sb->buf[count]==' ')
    {
        count--;
        (sb->len)--;
    }
    char*temp=(char*)malloc(sizeof(char)*(count+1));
    strncpy(temp,sb->buf,count+1);
    strcpy(sb->buf,temp);
}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    char*temp=(char*)malloc(sizeof(char)*(sb->len-len));
    strncpy(temp,sb->buf,pos);
    strcat(temp,sb->buf+pos+len);
    strcpy(sb->buf,temp);
}

