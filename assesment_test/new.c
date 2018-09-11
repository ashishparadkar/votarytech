#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 20

struct data{
	unsigned int operation;
	unsigned int len;
	int info[100];	
};

static struct data op[20];
static int count = 0;
static int flag = 0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Empty=PTHREAD_COND_INITIALIZER;

int cq_arr[MAX];
int front = -1;
int rear = -1;

void extract(char *buf,int size)
{ int i;
  int j = 0; 
  int cnt = 0;
  int ret;
  int k = 0;
  char temp[BUFSIZ];
  while(j < size) {
  	for(i = 0;buf[j]!=32 && buf[j]!=10;i++,j++){
		temp[i] = buf[j];
  	}
	temp[i] = '\0';
	//printf("%s  ",temp);
	j++;
	
	
	ret = atoi(temp);
	if(cnt == 0) {
		op[count].operation = ret;
		cnt++;						
	}
	else if(cnt  == 1) {
		op[count].len = ret;
		cnt++;
 	}
	else {
		op[count].info[k] = ret;
		k++; 
	}
   }

count++;
}

int isempty(void)
{
 if(front == -1)
	return 1;
 else 
	return 0;
}

int isfull()
{
 if((front == 0 && rear == MAX-1) || (front == rear+1))
	return 1;
 else 
	return 0;
}

void insert(int item)
{
  if(isfull()) {
	printf("Q overflow\n");
	return;
  }
  if(front == -1)
	front = 0;
  if(rear == MAX-1)
	rear = 0;
  else
	rear = rear + 1;
 cq_arr[rear] = item;
}

int del(void)
{
  int item;
  if(isempty()) {
	printf("Q underflow\n");
	exit(1);
  }

 item = cq_arr[front];
 if(front == rear) {
	rear = -1;
	front = -1;
 }
 else if (front == MAX - 1)
	front = 0;
 else 
	front = front + 1;

 return item;
}

int tot(void)
{
 int i;
 int total = 0;
 if(isempty()) {
  	printf("Q is empty\n");
	return 0 ;
 }
 i = front;
 if(front <= rear) {
	while(i <= rear)
		total++;
 }
 else {
	while(i <= MAX -1)
		total++; 	
	i = 0;
	while(i <= rear)
		total++;
 }
 return total;	
}

void *producer(void *arg)
{
 int i = 0,j; 
	for (i = 0; i < count; i++) {
		pthread_mutex_lock (&mut);
/*		while (isfull()) {
			printf ("producer: queue FULL.\n");
			pthread_cond_wait (&Full,&mut);
		}
*/		while(flag != 0);
		if(flag == 0) {
			
			if(op[i].operation == 1) {	
				for(j = 0;j < op[i].len;j++)
					insert(op[i].info[j]);
		printf("Enqueued %d messages\n",op[i].len);
	//	pthread_cond_wait(&Full,&mut);
		}
		//	else if(op[i].operation == 2){
				
		//	}
		flag = 1;
		}	
 
		pthread_cond_wait(&Full,&mut);
		pthread_mutex_unlock (&mut);
	//	pthread_cond_signal (&Empty);
		usleep (100000);
	}

while(1) {
	
	pthread_mutex_lock();
	for(;;)	{
	if(done != 1) break;
	
	if(op[i].operation == 1)
		break;
	else
		i++; 
	
	}
	if()
	pthread_mutex_unlock();
		
}
}

void *consumer(void *arg)
{
  int i,j;
	
	for (i = 0; i < count; i++) {
		pthread_mutex_lock (&mut);
/*		while (isempty()) {
			printf ("consumer: queue EMPTY.\n");
			pthread_cond_wait (&Empty,&mut);
		}
*/
	        while(flag != 1);
		
		if(flag == 1) {	        	
		if(op[i].operation == 2) {
			if(tot() >= op[i].len) {
				for(j = 0;j < op[i].len;j++)
					del();		
				printf("Dequeued %d messages\n",op[i].len);
			}
 
	//		pthread_cond_signal (&Full);
		}
			
		flag = 0;	
		pthread_cond_signal (&Full);
		}
		
	//	pthread_cond_signal (&Full);
		pthread_mutex_unlock (&mut);
	//	pthread_cond_signal (&Full);
		usleep(200000);
	}

}

int main()
{
char *line = NULL;
FILE *fprd = NULL;
FILE *fpwr = NULL;
size_t len = 0;
size_t read = 0;
int i,j;
pthread_t ptid,ctid;

fprd = fopen("test.txt","r");
if(fprd == NULL) {
	perror("fopen() fails");
	exit(1);
}

while ((read = getline(&line, &len, fprd)) != -1) {
	extract(line,read);
	printf("\n");
}

printf("count = %d\n",count);
for(i = 0;i < count;i++,printf("one operation end\n"))
	{
		printf("operaion : %d\t",op[i].operation);
		printf("len      : %d\t",op[i].len);
		if(op[i].operation == 1)	
		for(j = 0;j < op[i].len;j++)
			printf("%d  ",op[i].info[j]);	
	}

pthread_create(&ptid,NULL,producer,NULL);
pthread_create(&ptid,NULL,consumer,NULL);

pthread_join(ptid,NULL);
pthread_join(ctid,NULL);

free(line);
fclose(fprd);
exit(EXIT_SUCCESS);
}
