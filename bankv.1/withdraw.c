#include"bank.h"

int withdraw ( int acc , int amt)
{
    int max ;
    int n=1 ;
    int num = 1 ;
    key_t key ;
    int semid ;
    struct sembuf sembuf = { 0 , -1 , 0} ;
    FILE * fd ;
    FILE * temp ;

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
    rewind(fd);

    if( acc > max)
    {
        return FAILURE ;
    }

    while (fread( &record , sizeof( struct record) , 1 , fd))
    {
        if ( n == acc)
        {
            if( amt > record.balance || record.balance <= 0)
            {
                return INSUF_AMT ;
            }
            break ;
        }
        n++ ;
    }

    temp = fopen( "tempo" , "w+");
    if (temp == NULL)
    {
        return FILE_NOT_OPEN ;
    }
    rewind(fd);
    
    while (fread( &record , sizeof(struct record) , 1 , fd))
    {
        if ( num == acc)
        {
            record.balance -= amt ;
            fwrite ( &record , sizeof( struct record) , 1 , temp);    
        }
        else
        {
            fwrite ( &record , sizeof( struct record) , 1 , temp) ;
        }
        num ++ ;    
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
    if (withdraw( acc , amt) == SUCCESS )
    {
        printf ( "Withdrawn Successfully \n");
    }
    else if ( withdraw( acc , amt ) == FAILURE)
    {
        printf("Account number does not exist !\n");
    }
    else if ( withdraw( acc , amt ) == INSUF_AMT )
    {
        printf(" Insufficient amount in your account \n");
    }
    else if ( withdraw( acc , amt ) == FILE_NOT_OPEN)
    {
        printf("File open failed\n");
    }
    else
    {
        printf("Something went wrong \n");
    }
    
    
    
}