#include "Mylib.h"


void TestCallback(int (*test)())
{
    test();
    return;
}

int test()
{
    printf("callback test \n");
    return SUCCESS;
}

void TestCallback1(int (*test1)(),char *str)
{
    test1(str);
    return;
}

int test1(char *str)
{
    if(NULL == str)
    {
        return FAULT;
    }
    printf("callback test1:%s \n",str);
    return SUCCESS;
}