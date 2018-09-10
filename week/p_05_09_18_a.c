#include<stdio.h>
#include<string.h>

int main()
{
char buf[BUFSIZ];
int i,cnt = 1;
printf("Enter a string :\n");
fgets(buf,BUFSIZ,stdin);
buf[strlen(buf) - 1] = '\0';

for(i=0;buf[i];i++) {
if(cnt == 1) {
	if(buf[i] == 32) {
		cnt = 0;
		continue;
	}
	else {
		buf[i] -= 32;
	}
}
else if(cnt == 0){
	if(buf[i] == 32) {
		cnt = 1;
		continue;
	}
	
	if(*((buf + i) - 1) == 32){
		buf[i] -= 32;
	}
	else {
		continue;
	}
		
}
}

printf("%s\n",buf);
}
