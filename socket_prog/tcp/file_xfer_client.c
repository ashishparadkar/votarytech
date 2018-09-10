#include "header.h"

int main(int argc, char **argv)
{
 int sockd;
 int counter;
 int fd;
 struct sockaddr_in xferserver;
 char buf[MAXBUF];
 int ret;
 
 if(argc < 3) {
	fprintf(stderr,"Usage : %s <ip address> <filename> <dest filename>\n",argv[0]);
	exit(1);
 }

 /* create socket */ 
 sockd = socket(AF_INET, SOCK_STREAM, 0);
 if(sockd == -1) {
	fprintf(stderr,"could not open a socket!\n");
	exit(1);
 }

 /* set up the server infomation */

 xferserver.sin_family = AF_INET;
 xferserver.sin_addr.s_addr = inet_addr(argv[1]);
 xferserver.sin_port = htons(SERVERPORT); 

 /* connect to a server */
 ret = connect(sockd,(struct sockaddr *)&xferserver,sizeof(xferserver));
 if(ret == -1) {
	fprintf(stderr,"could not connect to the server!\n");
	exit(1);
 }

 /* send the name of the file which we want to retrieve from server */
 ret = write(sockd,argv[2],strlen(argv[2])+1);
 if(ret == -1) {
 	fprintf(stderr,"could not send filename to the server!\n");
	exit(1);
 }

 /* call shutdown to set our socket to read-only */
 shutdown(sockd,SHUT_WR);

 /* open up the handle to our destination file to receive the contents from the server */
 fd = open(argv[3],O_WRONLY | O_CREAT | O_APPEND);
 if(fd == -1) {
	fprintf(stderr,"could not open a destination file, using stdout.\n");
	fd = 1;
 }

 /* read the contents from the socket as long as there is data */ 
 while((counter = read(sockd,buf,MAXBUF)) > 0) {
	write(fd,buf,counter);
 }

 if(counter == -1) {
	fprintf(stderr,"could not read file from socket!\n");
	exit(1);
 }

 close(sockd);	
 return 0;
}
