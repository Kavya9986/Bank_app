#include"bank.h"

int deposit ( int acc , int amt)
{
    int max ;
    int n=1 ;
    int semid ;
    struct sembuf sembuf = { 0 , -1 , 0} ;
    FILE * fd ;          //     ^
    FILE * temp ;           //  |  
    /*sembuf.sem_num = 0 ;      |
    sembuf.sem_op = -1 ; -------|
    sembuf.sem_flg = SEM_UNDO;*/
    key_t key ;

    key = ftok("sb_acc" , 'S') ; // Setting key value

    // Get a semaphore from the system ( SYSTEM V VERSION )
    if ( semid = semget( key , 1 , 0777 | IPC_CREAT) == -1)
    {
        perror(" Cannot create a semaphore \n") ;
        exit(1);
    }

    // P operation ( SYSTEM V VERSION)
    if (semop( semid , &sembuf , 1 ) == -1)
    {
        perror("P OPERATION FAILED\n") ;
        exit(2);
    }
    printf(" P operation done successfully\n ");
    /*********************************************************************************************************/
    sleep(5);

    fd = fopen( "sb_acc" , "rw+");
    if ( fd == NULL )
    {
        return FILE_NOT_OPEN ;
    }

    fseek ( fd , 0 , SEEK_END);
    max = ftell(fd) / sizeof(record) ;
    if( acc > max)
    {
        return FAILURE ;
    }
    rewind(fd);

    temp = fopen( "tempo" , "w+");
    while ( fread( &record ,sizeof(struct record), 1 , fd))
    {
        if ( n == acc)
        {
            record.balance += amt ;
            fwrite (&record , sizeof(struct record) ,1, temp);
        }
        else
        {
            fwrite ( &record , sizeof(struct record) ,1, temp);
        }
        n++ ;
    }

    remove ( "sb_acc") ;
    rename ( "tempo" , "sb_acc");
    sembuf.sem_op = 1 ;
/*********************************************************************************************************/
// V operation ( SYSTEM V VERSION)
    if ( semop( semid , &sembuf , 1 ) == -1)
    {
        perror("V OPERATION FAILED\n");
        exit(3);
    }
    printf(" V operation done successfully\n ");

    return SUCCESS ;
}

int main()
{
    int acc ;
    int amt ;
    printf("\t\tWELCOME\n");
    printf("Enter your account number : ");
    scanf("%d", &acc );
    printf("Enter the amount : ");
    scanf("%d" , &amt);
    if (deposit( acc , amt) == SUCCESS )
    {
        printf ( "Deposited Successfully \n");
    }
    else if ( deposit( acc , amt) == FAILURE )
    {
        printf("Account number does not exist !\n");
    }
    else if (deposit( acc , amt) == FILE_NOT_OPEN)
    {
        printf("File open failed\n");
    }
    else
    {
        printf("Something went wrong \n");
    } 
}
