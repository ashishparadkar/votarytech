#include<stdio.h>
#include<stdlib.h>
typedef struct q_node{
int info;
struct q_node *link;
}node;

node *front = NULL;
node *rear = NULL;

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

 while(ptr) {
	printf("%d--->",ptr->info);
	ptr =ptr->link;
 }
}

void insert(int item)
{
  node *new = NULL;
  new = (node *) malloc(sizeof(node));
  if(new == NULL) {
	printf("memory is not available!!!\n");
	return;
  }
  new->info = item;
  new->link = NULL;
  if(front == NULL)
	front  = new;
  else
  rear->link = new;
  rear = new;		
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

int peek(void)
{
 if(isempty()) {
	printf("Queue Underflow\n");
	exit(1);
 }

 return front->info;
}

int main()
{
  char choice;
  int item;
  while(1) {
	printf("--------MENU--------\n");
	printf("1.insert\n2.delete\n3.display front\n4.display all\n5.quit\n");
	printf("enter your choice :");
	scanf(" %c",&choice);
	switch(choice) {
		case '1':printf("Enter the element to be inserted :");
			 scanf("%d",&item);
			 insert(item);
			 break;
		case '2':printf("deleted element : %d\n",del());
			 break;
		case '3':printf("front : %d\n",peek());
			 break;
		case '4':display();
			 break;	
		case '5':exit(0);
		default:printf("Invalid choice!!!\n");
		
	}
  }
}
