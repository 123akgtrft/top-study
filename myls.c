#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

#define PARAM_NONE 0	//无参数
#define PARAM_A 1		//有参数a
#define PARAM_L 2		//有参数l
#define PARAM_U 4		//有参数u
#define PARAM_R 8		//有参数R
#define MAX 128

int cmp(const void*,const void*);
int cmp1(const void*,const void*);
int get_param(int argc, char *argv[]);
void ls_do(const char*,int);
void display_l(struct stat*,const char*);// -l

int main(int argc,char**argv)
{
    int mode=get_param(argc,argv);
    char*path=(char*)malloc(sizeof(char)*MAX);
    strcpy(path,"");
    if(argc==1||*(argv+1)[0]=='-'){//"ls"
        ls_do(".",mode);
    }else{
        ls_do(*(argv+1),mode);
    }
    free(path);
    return 0;
}
int cmp(const void*a,const void*b){
    char**a1=(char**)a;
    char**b1=(char**)b;
    return strcmp(*a1,*b1);
}
int cmp1(const void*a,const void*b){
    char**a1=(char**)a;
    char**b1=(char**)b;
    return -1*strcmp(*a1,*b1);
}
int get_param(int argc,char**argv){
    int param=PARAM_NONE,ar=0;
    while(++ar<argc&&argv[ar][0]!='-');
    for(int i=1;ar<argc&&i<strlen(argv[ar]);i++){
        switch(argv[ar][i])
        {
            case 'a':param|=PARAM_A;break;
            case 'l':param|=PARAM_L;break;
            case 'u':param|=PARAM_U;break;
            case 'R':param|=PARAM_R;break;
        }
    }
    return param;
}
void display_err(const char *err_string,int line)
{
    fprintf(stderr, "line: %d ", line);
    perror(err_string);
    exit(1);
}
void display_l(struct stat*sta,const char*name){
    DIR*dir;
    mode_t mode_file=sta->st_mode;
    if(S_ISLNK(mode_file))printf("l");
    else if(S_ISREG(mode_file))printf("-");
    else if(S_ISDIR(mode_file))printf("d");
    else if(S_ISCHR(mode_file))printf("c");
    else if(S_ISBLK(mode_file))printf("b");
    else if(S_ISFIFO(mode_file))printf("f");
    else if(S_ISSOCK(mode_file))printf("s");

    if(S_IRUSR & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWUSR & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISUID & mode_file){
        if(S_IXOTH & mode_file)
            printf("s");
        else printf("S");
    }else if(S_IXUSR & mode_file){
        printf("x");
    }else printf("-");

    if(S_IRGRP & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWGRP & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISGID & mode_file){
        if(S_IXOTH & mode_file)
            printf("s");
        else printf("S");
    }else if(S_IXGRP & mode_file){
        printf("x");
    }else printf("-");

    if(S_IROTH & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWOTH & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISVTX & mode_file){
        printf("T");
    }else if(S_IXOTH & mode_file){
        printf("x");
    }else printf("-");

    printf("%2ld",sta->st_nlink);
    printf("%4s",getpwuid(sta->st_uid)->pw_name);
    printf("%4s",getgrgid(sta->st_gid)->gr_name);
    printf("%6ld",sta->st_size);

    char time[32];
    strcpy(time,ctime(&sta->st_mtime));//is mtime not atime
    time[strlen(time)-1]='\0';
    printf(" %.12s",time+4);
    printf(" %s\n",name);
}
void ls_do(const char*path,int mode){
    DIR*dir_fd;
    struct dirent*dir;
    struct stat sta;
    int total;
    char**file_name=(char**)malloc(sizeof(char*)*MAX);
    int count=0;
    if((dir_fd=opendir(path))==NULL){
        display_err("opendir",__LINE__);
    }
    while((dir=readdir(dir_fd))!=NULL){
        if((dir->d_name)[0]=='.'&&(mode&PARAM_A)==0)continue;
        if(count%MAX==0&&count){
            if(file_name=realloc(file_name,sizeof(char*)*(count/MAX+1)*MAX))
                display_err("realloc",__LINE__);
        }
        file_name[count]=malloc(sizeof(char)*MAX);
        strcpy(file_name[count],dir->d_name);
        char*path_full=(char*)malloc(sizeof(char)*MAX);
        sprintf(path_full,"%s/%s",path,file_name[count]);
        if(stat(path_full,&sta)==-1){
            display_err(path,__LINE__);
        }
        //total+=sta.st_blksize;
        //total+=(sta.st_blocks-1)/4096+1;
        total+=sta.st_blocks/4096;
        free(path_full);
        count++;
    }
   // if(mode & PARAM_L)printf("总用量 %d\n",total);

    if(mode & PARAM_U)qsort(file_name,count,sizeof(file_name[0]),cmp1);
    else qsort(file_name,count,sizeof(file_name[0]),cmp);

    for(int i=0;i<count;i++){
        char*path_full=(char*)malloc(sizeof(char)*MAX);
        sprintf(path_full,"%s/%s",path,file_name[i]);
        //printf("\n%s\n",path_full);
        if(stat(path_full,&sta)==-1){
            display_err(path,__LINE__);
        }

        if((mode & PARAM_R)&&S_ISDIR(sta.st_mode)){
            printf("\n%s:\n",path_full);
            ls_do(path_full,mode);
        }
        free(path_full);
        if(mode & PARAM_L)display_l(&sta,file_name[i]);
        // if(mode & PARAM_NONE)
        //     printf("%s  ",file_name[i]);
        if(!(mode & PARAM_L))printf("%s  ",file_name[i]);
        free(file_name[i]);
    }
    if(!(mode & PARAM_L))printf("\b\b");
    free(file_name);
}
