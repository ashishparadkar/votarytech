#include<stdio.h>
#include<stdlib.h>

#define MAX 10

int cq_arr[MAX];
int front = -1;
int rear = -1;

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
	printf("Q underflow\n");
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

void display(void)
{
 int i;
 if(isempty()) {
  	printf("Q is empty\n");
	return;
 }

 i = front;
 if(front <= rear) {
	while(i <= rear)
		printf("%d--->",cq_arr[i++]);
 }
 else {
	while(i <= MAX -1)
		printf("%d--->",cq_arr[i++]);
	i = 0;
	while(i <= rear)
		printf("%d--->",cq_arr[i++]);
 }
 printf("\n");
}

int peek()
{
 if(isempty()) {
	printf("Q underflow\n");
	exit(1);
 }
 
 return cq_arr[front];
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
