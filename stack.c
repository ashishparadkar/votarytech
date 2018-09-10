#include<stdio.h>
#include<stdlib.h>
int top = -1;
char buf[BUFSIZ];

int isfull(void)
{
  if(top == (BUFSIZ - 1))
	return 1;
  else 
	return 0;
}

int isempty(void)
{
  if(top == -1) 
	return 1;
  else
	return 0;
}

char peek(void)
{
  if(top == -1) {
	printf("No peek!!! Stack is empty...\n");
	exit(-1);
  }
  return buf[top];	
}

void push(char item)
{
  if(isfull()) {
	printf("Stack is full!!!\n");
	return;
  }
  top = top + 1;
  buf[top] = item;
}

char pull(void)
{
  char data;
  if(isempty()) {
	printf("Stack is empty!!!\n");
	exit(-1);
  }
  data = buf[top];
  top = top - 1;
  return data;	
}

void print(void)
{
 int i;
 if(isempty()) {
	printf("Stack is empty!!!\n");	
	return;
 }
 for(i = top;i >= 0;i--){
	printf("%c--->",buf[i]);
 }
}

int main()
{
 int choice;
 char data;
 while(1) {
 printf("------------------>MENU<------------------\n"); 
 printf("1.push  2.pull  3.peek  4.print  5.quit\n");
 printf("enter your choice:");
 scanf("%d",&choice);	
 switch(choice) 
 {
   case 1:printf("enter the element to be inserted :");
	  scanf(" %c",&data);
	  push(data);
	  break;
   case 2:data = pull();
	  printf("%c\n",data);	
	  break;
   case 3:data = peek();
	  printf("peek : %c\n",data);	
	  break;
   case 4:print();
	  break;
   case 5:exit(0);
   default:printf("Invalid choice !!!\n");
 } 	
 }
}
