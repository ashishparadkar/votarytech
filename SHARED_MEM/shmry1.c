#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/shm.h>

#define BUF 2048

struct shared_use_st{
	int w_flg;
	char data[BUF];
};

int main()
{
 int running = 1;
 void *shared_mem = NULL;
 struct shared_use_st *shared_stuff = NULL;
 int shmid;
 srand((unsigned int)getpid());
 
 shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
 if(shmid == -1) {
  	fprintf(stderr,"shmget() failed\n");
	exit(EXIT_FAILURE);
 }

 shared_mem = shmat(shmid,(void *)0,0);
 if(shared_mem == (void *)-1) {
  	fprintf(stderr,"shmat() failed\n");
	exit(EXIT_FAILURE);
 }

 shared_stuff = (struct shared_use_st *)shared_mem;
 shared_stuff->w_flg = 0;
 while(running) {
	if(shared_stuff->w_flg) {
		printf("you wrote : %s\n",shared_stuff->data);
		sleep(rand()%4);
		shared_stuff->w_flg = 0;
		if(strncmp(shared_stuff->data,"end",3) == 0)
			running = 0;
	} 
 }

 if(shmdt(shared_mem) == -1) {
	fprintf(stderr,"shmdt() failed\n");
	exit(EXIT_FAILURE);
 }

 if(shmctl(shmid,IPC_RMID,0) == -1) {
	fprintf(stderr,"Failed to delete!!!\n");
	exit(EXIT_FAILURE);
 }

 exit(EXIT_SUCCESS);
 
}
