#include<stdio.h>
#include<stdlib.h>
typedef struct stack{
	char data;
	struct stack *next;
}node;

node *head = NULL;

int isempty(void)
{
  if(head == NULL) 
	return 1;
  else
	return 0;
}

void push(char item)
{
 node *new = NULL;
 new = malloc(sizeof(node)); 
 if(new == NULL) { 
	printf("Stack is full!!!\n");
	return;
 }
 new->data = item; 
 new->next = head;
 head =  new;
}

char pop(void)
{
  
  char item;
  node *temp;
  if(isempty()) {
	printf("Stack is empty!!!\n");
	exit(-1);
  }
  item = head->data;
  temp = head;
  head = head->next;
  temp->next = NULL;
  free(temp);		
  return item;	
}

int compare(char a,char b)
{
 if(a == '{' && b == '}')
	return 1;
 if(a == '(' && b == ')')
 	return 1;
 return 0;
}

int process(char *test,int size)
{
 char item;
 int i;
 for(i = 0;i < size;i++)
 {
     if((test[i] == '{') || (test[i] == '('))
	push(test[i]);
     if((test[i] == '}') || (test[i] == ')'))
	{
		if(head == NULL) {
			return 0;
		}
		else {
			item = pop();		
			if(compare(item,test[i]))
				continue;
			else 
			  	return 0;
		}
	}	
 }

 if(head == NULL) {
	return 1;		
 }
 else {
	return 0;
 }
}

int main()
{
 int valid;
 char test1[] = {'{','(',')','(',')','}'};
 char test2[] = {'{','(',')','(',')','}',')'};	
 
 valid =  process(test1,sizeof(test1));
 if(valid)
 	printf("test1 valid\n");
 else
	printf("test1 Invalid\n");

 valid =  process(test2,sizeof(test2));
 if(valid)
 	printf("test2 valid\n");
 else
	printf("test2 Invalid\n");
 
 return 0;
}
