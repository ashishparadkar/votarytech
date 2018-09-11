#include<stdio.h>
#include<stdlib.h>
typedef struct q_node{
int priority;
int info;
struct q_node *link;
}node;

node *front = NULL;
//node *rear = NULL;

int isempty(void)
{
 if(front == NULL)
	return 1;
 else 
	return 0;
}

void display(void)
{
 node *ptr = front;
 if(isempty()) {
	printf("Q is empty\n");
	return;
 }

printf("Priority	Item\n");
 while(ptr) {
	printf("%5d	%5d\n",ptr->priority,ptr->info);
	ptr =ptr->link;
 }
}

void insert(int item,int item_priority)
{
  node *new = NULL,*p = NULL;
  new = (node *) malloc(sizeof(node));
  if(new == NULL) {
	printf("memory is not available!!!\n");
	return;
  }
  new->info = item;
  new->priority = item_priority;
  new->link = NULL;
  if(isempty() || item_priority < front->priority) {
	new->link = front;
	front = new;
  }
  else {
  	p = front;
	while(p->link!=NULL && p->link->priority<=item_priority)
		p = p->link;
	new->link = p->link;
	p->link = new;
  }		
}

int del(void)
{
 node *tmp = NULL;
 int item;
 if(isempty()) {
	printf("Queue underflow\n");
	exit(1);
 }
 tmp = front;
 item = tmp->info;
 front = front->link;
 free(tmp);
 return item;
}

int main()
{
  char choice;
  int item,item_priority;
  while(1) {
	printf("--------MENU--------\n");
	printf("1.insert\n2.delete\n3.display all\n4.quit\n");
	printf("enter your choice :");
	scanf(" %c",&choice);
	switch(choice) {
		case '1':printf("Enter the element to be inserted :");
			 scanf("%d",&item);
			 printf("Enter priority :");	
			 scanf("%d",&item_priority);
			 insert(item,item_priority);
			 break;
		case '2':printf("deleted element : %d\n",del());
			 break;
		case '3':display();
			 break;	
		case '4':exit(0);
		default:printf("Invalid choice!!!\n");
		
	}
  }
}
