#include<stdio.h>
int main()
{int i;

 char *arr[5]={0};
 
 printf("%u\n",sizeof(arr));

for(i=0;i<5;i++)
 printf("%x\n",arr[i]);

}
