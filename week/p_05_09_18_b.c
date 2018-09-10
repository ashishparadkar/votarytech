#include<stdio.h>
#include<string.h>

int main()
{
char buf[BUFSIZ];
int i,cnt = 1;
char ch;
char *ptr = NULL;
printf("Enter a string :\n");
fgets(buf,BUFSIZ,stdin);
buf[strlen(buf) - 1] = '\0';

printf("enter char to remove:\n");
scanf("%c",&ch);

while((ptr = strchr(buf,ch)) != NULL) {
	memmove(ptr,ptr + 1,strlen(ptr + 1) + 1);
}

printf("%s\n",buf);
}
