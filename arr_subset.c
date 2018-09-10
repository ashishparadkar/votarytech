#include<stdio.h>
int main(int argc,char **argv)
{
	int i,j;
	int cnt=4,sz1,sz2;
	int arr1[6]={10,5,2,23,19};
	int arr2[4]={19,5,3};
	sz1 = sizeof(arr1)/sizeof(arr1[0]);
	sz2 = sizeof(arr2)/sizeof(arr2[0]);
	printf("sz1=%d\tsz2=%d\n",sz1,sz2);
	for(i = 0; i < sz2; i++)
	{
		for(j = 0;j < sz1; j++)
		{
			if(arr2[i] == arr1[j])
				cnt--;
		}
	}

	if(cnt == 0)
		printf("yes\n");
	else
		printf("no\n");
}
