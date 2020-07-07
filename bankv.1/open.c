#include"bank.h"
int open_acc( char* name , char* phno)
{
    int acc_no;
    FILE* fd ;
    fd = fopen ( "sb_acc" , "rw+");
    fseek ( fd , 0 , SEEK_END);
    acc_no = ftell(fd) / sizeof(record) ;
    strcpy ( record.name , name );
    strcpy ( record.phno , phno );
    record.balance = 0 ;
    fwrite ( &record ,  sizeof(record) , 1 , fd);
    fclose(fd);
    return ( acc_no + 1 );
}

int main()
{
    char name[12];
    char phno[10];
    printf("\t\tWELCOME\n");
    printf("Enter your name : ");
    scanf("%s" , name);
    printf("Enter your contact number : ");
    scanf("%s" , phno);
    printf ("%d\n" , open_acc( name , phno));
}
