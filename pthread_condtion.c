// C program to implement cond(), signal()
// and wait() functions
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
struct LL{
	int data;
	struct LL * next;
};
int done = 1;
char msg[20];
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

// Thread function
void* foo(void * head)
{
	int i=1;
	while(1){
		pthread_mutex_lock(&lock);
		if (done == 1){
			done = 2;

			push((struct LL**)head,i);
			i+=2;
		
			pthread_cond_wait(&cond1, &lock);
		}
		
		pthread_mutex_unlock(&lock);
		if(i>10)
			pthread_exit(0);
	}
	printf("Returning thread\n");

	return NULL;
}

void * foo1(void * head)
{
	int i=2;
	while(1){
		pthread_mutex_lock(&lock);
		if(done==2){
			done =1;

			push((struct LL **)head,i);
		i+=2;
	
//			sleep(1);
			pthread_cond_signal(&cond1);
			
		}
		pthread_mutex_unlock(&lock);
			if(i>10)
			pthread_exit(0);
	}

	printf("Returning thread\n");

	return NULL;
}

// Driver code
int main()
{
	pthread_t tid1, tid2;
	struct LL * head=NULL;
	// Create thread 1
	pthread_create(&tid1, NULL, foo, &head);
	pthread_create(&tid2, NULL, foo1, &head);

	// wait for the completion of thread 2
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printLL(head);
	return 0;
}
