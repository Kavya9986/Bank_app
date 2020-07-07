#include"bank.h"

int main()
{
    int semid ;
    union semun arg;
    key_t key = ftok("sb_acc" , 'S');

    if ((semid = semget( key, 1 , 0777 | IPC_CREAT)) == -1) 
    {
        perror("semget");
        exit(1);
    }

    if (semctl ( semid, 0, IPC_RMID , arg) == -1) 
    {
        perror ("semctl IPC_RMID");
        exit (2);
    }

    return 0 ;
}