#include<stdio.h>
#include<unistd.h>

int main()
{
 int count = 0;
 FILE *fp = NULL;
 fp = fopen("test.txt","a");
 fprintf(fp,"hi hello %d",count);

fclose(fp);
}
