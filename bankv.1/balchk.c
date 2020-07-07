#include"bank.h"

int balchk( int acc )
{
    int max ;
    int n = 1;
    FILE* fd ;
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

    while ( fread( &record ,sizeof(struct record), 1 , fd))
    {
        if ( n == acc )
        {
            printf("------------------------------------\n");
            printf("%d\n" , n );
            printf("%s\n" , record.name);
            printf("%d\n" , record.balance);
            printf("%s\n" , record.phno);
            printf("-------------------------------------\n");
            break ;
        }
        n++ ;
    }
    return SUCCESS ;
}

int main()
{
    int acc ;
    printf("\t\tWELCOME\n");
    printf("Enter your account number : ");
    scanf("%d", &acc );
    if ( balchk(acc) == FAILURE )
    {
        printf ( " Account number not found \n");
    }
}