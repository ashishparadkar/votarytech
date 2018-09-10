#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>           /* For O_* constants */
#include<sys/stat.h>        /* For mode constants */
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

sem_t m1,m2,m3;
static unsigned int cnt1,cnt2,cnt3;

void sig_handler(int signum)
{
 printf("received SIGINT(%d)\n",signum);
 cnt1 = 1;
}

void *t1(void *arg)
{
 while(1) {
	
	sem_wait(&m1);
	printf("One\n");
	sleep(1);
	sem_post(&m2);
        if(cnt1 == 1) {
		printf("destroying m1\n");
		sem_destroy(&m1);
		cnt2 = 1;
		break;
	}
 }

pthread_exit(NULL);
}

void *t2(void *arg)
{
 
 while(1) {
	sem_wait(&m2);
	printf("Two\n");
 	sleep(1);
	sem_post(&m3);
	if(cnt2 == 1) {
		printf("destroying m2\n");	
		sem_destroy(&m2);
		cnt3 = 1;
		break;
	}	
 }

pthread_exit(NULL);
}

void *t3(void *arg)
{
 while(1) {
	sem_wait(&m3);
	printf("Three\n");
	sleep(1);
	if(cnt3 == 1) {
		printf("destroying m3\n");	
		sem_destroy(&m3);
		cnt1 = 1;
		break;
	}
	sem_post(&m1);
	
 }

pthread_exit(NULL);
}

int main()
{
 int ret = 0;
 pthread_t th1,th2,th3;
 signal(SIGINT,sig_handler); 
   
ret = sem_init(&m1, 0, 1);
if(ret == -1) {
	perror("sem_init1");
	exit(1);
}

ret = sem_init(&m2, 0, 0);
if(ret == -1) {
	perror("sem_init2");
	exit(1);
}

ret = sem_init(&m3, 0, 0);
if(ret == -1) {
	perror("sem_init3");
	exit(1);
}

ret=pthread_create(&th1,NULL,t1,NULL);
if(ret != 0) {
 perror("pthread_create(1)");
 exit(1);
}
ret=pthread_create(&th2,NULL,t2,NULL);
if(ret != 0) {
 perror("pthread_create(2)");
 exit(1);
}
ret=pthread_create(&th3,NULL,t3,NULL);
if(ret != 0) {
 perror("pthread_create(3)");
 exit(1);
}

pthread_join(th1,NULL);  
pthread_join(th2,NULL);  
pthread_join(th3,NULL);  

exit(0);
}

