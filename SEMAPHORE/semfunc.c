#include "semun.h"
static int set_semvalue(void)
{
 union semun sem_union;
 sem_union.val = 1;
 if(semctl(sem_id,0,SETVAL,sem_union) == -1) return (0);
 return (1);
}

static void del_semvalue(void)
{
 union semun sem_union;
 if(semctl(sem_id,0,IPC_RMID,sem_union) == -1) 
	fprintf(stderr,"Failed to delete semaphore\n");
}

static int semaphore_p(void)
{
 struct sembuf sem_b;
 
 sem_b.sem_num = 0;
 sem_b.sem_op
}
