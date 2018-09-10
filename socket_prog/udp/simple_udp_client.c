#include"header.h"

int main(int argc,char **argv)
{
 int udpsocket;
 int ret;
 int addrlen;
 struct sockaddr_in udpclient,udpserver;
 char buf[MAXBUF];
 
 if(argc != 3) {
	fprintf(stderr,"Usage : %s <ip addr> <port>\n",argv[0]);
	exit(1);
 }

 /* create a socket */
 if((udpsocket = socket(AF_INET,SOCK_DGRAM,0)) < 0) {PRINT_ERRMSG(); exit(1);}

 /* client address */
 udpclient.sin_family = AF_INET;
 udpclient.sin_addr.s_addr = INADDR_ANY;
 udpclient.sin_port = 0;
 
 if((ret = bind(udpsocket,(struct sockaddr *)&udpclient,sizeof(udpclient))) < 0) {PRINT_ERRMSG(); close(udpsocket);exit(1);}
 
 /* set up the message to sent to the server */
 strcpy(buf,"client hello\n");
 
 /* server address */
 udpserver.sin_family = AF_INET;
 udpserver.sin_addr.s_addr = inet_addr(argv[1]);
 udpserver.sin_port = htons(atoi(argv[2]));
 
 if((ret = sendto(udpsocket, buf, strlen(buf) + 1, 0, (struct sockaddr *)&udpserver,sizeof(udpserver))) < 0) {
	fprintf(stderr,"could not send a message\n");
 } 
 else {
	printf("message sent\n");

 	/* if message sent : wait for confirmation from server */
 	addrlen = sizeof(udpserver);
	if((ret = recvfrom(udpsocket,buf,MAXBUF,0,(struct sockaddr *)&udpserver,&addrlen)) < 0) {
		fprintf(stderr,"could not receive from a message\n");
	}
        else {
		buf[ret] = 0;
		printf("ACK : %s\n",buf);
  	}
 }
close(udpsocket);
return 0;
}
