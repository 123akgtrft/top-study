#include "stdio.h"
#include "string.h"
//字符串单词逆序并输出
void wordnixu(char *start,char *end);
char* setence(char *str);
int main()
{
	char str[100];
	printf("输入字符串:");
	gets(str);
	printf("%s\n",str);
	char* p=setence(str);
	int sign=0;
	for(int i=0;i<strlen(str);i++)
	{
		if(*(p+i)!=' '||(*(p+i+1)!=' '&&sign==1))
		{
			sign=1;
			printf("%c",*(p+i));
		}
	}
	return 0;
}
void wordnixu(char *start,char *end)//一个单词字符逆序，不包括空格字符
{
	char jiaohuan;
	while(start<end)
	{
		jiaohuan=*start;
		*start++=*end;
		*end--=jiaohuan;
	}
}
char* setence(char *str)//1、句子的单词先内部逆序/2、之后再把句子看做单词整体逆序即可得到逆序单词输出
{
	char *start=str;//指向串内部单词首字符
	char *p=str;//指向串的首地址，作为整体逆序的首地址
	while(*str!='\0')
	{
		if(*str==' ')
		{
			wordnixu(start,str-1);//串内单词内部逆序
			start=++str;//指向下一个单词的首地址,需要特别注意地址的操作++，与--
		}
		else
			str++;
	}
	wordnixu(start,str-1);//把最后一个单词逆序逆序
	wordnixu(p,str-1);//以整个串为单词逆序
	return p;//返回首地址
}