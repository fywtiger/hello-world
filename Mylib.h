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
} DigitalList;

typedef struct msqTocsq
{
    char op[2];
    char stack[MAX];
    char out[MAX];
} mSQTOCQ;
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

#define MAX_PEOPLE 1100
typedef struct node
{
    int height;
    int sortSite[MAX_PEOPLE];
} NODE_PEOPLE;
struct nodeList
{
    int height;
    int site;
    struct nodeList *next;
};
typedef struct nodeList *NODE_LIST;
struct resultList
{
    int count;
    int value;
};
typedef struct resultList Result_List;
//add 1162 地图分析
struct ocean
{
    int x;
    int y;
    struct ocean *next;
};
typedef struct ocean OCEAN;
struct land
{
    int x;
    int y;
    struct land *next;
};
typedef struct land LAND;
//end add 1162 地图分析
int scanfDigitalNum(char *str);
int scanfDigitalString(char *str);
void TestCallback(int (*test)());
void TestCallback1(int (*test1)(), char *str);
int test();
int test1(char *str);
int TscanfDigital();
int Talgorithm();
void Free_Memory(char *str);
int scanfDigitalNumList(char *str);
int PListPrint();
int scanf_s(const char *restrict format, ...);
void SecurityTest();
int postfix(char *infix, char *outPutCheck);
int priority(char op);
void SequenceToConsequent();
int debugPostfix(char *infix);
void debugPostfixPrintLine(char *op, char *stack, int stackStart, char *out, int outStart);
void debugPostfixPrintf(mSQTOCQ *PostfixList);
int ChangeDigitalList();
void PrintMap();
double evalPf(char *postfix);
double cal(double p1, char op, double p2);
void DelOnePointFromList();
int StringToDigitalNum(char *str, unsigned int *dOutList, int *dOutListNum);
void deleteNode(struct ListNode **node, unsigned int value);
struct ListNode *deleteNode2(struct ListNode *node, unsigned int value);
void findMedianSortedArraysPrint();
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size);
int OutScanfDigitalNum(char *str, int *dOutList, int *dOutListLen);
int insertNumToList(int iNum, int *numList, int numListLen);

struct bitnode *PerOrderCreateTree();
void PerOrderTravel(bitree T);
void InOrderTravel(bitree T);
void TailOrderTravel(bitree T);
bitree FreeTree(bitree T);
void PreTreeCreatAndOrder();
bitree InOrderCreateTree();

int leastInterval(char *tasks, int tasksSize, int n);
void sortTaskList(int *TaskList, int *taskListLen);
void taskRunTime();
int ChangeTaskListToSum(char *tasks, int tasksSize, int *TaskSumList);

int findJudge(int N, int **trust, int trustSize, int *trustColSize);

int movesToMakeZigzag(int *nums, int numsSize);
int TwoNumbers(int *nums);
int MoreThreeNumbers(int *nums, int numsSize);

NODE_PEOPLE *SortQueueList(int **people, int peopleSize, int *nodeListLen);
void printList(NODE_LIST head);
NODE_LIST insertNodeList(int nodeListLen, NODE_PEOPLE *peopleList);
int **reconstructQueue1(int **people, int peopleSize, int *peopleColSize, int *returnSize, int **returnColumnSizes);
int **SortQueueList1(int **people, int peopleSize, int *peopleColSize);
NODE_LIST insertNodeList1(int **SortPeople, int peopleSize);
int insertOneToResultList(Result_List *resultList, int value, int listLen);
int queryMaxCountFromList(Result_List *resultList, int listLen);

void skillPrint();
unsigned int skill(unsigned int elem_num, unsigned int slot_num);

int subarraysWithKDistinct(int* A, int ASize, int K);
int checkArray(int* A,int K,int startSite,int ASize,int *resultArray,int *overFlag,int fillValue);

void splitArray(unsigned int leftValue,unsigned int rightValue,unsigned int value,int deept,unsigned int **node,unsigned int *result);
void printfSplitNode(unsigned int *node, int len);
void printfSplitNodeArray(unsigned int **node, int len, int arrayLine);
unsigned int getSplitArrayResult(unsigned int leftValue,unsigned int rightValue,unsigned int value);
int compareNode(unsigned int **node, int len,int compareLift,int compareRight);
#endif
