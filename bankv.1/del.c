#include"bank.h"

int main()
{
    union semun arg;
    semctl ( 163840  , 0, IPC_RMID , arg);
    semctl ( 32769, 0, IPC_RMID , arg);
    //semctl ( 65538, 0, IPC_RMID , arg);
    //semctl ( 98307, 0, IPC_RMID , arg);
}
