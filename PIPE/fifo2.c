#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>

#define BUFFER_SIZE PIPE_BUF
int main()
{
 int pipe_fd;
 int res;
 char buffer[BUFFER_SIZE + 1];
 int bytes_read = 0;
 memset(buffer,'\0',BUFFER_SIZE);
 printf("process %d openning fifo O_RDONLY\n",getpid());
 pipe_fd = open("my_fifo",O_RDONLY);
 if(pipe_fd == -1) {
	fprintf(stderr,"could not open a fifo file in O_RDONLY mode\n");
	exit(EXIT_FAILURE);
 }

 do {
	res = read(pipe_fd,buffer,BUFFER_SIZE);
	bytes_read += res;
 }while(res > 0);

 close(pipe_fd);
 printf("process %d finished,%d bytes read\n",getpid(),bytes_read);
 exit(EXIT_FAILURE);
} 
