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
 char buffer[BUFSIZ];
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
	while(shared_stuff->w_flg == 1) {
		sleep(1);
		printf("waiting for client...\n");
	}
		printf("Enter some data : ");
		fgets(buffer,BUFSIZ,stdin);
		strncpy(shared_stuff->data,buffer,BUF);
		shared_stuff->w_flg = 1;
 		if(strncmp(buffer,"end",3) == 0) 
			running = 0;
}

if(shmdt(shared_mem) == -1) {
	fprintf(stderr,"shmdt() failed\n");
	exit(EXIT_FAILURE);
 }

 exit(EXIT_SUCCESS);
 
}
