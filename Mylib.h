#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#ifndef Mylib
#define Mylib

#define MAX 255
#define SUCCESS 1
#define FAULT 0
#define TRUE 1
#define FALSE 0
typedef struct msqTocsq
{
    char op[2];
    char stack[MAX];
    char out[MAX];
}mSQTOCQ;

int scanfDigitalNum(char *str);
int scanfDigitalString(char *str);
void TestCallback(int (*test)());
void TestCallback1(int (*test1)(),char *str);
int test();
int test1(char *str);
int TscanfDigital();
int Talgorithm();
void Free_Memory(char *str);
int scanfDigitalNumList(char *str);
int pListPrint();
int scanf_s(const char *restrict format, ...);
//errno_t memcpy_s(void * restrict dest, rsize_t destsz, const void * restrict src, rsize_t count);
//errno_t memset_s(void * dest, rsize_t destsz, int ch, rsize_t count);
//errno_t strcat_s(char * restrict dest, rsize_t destsz, const char * restrict src);
void SecurityTest();
int postfix(char *infix);
int priority(char op);
void SequenceToConsequent();
int debugPostfix(char* infix);
void debugPostfixPrintLine(char *op,char *stack,int stackStart,char *out,int outStart);
void debugPostfixPrintf(mSQTOCQ *PostfixList);
int ChangeDigitalList();
#endif


