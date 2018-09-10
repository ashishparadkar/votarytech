#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <string.h>
static unsigned int flag = 1,odd = 1,even = 2;
pthread_mutex_t lock;
unsigned int m,n;
void *thread_func(void *arg)
{
 while(m || n)
 {
 pthread_mutex_lock(&lock);
 /////////////////////////////////////////
 if(flag == 1 && n != 0) {
	printf("%u  ",odd);
	odd = odd + 2;
	n--;
	if(m != 0)
	flag = 0;
 	if(n == 0) {
		pthread_mutex_unlock(&lock);
		pthread_exit(NULL);	
	}
 }
 else if(flag == 0 && m != 0) {
	printf("%u  ",even);
	even = even + 2;
	m--;
  	if(n != 0)
	flag = 1;
 	if(m == 0) {
		pthread_mutex_unlock(&lock);
		pthread_exit(NULL);	
 	}
 } 
 /////////////////////////////////////////
 pthread_mutex_unlock(&lock);
 }
}

int main()
{
 int i = 0,err;
 pthread_t tid[2];
 if(pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
 }
 
 printf("enter the no. of even numbers :");
 scanf("%u",&m);
 printf("enter the no. of odd numbers :");
 scanf("%u",&n);
 if(n == 0)
	flag = 0;
 while(i < 2) {
        err = pthread_create(&(tid[i]), NULL, thread_func, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
 }	
 
 pthread_join(tid[0], NULL);
 pthread_join(tid[1], NULL);
 pthread_mutex_destroy(&lock);

 return 0;
}
