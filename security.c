#include "Mylib.h"

void SecurityTest()
{
    #if 0
    char strBuf[10]={0};
    
    printf("strcat_s overflow error:%d\n",strcat(strBuf,"0123456789qwe"));
    printf("strBuf is %s\n",strBuf);

    printf("strcat_s Be equal to error:%d\n",strcat(strBuf,"0123456789"));
    printf("strBuf is %s\n",strBuf);

    printf("strcat_s less error:%d\n",strcat(strBuf,"01234567"));
    printf("strBuf is %s\n",strBuf);

    //printf("sizeof(strBuf) is %d, sizeof(char) is %d \n",sizeof(strBuf),sizeof(char));
    #endif
    return;
}