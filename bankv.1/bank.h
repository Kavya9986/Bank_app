#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/file.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdlib.h>
#define SUCCESS 0
#define FAILURE 1
#define INSUF_AMT 2
#define FILE_NOT_OPEN 3


union semun
{
    int val; /* used for SETVAL only */
    struct semid_ds *buf; /* for IPC_STAT and IPC_SET */
    ushort *array; /* used for GETALL and SETALL */
};
struct record
{
    char name[12];
    char phno[10];
    int balance ;
};
struct record record ;

int open_acc ( char* name , char* phno);
int deposit ( int acc , int amt);
int withdraw ( int acc , int amt);
