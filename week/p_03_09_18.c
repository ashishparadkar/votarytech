#include<stdio.h>
#include<string.h>
int helper(char *p,char *q,int size)
{
 int i,j;
 for(i=0,j=size;i<j;i++,j--)
 {
    if(p[i] != p[j]) return 0;
 }

 return 1;
}

int main()
{
 int i,j,ret=0;
 char buf[BUFSIZ],result[BUFSIZ];
 printf("Enter the string :\n");
 fgets(buf,BUFSIZ,stdin);
 buf[strlen(buf) -  1] = '\0';

 for(i = 0;buf[i];i++) {
	for(j=i+1;buf[j];j++) {
		ret = 0;
		ret = helper(buf + i,buf + j,j-i);
		if(ret == 1) {
			strncpy(result,buf + i,(j-i) + 1);
			result[j - i + 1] = '\0';
			printf("%s\n",result);
			result[0] = '\0';
		}
	}
 }
}
