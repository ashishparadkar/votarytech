/* Program for counting no. of occurance of same data in a lIst */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
struct LL{
	int data;
	struct LL * next;
};
sigset_t set;
int sig;
void push(struct LL **,int);
void reverse(struct LL **);
void printLL(struct LL*);
void * odd(void *);
void * even(void *);
pthread_t p1,p2;
void catcher(int signum) {
  puts("inside catcher...");
}
int main()
{
	int i,n,x,y;
	struct LL * head=NULL;
	pthread_create(&p1,NULL,&odd,&head);
	pthread_create(&p2,NULL,&even,&head);	
	pthread_join(p2,NULL);
	printLL(head);
}

void push(struct LL **root,int data)
{
	struct LL * temp=(struct LL *)malloc(sizeof(struct LL));
	temp->data=data;
	temp->next=NULL;
	if(*root==NULL)
	{
		*root=temp;
		return;
	}
	temp->next=*root;
	*root=temp;
}
void printLL(struct LL * root)
{
	while(root!=NULL)
	{
		printf("%d ",root->data);
		root=root->next;
	}
	printf("\n");
}


void * odd(void *head)
{
	int i=1,sig;

	 struct sigaction sigact;

  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;
  sigact.sa_handler = catcher;
  sigaction(SIGALRM, &sigact, NULL);

	while(1){
	
		push((struct LL**)head,i);
			i+=2;
			pthread_kill(p2,SIGALRM);
			sleep(1);
			if(i>10)
			pthread_exit(0);

			pause();
		}
}
void *even(void * head)
{
	int i=2,sig;
	sigset_t set1;
 struct sigaction sigact;

  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;
  sigact.sa_handler = catcher;
  sigaction(SIGALRM, &sigact, NULL);
	while(1){
		sleep(1);
			push((struct LL **)head,i);
		i+=2;
		pthread_kill(p1,SIGALRM);
		
		if(i>10)
			pthread_exit(0);
		pause();
	}
}
