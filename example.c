/* Program for counting no. of occurance of same data in a lIst */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
struct LL{
	int data;
	struct LL * next;
};
struct LL * head=NULL;
pthread_mutex_t count_mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition_var2 = PTHREAD_COND_INITIALIZER;

sigset_t set;
int sig,i = 1,j = 2;
int k = 1;
int *sigptr=&sig;
void push(struct LL *,int);
//void reverse(struct LL **);
void printLL(struct LL*);

void * odd(void *);

void * even(void *);
pthread_t p1,p2;
/*
void handler(int sig)
{
	printf("Recieved %d",sig);

}
*/
void handler(int sig)
{
  
		push((struct LL *)head,k);
	//	i+=2;
                k++;
}

void set_sig_handler(int sig)
{
        struct sigaction action;


        action.sa_flags = SA_SIGINFO; 
        action.sa_sigaction = handler;

        if (sigaction(sig, &action, NULL) == -1) { 
            perror("sigusr: sigaction");
            _exit(1);
        }

}

void mask_sig(int sig)
{
	sigset_t mask;
	sigemptyset(&mask); 
        sigaddset(&mask, sig); 
                
        pthread_sigmask(SIG_BLOCK, &mask, NULL);
        
}
int main()
{
	int i,n,x,y;
//	struct LL * head=NULL;
//	signal(SIGUSR1,handler);
//	pthread_t p1,p2;
//	sigaddset(&set,SIGINT);
//	sigaddset(&set,SIGUSR1);
//	sigprocmask(SIG_BLOCK, &set, NULL);
        set_sig_handler(SIGUSR1);
        set_sig_handler(SIGUSR2);
	pthread_create(&p1,NULL,&odd,&head);
	pthread_create(&p2,NULL,&even,&head);	
//	pthread_kill(p1,2);
//	sigprocmask(SIG_UNBLOCK, &set, NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printLL(head);
}

void push(struct LL *root,int data)
{
	struct LL *temp=(struct LL *)malloc(sizeof(struct LL));
	temp->data=data;
	temp->next=NULL;
	if(root==NULL)
	{
		root=temp;
		return;
	}
	temp->next=root;
	root=temp;
}
void printLL(struct LL *root)
{
	while(root!=NULL)
	{
		printf("%d ",root->data);
		root=root->next;
	}
	printf("\n");
}


void *odd(void *head)
{
	int sig;
        mask_sig(SIGUSR1);
        sleep(2);
	while(1){
		//sleep(2);
		if(sigaddset(&set,SIGUSR2)==-1)
			printf("sigadd1 fail\n");
//	        pthread_mutex_lock( &count_mutex1 );
                
//		push((struct LL**)head,i);
//			i+=2;
       //         pthread_cond_signal( &condition_var2 );
          //      pthread_cond_wait( &condition_var1, &count_mutex1 );
  //              pthread_mutex_unlock( &count_mutex1 );
		if(k>10)
			pthread_exit(0);
//		sleep(1);
		pthread_kill(p2,SIGUSR1);
//
		if(sigwait(&set,sigptr)!=0)
			printf("wait1 fail\n");
	//	raise(10);
	}
}
void *even(void * head)
{
	int sig;
	sigset_t set1;
	mask_sig(SIGUSR2);
//	signal(SIGUSR1,handler);
	while(1){
		//sleep(2);
		if(sigaddset(&set1,SIGUSR1)==-1)
			printf("sigadd1 fail\n");
		if(sigwait(&set1,&sig)!=0)
			printf("wait2 fail\n");
//		pthread_mutex_lock( &count_mutex2 );
//                pthread_cond_wait( &condition_var2, &count_mutex2 );
//		push((struct LL **)head,i);
//		i+=2;
//                pthread_cond_signal( &condition_var1 );
 //               pthread_mutex_unlock( &count_mutex2 );
  		if(k>10)
			pthread_exit(0);
		pthread_kill(p1,SIGUSR2);
//		raise(2);
	}
}
