#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
 int **p = NULL;
 int M = 0;
 int N = 0;
 int old_M = 0;
 int old_N = 0;	
 int i,j,m,n;
 int rem = 0;
 int val = 0;
 int sum = 0;
 int diagonal = 0;
 int antidiagonal = 0;
 
 printf("Enter the matrix size :\n");
 lable1:printf("Enter M : ");
 scanf("%d",&M);
 if(M <= 0) {
	fprintf(stderr,"Invalid input!!! Please Enter positive integer value\n");
	goto lable1;
 }
 lable2:printf("Enter N : ");
 scanf("%d",&N);
 if(N <= 0) {
	fprintf(stderr,"Invalid input!!! Please Enter positive integer value\n");
	goto lable2;
 }
 printf("M = %d N = %d\n",M,N);
 old_M = M;
 old_N = N;
 
 /* allocating memory for rows and columns */
 p = (int **)malloc(M * sizeof(int *));
 if(p == NULL) {
	fprintf(stderr,"clould not allocate memory!!!\n");
	exit(EXIT_FAILURE);	
 }
 
 for(i = 0; i < M; i++) {
	p[i] = (int *)malloc(N * sizeof(int));
 	if(p[i] == NULL) {
	fprintf(stderr,"clould not allocate memory!!!\n");
	exit(EXIT_FAILURE);	
 	}
 }
 
 /* input from user */
 printf("Enter the matrix data : \n");
 for(i = 0; i < old_M; i++) {
	for(j = 0; j < old_N; j++) {
		printf("p[%d][%d] = ",i,j);
		scanf("%d",&p[i][j]);
	}
 }
 
 /* rounding of row and column if necessary */
 if((rem = (M % 3)) != 0) {
	val = 3 - rem;
	M += val;
 }
 
 rem = 0;
 val = 0;
 
 if((rem = (N % 3)) != 0) {
	val = 3 - rem;
	N += val;	
 }

/* reallocating memory for row and column if necessary ,after rounding off  */
 if(M == old_M && N == old_N) 
	goto lable3;
 else if(M != old_M && N != old_N) {
        /* only cloumns */
	for(i = 0; i < old_M; i++) {
		p[i] = (int *)realloc(p[i],(N * sizeof(int)));	
	}
	
	/* Fill the 1's */
        for(i = 0; i < old_M; i++) {
		for(j = old_N; j < N; j++) {
			p[i][j] = 1;
		}
	}
	
	/* only row */
	p = (int **)realloc(p,(M * sizeof(int *)));
	for(i = old_M; i < M; i++) 
		p[i] = (int *)malloc((N * sizeof(int)));
	
	/* fill the 1's */
	for(i = old_M; i < M ; i++) {
		for(j = 0;j < N; j++) {
			p[i][j] = 1;
		}
	}	
      }
 else{
	if(M != old_M) {
		/*increase rows*/
		p = (int **)realloc(p,(M * sizeof(int *)));
		for(i = old_M; i < M; i++) {
			p[i] = (int *)malloc(N * sizeof(int));
		}
		/*fill the 1's*/
		for(i = old_M; i < M; i++) {
			for(j = 0; j < N; j++) {
				p[i][j] = 1;
			}
		}
	}
	else {
		/*increase col*/
		for(i = 0;i < M;i++) {
			p[i] = (int *)realloc(p[i],(N * sizeof(int)));
		}
		/* Fill the 1's */	
		for(i = 0;i < M;i++) {
			for(j = old_N; j < N; j++) {
				p[i][j] = 1;
			}
		}
	}	
 }

/* printing 3*3 micro matrix */
  lable3:
	for(i = 0; i < M; i++,printf("\n")) { 
		for(j = 0; j < N; j++) {
			printf("%*d  ",4,p[i][j]);
			if((j+1) % 3 == 0) printf("  ");
		}
		if((i+1) % 3 == 0) {
		printf("\n");
		}
        }

/* calculating sum of each 3*3 micro matrix */
for(i = 0; i < (M / 3); i++) {
          for(j = 0; j < (N / 3); j++) {
                  for(m = 0;m < 3;m++) {
                          for(n = 0; n < 3; n++) {
                                  sum += p[(m + (3*i))][(n + (3*j))];
                          }
                  }
          printf("Sum = %d\t",sum);
          sum = 0;
          }
    printf("\n");
   }

/* calculating diagonal and anti-diagonal */
for(i = 0;i < M; i++)   {
          diagonal += p[i][i];
          antidiagonal += p[i][M - 1 - i];
}
printf("diagonal = %d\n",diagonal);
printf("antidiagonal = %d\n",antidiagonal);

/* freeing memory */
for(i = 0; i < M; i++) {
	free(p[i]);
}
free(p);

exit(EXIT_SUCCESS);  
}
