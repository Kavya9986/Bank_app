#include"bank.h"

int main(void)
{
    key_t key = ftok("sb_acc" , 'S');
    int semid;
    union semun arg;


    /* create a semaphore set with 1 semaphore: */
    if ((semid = semget( key , 1 , 0777 | IPC_CREAT)) == -1) 
    {
        perror("semget");
        exit(1);
    }
    /* initialize semaphore #0 to 1: */
    arg.val = 1;
    if (semctl(semid, 0 , SETVAL, arg) == -1) 
    {
        perror("SETVALUE");
        exit(2);
    }
    return 0;
}