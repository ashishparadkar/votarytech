#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
int pipe_p[2];
int pipe_c[2];

int main()
{
	char buf[BUFSIZ];
	pid_t cpid;
	int i=0;
	/* opening unnamed pipe for communication between parent & child process*/
	if(pipe(pipe_p)==-1) {
		perror("pipe");
		exit(EXIT_FAILURE);	
	}

	if(pipe(pipe_c)==-1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	/* making read call on both pipes non-blockable */
	fcntl(pipe_p[0],F_SETFL,O_NONBLOCK);
	fcntl(pipe_c[0],F_SETFL,O_NONBLOCK);

	/* creating child process */
	cpid=fork();

	if(cpid==0) {
		/*-----------------------------------------------child context----------------------------------------------*/
		close(pipe_p[1]);
		close(pipe_c[0]);

		while(1)
		{      
		       	/*child reads from parent pipe(pipe_c).if pipe is empty read returns -1 so read will get invoked 
			 *in while loop multiple times.
			 *When data will arrive in the pipe while loop will break.
			 */ 	
			while(read(pipe_p[0],buf,BUFSIZ)==-1);
			
			/* condition to end communication */
			if(strcmp(buf,"quit")==0) {
				close(pipe_p[0]);
				close(pipe_c[1]);
				printf("parent signaled to child to end communication\n");
				exit(EXIT_SUCCESS);
			}
                        
			/* Do manipulation on received data */
			for(i=0;buf[i]!='\0';i++)
			{
				if((buf[i]>='a') && (buf[i]<='z'))
					buf[i]-=32;
			}
                        
			/* child Writing converted output on child pipe (pipe_c) */
			write(pipe_c[1],buf,strlen(buf)+1);
			
			memset(buf,'\0',BUFSIZ);
		}
	}
	else {
		/*----------------------------------------------parent context----------------------------------------------*/
		close(pipe_p[0]);
		close(pipe_c[1]); 

		while(1) {
			printf("Enter string (\"quit\" to end communication):\n");
			fgets(buf,BUFSIZ,stdin);
			buf[strlen(buf)-1]='\0';

			/* parent writing data to parent pipe (pipe_p) */
			write(pipe_p[1],buf,strlen(buf)+1);
                        
			/* condition to end communication */
			if(strcmp(buf,"quit")==0) {
				sleep(1);	
				close(pipe_p[1]);
				close(pipe_c[0]);
				exit(EXIT_SUCCESS);
			}

			memset(buf,'\0',BUFSIZ);
                        
			/* reading echo of parent coming from child pipe after conversion */
			while(read(pipe_c[0],buf,BUFSIZ)== -1);

			printf("parent echo:%s\n",buf);
		}
	}

}
