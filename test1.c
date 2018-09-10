#include<stdio.h>
#include<string.h>
int main()
{
 char temp[100];
 char unsorted_arr[5][100] = {"Ashish","Abhi","Samruddhi","Nikhil","Rushikesh"};
 int i,j;
 for(i = 0; i < 5; i++)
	printf("%s\n",unsorted_arr[i]);
 for(i = 4;i >= 0;i--)
	for(j = 0;j < i; j++)
	{
		if(strcmp(unsorted_arr[j],unsorted_arr[j + 1]) > 0)
		{
			memcpy(temp,unsorted_arr[j],100);	
			memcpy(unsorted_arr[j],unsorted_arr[j + 1],100);	
			memcpy(unsorted_arr[j + 1],temp,100);	
		}
	}
 
 printf("After\n");
 for(i = 0; i < 5; i++)
	printf("%s\n",unsorted_arr[i]);
}
