#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>           /* For O_* constants */
#include<sys/stat.h>        /* For mode constants */
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>

sem_t *m1,*m2,*m3;
static unsigned int cnt1,cnt2,cnt3;

void sig_handler(int signum)
{
 printf("received SIGINT(%d)\n",signum);
 cnt1 = 1;
}

void *t1(void *arg)
{
 while(1) {
	
	sem_wait(m1);
	printf("One\n");
	sleep(1);
	sem_post(m2);
        if(cnt1 == 1) {
		printf("closing m1\n");
		sem_close(m1);
		cnt2 = 1;
		break;
	}
 }

pthread_exit(NULL);
}

void *t2(void *arg)
{
 
 while(1) {
	sem_wait(m2);
	printf("Two\n");
 	sleep(1);
	sem_post(m3);
	if(cnt2 == 1) {
		printf("closing m2\n");	
		sem_close(m2);
		cnt3 = 1;
		break;
	}	
 }

pthread_exit(NULL);
}

void *t3(void *arg)
{
 while(1) {
	sem_wait(m3);
	printf("Three\n");
	sleep(1);
	if(cnt3 == 1) {
		printf("closing m3\n");	
		sem_close(m3);
		cnt1 = 1;
		break;
	}
	sem_post(m1);
	
 }

pthread_exit(NULL);
}

int main()
{
 int ret = 0;
 pthread_t th1,th2,th3;
 signal(SIGINT,sig_handler); 
m1 = sem_open("/sync1", O_CREAT|O_EXCL, S_IRUSR | S_IWUSR, 1); 
 if (m1 == SEM_FAILED) {
	perror("sem_open");
	exit(1);
	}
 
m2 = sem_open("/sync2", O_CREAT|O_EXCL, S_IRUSR | S_IWUSR, 0); 
 if (m2 == SEM_FAILED) {
   	perror("sem_open");
	exit(1);
	}
 
m3 = sem_open("/sync3", O_CREAT|O_EXCL, S_IRUSR | S_IWUSR, 0);
 if (m3 == SEM_FAILED) {
   	perror("sem_open");
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

sem_unlink("/sync1");
sem_unlink("/sync2");
sem_unlink("/sync3");
exit(0);
}

