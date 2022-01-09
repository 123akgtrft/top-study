#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
};

void strbuf_init(struct strbuf *sb, size_t alloc);//缓存区初始化
size_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint);//读取文件(使用文件路径)
int strbuf_getline(struct strbuf *sb, FILE *fp);//从文件中读入一行
size_t strbuf_read(struct strbuf *sb, int fd, size_t hint);//读取文件(使用文件描述符)(注:因为我没有查到怎么看linux下文件的描述符，所以这个函数没有进行测试)

int main(void)
{
    struct strbuf sb;
    strbuf_init(&sb,10);
    char*filename="/home/kangning/Code/c/kmp.c";

    int len=strbuf_read_file(&sb,filename,BUFSIZ);
    printf("len = %d,sb->len = %d\n",len,sb.len);
    printf("sb->buf:\n%s",sb.buf);

    FILE*file=fopen(filename,"r");
    size_t len2=strbuf_getline(&sb,file);
    printf("len2 = %d\n",len2);
    printf("sb->len = %d\n",sb.len);
    fclose(file);
    
    free(sb.buf);
    return 0;
}


void strbuf_init(struct strbuf*sb,size_t alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(sizeof(char)*alloc);
}
size_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    FILE*file=fdopen(fd,"r");
    sb->buf=realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
    char*line=(char*)malloc(BUFSIZ);
    size_t len=0;
    int sign=0;

    while(sign=getline(&line,&len,file)!=EOF)
    {
        strcat(sb->buf,line);
        sb->len+=strlen(line);
    }
    fclose(file);
    file=NULL;
    free(line);
    return sb->len;
}
size_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint)
{
    sb->buf=realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
    FILE*file=fopen(path,"r");
    char*line=(char*)malloc(BUFSIZ);
    size_t len=0;
    int sign=0;

    while(sign=getline(&line,&len,file)!=EOF)
    {
        strcat(sb->buf,line);
        sb->len+=strlen(line);
    }
    fclose(file);
    file=NULL;
    free(line);
    return sb->len;
}
int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    size_t len=0;
    int sign=0;
    char*line=(char*)malloc(1000);
    if(sign=getline(&line,&len,fp))
    {
        len=strlen(line);
        sb->len+=len;
        if(sb->len>=sb->alloc){
            sb->alloc*=2;
            realloc(sb->buf,sb->alloc);
        }
        strcat(sb->buf,line);
    }
    free(line);
    return len;
}