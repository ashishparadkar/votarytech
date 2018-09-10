#include<stdio.h>
#include<string.h>
#define PRINT_ERRMSG() fprintf(stderr,"Internal error: at %s"" ""line %d",__FILE__,__LINE__)
//#define debug() fputs(__FILE__ ":" __LINE__ " - ", stderr)
//#define debug() fprintf(stderr, "Internal error: "
 //                "negative string length "
  //               "%d at %s, line %d.",
   //      length, __FILE__, __LINE__);

int main()
{char buf[100];
 int a = 1;
// printf("%d\n",(__LINE__)-1);
// printf("");
if(a)
	PRINT_ERRMSG();
 // strcpy(buf,"client id : %s\n",itoa(getpid()));
printf("client id : %s\n",itoa(getpid()));
}
