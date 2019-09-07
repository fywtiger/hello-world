#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#ifndef Mylib
#define Mylib

#define MAX 255
#define SUCCESS 1
#define FAULT -1
#define TRUE 1
#define FALSE 0

typedef struct nList
{
    unsigned int no;
    unsigned int value;
    struct nList *next;
}DigitalList;

typedef struct msqTocsq
{
    char op[2];
    char stack[MAX];
    char out[MAX];
}mSQTOCQ;
struct ListNode
 {
    unsigned int val;
    struct ListNode *next;
 };
typedef int ElementType;
struct bitnode
{
	ElementType data;
	struct bitnode *left, *right;
};

typedef struct bitnode *bitree;

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
int PListPrint();
int scanf_s(const char *restrict format, ...);
void SecurityTest();
int postfix(char *infix,char *outPutCheck);
int priority(char op);
void SequenceToConsequent();
int debugPostfix(char* infix);
void debugPostfixPrintLine(char *op,char *stack,int stackStart,char *out,int outStart);
void debugPostfixPrintf(mSQTOCQ *PostfixList);
int ChangeDigitalList();
void PrintMap();
double evalPf(char* postfix);
double cal(double p1, char op, double p2);
void DelOnePointFromList();
int StringToDigitalNum(char *str,unsigned int *dOutList,int *dOutListNum);
void deleteNode(struct ListNode** node,unsigned int value);
struct ListNode* deleteNode2(struct ListNode* node,unsigned int value);
void findMedianSortedArraysPrint();
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);
int OutScanfDigitalNum(char *str,int *dOutList,int *dOutListLen);
int insertNumToList(int iNum,int *numList,int numListLen); 
 
struct bitnode* PerOrderCreateTree();
void PerOrderTravel(bitree T);
void InOrderTravel(bitree T);
void TailOrderTravel(bitree T);
bitree FreeTree(bitree T);
void PreTreeCreatAndOrder();
bitree InOrderCreateTree();

int leastInterval(char *tasks, int tasksSize, int n);
void sortTaskList(int *TaskList,int *taskListLen);
void taskRunTime();
int ChangeTaskListToSum(char *tasks,int tasksSize ,int *TaskSumList);

int findJudge(int N, int** trust, int trustSize, int* trustColSize);
#endif



