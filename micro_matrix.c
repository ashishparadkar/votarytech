#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

#define M 6
#define N 6

int main()
{
 int i,j,m,n,sum = 0;
 int diagonal = 0;
 int antidiagonal = 0;
 int arr[M][N];
 srand((unsigned int)getpid()); 
 for(i = 0;i < M;i++) {
 	for(j = 0;j < N;j++){
		arr[i][j] = (rand() % 9) + 1;
 	}
 } 

 for(i = 0;i < M;i++,printf("\n")) {
	for(j = 0;j < N;j++) {
		printf("%*d",4,arr[i][j]);
	}
 }

for(i = 0;i < M; i++) 	{
	diagonal += arr[i][i];
 	antidiagonal += arr[i][M - 1 - i];
}

printf("diagonal = %d\n",diagonal);
printf("antidiagonal = %d\n",antidiagonal);

 for(i = 0; i < (M / 3); i++) {
	for(j = 0; j < (N / 3); j++) {
		for(m = 0;m < 3;m++) {
			for(n = 0; n < 3; n++) {
				sum += arr[(m + (3*i))][(n + (3*j))]; 
			}
		}
	printf("Sum = %d\t",sum);
	sum = 0;
	}
 printf("\n");
 }
 
 for(i = 0; i < (M / 3); i++) {
	for(j = 0; j < (N / 3); j++) {
		for(m = 0;m < 3;m++,printf("\n")) {
			for(n = 0; n < 3; n++) {
				printf("%d  ",arr[(m + (3*i))][(n + (3*j))]); 
			}
		}
	printf("\n");
	}
 printf("\n");
 }


}
