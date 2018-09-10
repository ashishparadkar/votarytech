#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
int findMax(int **arr,int m,int n);
int max;
int k=3,cnt=0;

void printSum(int **arr,int r,int c)
{
	int i,j,p,dia1=0,dia2=0;

	int sum = 0;
	if (k > c) return;


	for (int i=0; i<r; i++)
	{
		// column of first cell in current sub-square of size k x k
		for (int j=0; j<c; j++)
		{
			// Calculate and print sum of current sub-square
			for (int p=0; p<k; p++){
				for (int q=0; q<k; q++){
					sum += arr[p+i][q+j];
				}
			}
			printf("sum is %d \n",sum);
			sum=0;
			j=j+2;
		}
		i=i+2;
		puts("****************************");
	}


}

int main()
{
	int **b,r,c,i,j,y,mod,old_r,old_c;\
int d1=0,d2=0,rem = 0;
	//freopen("/home/patilkam/1028/input.txt","r",stdin);

		printf("Enter the number of rows in the matrix\n");
	scanf("%d",&r);
	printf("Enter the number of columns in the matrix\n");
	scanf("%d",&c);
	printf("Enter the elements in the matrix\n");


	//	int arr[6][6]={1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};
	b=malloc(sizeof(int*)*r);
	for(i=0;i<r;i++)
	{
		b[i]=malloc(sizeof(int)*c);
		for(j=0;j<c;j++)
		{
			scanf("%d",&b[i][j]);
		}
	}

	old_r=r;
	old_c=c;

	if(r%3!=0)
	{
		rem=r%3;
		r=r+(3-rem);
	}
	rem = 0;
	if(c%3!=0)
	{
		rem=c%3;
		c=c+(3-rem);
	}
	printf("old_r = %d, r = %d, old_c = %d, c = %d\n",old_r,r,old_c,c);
	if(old_r==r&&old_c==c)
		goto l1;

	else if(old_r!=r&&old_c!=c)
	{
		b=realloc(b,sizeof(int*)*r);
		for(i=0;i<r;i++)
		{
			b[i]=realloc(b[i],sizeof(int)*c);
		}

		for(i=0;i<old_r;i++)
			for(j=old_c;j<c;j++)
				b[i][j]=1;


		for(i=old_r;j<r;i++)
			for(j=0;j<c;j++)
				b[i][j]=1;

	}

	else if(old_r==r&&old_c!=c)
	{
		for(i=0;i<r;i++)
		{
			b[i]=realloc(b[i],sizeof(int)*c);
		}

		for(i=0;i<old_r;i++)
			for(j=old_c;j<c;j++)
				b[i][j]=1;
	}

	else if(old_c==c&&old_r!=r)
	{
		b=realloc(b,sizeof(int *) * r);
		for(i=old_r;i<r;i++)
		{
			b[i]=malloc(sizeof(int)*c);
		}
		for(i=old_r;i<r;i++)
			for(j=0;j<c;j++)
				b[i][j]=1;

	}
	else{
		puts("error");
		exit(1);
	}



l1:	printf("The matrix is\n");
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d ",b[i][j]);
		}

		printf("\n");
	}
	printSum(b,r,c);

	   for(i=0;i<c;i++)
	  { d1=d1+b[i][i];
	  d2=d2+b[i][(c-1)-i];
}
	   printf("diagonal=%d \n antidiagonal= %d",d1,d2);

	return(0);


}

