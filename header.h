#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

#define SERVERPORT 8000
#define MAXBUF 1024
