#include"header.h"

//#define PRINT_ERRMSG() fprintf(stderr,"Internal error: at %s"" ""line %d",__FILE__,__LINE__)

int main(int argc,char **argv)
{
 int udp_socket;
 int ret = 0;
 int addrlen = 0;
 struct sockaddr_in udpserver,udpclient;
 char buf[MAXBUF];
 if(argc != 2) {
	fprintf(stderr,"Usage : %s <port>\n",argv[0]);
	exit(1);
 }

 /* create udp socket */
 if((udp_socket = socket(AF_INET,SOCK_DGRAM,0)) == -1) {PRINT_ERRMSG(); exit(1);} 
 
   /* Set socket to allow broadcast */
    int broadcastPermission = 1;
      if (setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
           sizeof(broadcastPermission)) < 0) {
                 PRINT_ERRMSG();
                 exit(1);
     }
 
 /* Set up server address and port */ 
 udpserver.sin_family = AF_INET;
 udpserver.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.2.255");//htonl(INADDR_ANY);
 udpserver.sin_port = htons(atoi(argv[1]));
 
 /* bind to the socket */
 if((ret = bind(udp_socket,(struct sockaddr *)&udpserver,sizeof(udpserver))) < 0) {PRINT_ERRMSG(); exit(1);}
 printf("udp server is deployed successfully\n");
 while(1) {
	addrlen = sizeof(udpclient);
	if((ret = recvfrom(udp_socket,buf,MAXBUF,0,(struct sockaddr *)&udpclient,&addrlen)) < 0) { 
 		printf("could not receive msg\n"); 
		ret = 0;
		continue;
	}
	printf("Received %s\n",buf);
 	strcpy(buf,"OK");
	if((ret = sendto(udp_socket, buf, strlen(buf)+1, 0,(struct sockaddr *)&udpclient,sizeof(udpclient))) < 0) 
		printf("could not send confirmation!\n");
	
 }

/* cleanup */
close(udp_socket);
return 0;
}
