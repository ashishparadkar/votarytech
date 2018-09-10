#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

//#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*10)

int main()
{
 int pipe_fd;
 int ret;
 int byte_sent = 0;
 char buffer[BUFFER_SIZE + 1];
 if(access("my_fifo",F_OK) == -1) {
	ret = mkfifo("my_fifo",0777);
	if(ret != 0) {
		fprintf(stderr,"could not create a fifo %s\n","my_fifo");
		exit(EXIT_FAILURE);
	}
 }

 printf("process %d opening FIFO O_WRONLY\n",getpid());
 pipe_fd = open("my_fifo",O_WRONLY);
 if(pipe_fd == -1) {
	fprintf(stderr,"could not open a fifo file for writting!!!\n");
	exit(EXIT_FAILURE);
 }
 
 while(byte_sent < TEN_MEG) {
	ret = write(pipe_fd,buffer,BUFFER_SIZE);
 	byte_sent += ret;
	if(ret == -1) {
 		fprintf(stderr,"Write error on pipe\n");
		exit(EXIT_FAILURE);
 	}
 }

 close(pipe_fd);
 printf("process : %d\n finished\n",getpid());
 exit(EXIT_SUCCESS);
}
