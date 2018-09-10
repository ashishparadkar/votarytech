#include "header.h"

int main()
{
 int socket1,socket2;
 int addrlen;
 struct sockaddr_in xferserver,xferclient;
 int ret;
	
 socket1 = socket(AF_INET,SOCK_STREAM,0);
 if(socket1 == -1) {
	fprintf(stderr,"could not create socket\n");
	exit(1);
 }
 
 xferserver.sin_family = AF_INET;
 xferserver.sin_port = htons(SERVERPORT);
 xferserver.sin_addr.s_addr = inet_addr("192.168.2.117");
 
 const int trueValue = 1;
 ret = setsockopt(socket1, SOL_SOCKET, SO_REUSEADDR, &trueValue, sizeof(trueValue)); 
 if(ret == -1) {
	fprintf(stderr,"could not set socket option SO_REUSEADDR by setsockopt()!\n");
	exit(1);
 }
 
 
 ret = bind(socket1,(struct sockaddr *)&xferserver,sizeof(xferserver));
 if(ret == -1) {
//	fprintf(stderr," errno = %d, could not bind to socket!\n",errno);
	perror("bind failed");
	exit(1);
 }
 
 ret = listen(socket1,5);
 if(ret == -1) {
	fprintf(stderr,"could not listen on socket!\n");
	exit(1);
 }

 for(;;) {
	int fd;
	int i,rcnt,wcnt;
	char *bufptr;
	char buf[MAXBUF];
	char filename[MAXBUF];
	
	/* wait for an incoming connection */
	addrlen = sizeof(xferclient);

	/*use accept() to handle the incoming connection request and free up the original socket for other requestr */
	socket2 = accept(socket1,(struct sockaddr *)&xferclient,&addrlen);
	if(socket2 == -1) {
		fprintf(stderr,"could not accpet connection from client\n");
		exit(1);
	}

	/* get a filename from the client over the socket */
	i = 0;

	if((rcnt = read(socket2,filename + i,MAXBUF)) > 0) {
		i += rcnt;
	}

	if(rcnt == -1) {
		fprintf(stderr,"could not read filename from socket!\n");
		close(socket2);
		continue;
	}

	filename[i + 1] = '\0';

	printf("Fetching file %s\n",filename);
	
	/* open file for reading */
	fd = open(filename,O_RDONLY);
	if(fd == -1) {
		fprintf(stderr,"could not open a file for reading!\n");
		close(socket2);
		continue;
   	}
	
	/* reset the read counter */
	rcnt = 0;

	/* read the file and send it to the client in the chunks of MAXBUF */

	while((rcnt = read(fd,buf,MAXBUF)) > 0) {
		wcnt = 0;
		bufptr = buf;
		while(wcnt < rcnt) {
			rcnt -= wcnt;
			bufptr += wcnt;
			wcnt = write(socket2,bufptr,rcnt);

			if(wcnt == -1) {
				fprintf(stderr,"could not write file to client!\n");
				close(socket2);
				continue;
			}
		}
	}
	
	close(fd);
	close(socket2);
	}

close(socket1);
return 0;
}
