#include<stdio.h>
#include<stdlib.h>
int main()
{
 void *buffer = NULL;
 int i;
 char *arr[5] = {0};
 char *ptr = "OPTEE\n";
 for(i = 0; i < 5; i++) {
	arr[i] = (char *)malloc(20);
	fgets(arr[i],20,stdin);
 }

 for(i = 0; i < 5; i++) {
	printf("%s\n",arr[i]);
 }

 
 buffer = arr;
 *((char **)buffer + 2) = ptr;
 
 for(i = 0; i < 5; i++) {
	 printf("%s\n",(char *)(*((char **)buffer + i)));
 }

 
}
