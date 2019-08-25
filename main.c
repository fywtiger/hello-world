#include "Mylib.h"
int main(int argc, char const *argv[])
{    
    char OP[MAX];
    int i=0;
    //printf("sizeof(int) is %d\n",sizeof(int));
    PrintMap();
    while (TRUE)
    {
        if(0!=i)
        {
            printf("\n");
        }
        printf("Please input a Number of Function Map:");
        i=1;
        scanf("%s",OP);        
        switch(OP[0])
        {
            case '1':
                TscanfDigital();
                break;
            case '2':
                TestCallback(test);
                TestCallback1(test1,"1234\n");
                break;
            case '3':
                PListPrint();
                break;
            case '4':
                ChangeDigitalList();
                break;
            case '5':
                SequenceToConsequent();
                break;
            case 'q':
                printf("Bye! Quit main function.\n");
                return SUCCESS;
            default:
                printf("\ninput Number is error!\n");
                return FAULT;
        }/* code */
    }    
    return SUCCESS;
}

void PrintMap()
{
    printf("Wellcome! This is a function map:\n");
    printf("  NO       Function Name           Action            \n");
    printf("   1       TscanfDigital           Print out the number in the input string!\n");
    printf("   2       TestCallback            Test callback function!\n");
    printf("   3       PListPrint              Use list to print out the number in the input string!\n");
    printf("   4       ChangeDigitalList       Print numbers in a pyramid!\n");
    printf("   5       SequenceToConsequent    Converting an intermediate input to a sequential input!\n");
    printf("   q       Quitmain                Quit main Function!\n");
    return;
}

