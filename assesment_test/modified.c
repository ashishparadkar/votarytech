#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#define MAX 20

struct enqdata{
	unsigned int len;
	int info[100];	
};

struct deqdata{
	unsigned int len;
};

static struct enqdata eop[20];
static struct deqdata dop[20];
static int enqcount = 0;
static int deqcount = 0;
FILE *fpwr = NULL;

sem_t m1,m2;

int cq_arr[MAX];
int front = -1;
int rear = -1;

void extract(char *buf,int size)
{ int i;
	int j = 0; 
	int cnt = 0;
	int ret;
	int k = 0;
	unsigned int operation;
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
			if(ret == 1) {
				operation = 1;
			}
			else if(ret == 2) {
				operation = 2;
			}
			else
				return;
			cnt++;						
		}
		else if(cnt  == 1) {
			if(operation == 1)
				eop[enqcount].len = ret;
			else if(operation == 2) {
				dop[deqcount].len = ret;
				deqcount++;
				return;
			}
			cnt++;
		}
		else {
			eop[enqcount].info[k] = ret;
			k++; 
		}
	}

	if(operation == 1)
		enqcount++;
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
		return 0 ;
	}
	i = front;
	if(front <= rear) {
		while(i <= rear) {
			total++;
			i++;
		}
	}
	else {
		while(i <= MAX -1)
		{
			total++; 	
			i++;
		}
		i = 0;
		while(i <= rear) {
			total++;
			i++;
		}
	}
	return total;	
}

void *producer(void *arg)
{
	int i = 0,j;


	while(1) {
		sem_wait(&m1);
		if(i < enqcount) {
			if((MAX - tot()) < eop[i].len)
				goto l1;
			for(j = 0;j < eop[i].len;j++) {
				insert(eop[i].info[j]);
			}
			printf("Enqueued %d messages\n",eop[i].len);
			i++;	
		}
l1:	sleep(1);
	sem_post(&m2);
	}
}

void *consumer(void *arg)
{
	int i = 0,j;
	int flag = 1;

	while(1) {
		sem_wait(&m2);
		if(i < deqcount) {
			if(dop[i].len > tot())
				goto l2;
			for(j = 0;j < dop[i].len; j++)
				fprintf(fpwr,"%5d  ",del());
			printf("Dequeued %d messages\n",dop[i].len);
			fprintf(fpwr,"Dequeued %d messages\n",dop[i].len);
			i++;
		}
		else if (i >= deqcount && flag == 1) {
			fclose(fpwr);
			flag = 0;
		}
l2:	sleep(1);
	sem_post(&m1);
	}
}

int main()
{
	char *line = NULL;
	FILE *fprd = NULL;
	size_t len = 0;
	size_t read = 0;
	int i,j,ret;

	pthread_t ptid,ctid;

	fprd = fopen("test.txt","r");
	if(fprd == NULL) {
		perror("fopen(r) fails");
		exit(1);
	}

	fpwr = fopen("dequeue.txt","a");
	if(fpwr == NULL) {
		perror("fopen(w) fails");
		exit(1);
	}

	while ((read = getline(&line, &len, fprd)) != -1) 
		extract(line,read);



	printf("enqcount = %d\n",enqcount);
	printf("deqcount = %d\n",deqcount);
	printf("Enqueue operations :\n");
	for(i = 0;i < enqcount;i++,printf("\n")) {
		printf("len      : %d\t",eop[i].len);	
		for(j = 0;j < eop[i].len;j++)
			printf("%d  ",eop[i].info[j]);	
	}

	printf("Dequeue operations :\n");
	for(i = 0;i < deqcount;i++,printf("\n"))
	{
		printf("len      : %d\t",dop[i].len);	
	}

	ret = sem_init(&m1, 0, 1);
	if(ret == -1) {
		perror("sem_init1");
		exit(1);
	}

	ret = sem_init(&m2, 0, 0);
	if(ret == -1) {
		perror("sem_init2");
		exit(1);
	}

	ret = pthread_create(&ptid,NULL,producer,NULL);
	if(ret != 0) {
		perror("pthread_create(1)");
		exit(1);
	}

	ret = pthread_create(&ctid,NULL,consumer,NULL);
	if(ret != 0) {
		perror("pthread_create(2)");
		exit(1);
	}

	pthread_join(ptid,NULL);
	pthread_join(ctid,NULL);

	free(line);
	fclose(fprd);
	exit(EXIT_SUCCESS);
}
