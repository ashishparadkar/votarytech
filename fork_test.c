#include<stdio.h>
#include<stdlib.h>

int main() {
 int *ptr = malloc(sizeof(int));
 //scanf("%d",ptr);
 *ptr = 10;
 if(fork()== 0) {
    *ptr = 8;	
   printf("val = %d\n",*ptr);
 }
 else {
 printf("parent context = %d\n",*ptr);
 }

}
