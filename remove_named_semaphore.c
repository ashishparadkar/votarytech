#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>

#include<pthread.h>

int main()
{
 sem_unlink("/sync1");
 sem_unlink("/sync2");
 sem_unlink("/sync3");
 exit(0);
}
