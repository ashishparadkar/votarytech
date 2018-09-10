#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int i,j;
    char buf[100];
    char *ptr=NULL;
    char t1[10];
    int a,b,c;
    scanf("%s",buf);
    ptr=buf;
    
    for(j = 3; j > 0; j--)
	{
	 t1[0] = '\0';
	 if(j > 0 && *ptr == '\0') 
          {
            printf("Invalid input\nUSE : <num1>,<num2>,<num3>\n");
            exit(1);
	  }
	 for(i = 0;(*ptr != ',') && (*ptr);i++,ptr++)
    	  {
        	t1[i] = *ptr;
    	  }
        t1[i]='\0';
		if(j == 3) a = atoi(t1);
        else if(j == 2) b = atoi(t1);
        else if(j == 1) c = atoi(t1);
        
        ptr++;
        }
    printf("%d %d %d\n",a,b,c); 
    if(a >= b && a>=c) 
        printf("%d\n",a);
    else if(b >= c && b >=a)
        printf("%d\n",b);
    else
        printf("%d\n",c);
    
    return 0;
}
