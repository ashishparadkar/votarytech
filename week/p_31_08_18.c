#include<stdio.h>

int main()
{
  int num,numcp,i;
  int rem = 0;
  int sum = 0;
  for(i = 10; i < 100; i++) {
	num = i;
	sum = 0;
 	rem = 0;
	while(num) {
		rem = num % 10;
		sum += rem;
		num = num / 10; 
	}
	if(i == (3 * sum)) {
		printf("peculiar number : %d\n",i);
	}
  }
}
