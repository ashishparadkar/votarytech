#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
 int fd[2];
 int ret,data_processed,i,v;
 char data[1024] = "ashish";
 char rbuf[1024];
 
 if(pipe(fd) == -1) {
	fprintf(stderr,"failed to open file\n");
	exit(EXIT_FAILURE);
 }

ret = fork();
if(ret == -1) {
	fprintf(stderr,"fork() failure\n");
	exit(EXIT_FAILURE);
}
else if(ret == 0) {
	/* child context */
	close(fd[1]);
  	data[0]='\0';
	i = 0;
	do {
		read(fd[0],data + i,1);
	   }while(data[i++] != '\0');
	printf("data received : %s\n",data);
	close(fd[0]);
	exit(1);
}
else {
	/* parent context */
	close(fd[0]);
	write(fd[1],data,strlen(data) + 1);
	wait(&v);
}

 
 close(fd[0]);
 close(fd[1]);
 exit(EXIT_SUCCESS);
}
