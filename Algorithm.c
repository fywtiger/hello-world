#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "Mylib.h"


int Talgorithm()
{
    unsigned int number;
    unsigned int *numList = NULL;
    int i = 0;
    printf("Please input the total number:");
    scanf("%d",&number);
    numList = malloc(sizeof(unsigned int)*number);
    if(NULL == numList)
    {
        printf("Malloc memory is NULL!\n");
        return FAULT;
    }
    
    *numList = 0;
    *(numList+1) = 1;
    for(i=2;i<number;i++)
    {
        *(numList+i) = *(numList+i-1) + *(numList+i-2);
        if(*(numList+i)<*(numList+i-1))
        {
            printf("call numList[%d]:%d 0x%X\n",i,*(numList+i-1),*(numList+i-1));
            number=i;
            break;
        }
    }
    printf("The number list[%d] is:\n",number-1);
    for(i=0;i<number;i++)
    {
        printf("number list[%d]:%u 0x%X \n",i,*(numList+i),*(numList+i));
    }
    free(numList);
    numList = NULL;

    return SUCCESS;
}

void SequenceToConsequent()
{
    int i=0,j=0;    
    char input[MAX]={0};  
    char inputCheck[MAX]={0};  
    char outPutCheck[MAX];
    printf("please input infix: \n");
    scanf("%s",input);
    //printf("input is %s\n",input);
    while('\0'!=input[i])
    {
        switch(input[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
                inputCheck[j]=input[i];                
                i++;
                j++;
                break;
            case ' ':               
                i++;
                break;
            default:
                printf("input position[%d]:%c is Unreasonable Character!\n",i+1,input[i]);
                return;
        }        
    }
    inputCheck[j]='\0';
    printf("Get out postfix:\n");
    postfix(inputCheck,outPutCheck);    
    printf("\n");
    debugPostfix(inputCheck);
    printf("\n");
    printf("postfix:%c%s%c Calculation result is %lf,\n",'"',outPutCheck,'"',evalPf(outPutCheck));
    return;
}

int postfix(char* infix,char* outPutCheck)
{
    int i = 0, top = 0, j = 0;
    char stack[80] = {'\0'};
    char op;
    if(NULL == infix||NULL == outPutCheck)
    {
        printf("postfix input point is error!");
        return FAULT;
    }
    while(TRUE && j<MAX)
    {
        op = infix[i];
        switch(op)
        {
            case '\0':
                while(top > 0)
                {
                    printf("%c", stack[top]);
                    outPutCheck[j++] = stack[top];
                    top--;
                }
                printf("\n");
                outPutCheck[j]='\0';
                return SUCCESS;
            case '(':
                if(top < (sizeof(stack) / sizeof(char)))
                {
                    top++;
                    stack[top] = op; 
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while(priority(stack[top]) >= priority(op))
                {
                    printf("%c", stack[top]);
                    outPutCheck[j++] = stack[top];                    
                    top--;
                }
                if(top < (sizeof(stack) / sizeof(char)))
                {
                    top++;
                    stack[top] = op;                    
                }
                break;
            case ')':
                while(stack[top] != '(')
                {
                    printf("%c", stack[top]);
                    outPutCheck[j++] = stack[top];
                    top--;
                }
                top--;
                break;
            default:
                printf("%c", op);
                outPutCheck[j++] = op;                
                break;
        }
        i++;
    }
    return FAULT;
}

int debugPostfix(char* infix)
{
    int i = 0, top = 0, len = 0, sLen = 0;
    int pOut=0;
    char stack[MAX] = {'\0'};
    char op;
    
    mSQTOCQ mSqToCqList[MAX];

    memset(&mSqToCqList[0],'\0',sizeof(mSQTOCQ)*MAX);

    while(TRUE)
    {
        op = infix[i];
        mSqToCqList[i].op[0] = op;
        //printf("0mSqToCqList[%d].op is %s\n",i, &mSqToCqList[i].op);
        switch(op)
        {
            case '\0':
                while(top > 0)
                {
                    //printf("%c\n", stack[top]);
                    if(0==i)
                    {
                        mSqToCqList[i].out[0] = stack[top];                        
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out); 
                        //pOut++;    
                    }
                    else
                    {
                        if(0 == pOut)
                        {
                            len = strlen(&mSqToCqList[i-1].out[0]);
                            memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);
                        }
                        mSqToCqList[i].out[len+pOut]=stack[top];                           
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out);     
                        pOut++;              
                    }
                    //printf("0stack[%d]:%c\n", top,stack[top]);
                    top--;
                    sLen = top;
                    while(0!=sLen)
                    {
                        mSqToCqList[i].stack[top-sLen]=stack[sLen];
                        sLen--;
                    }
                    mSqToCqList[i].stack[top]='\0';
                }
                pOut = 0;
                mSqToCqList[i].op[0] = ' ';                
                debugPostfixPrintf(&mSqToCqList[0]);
                return 0;
            case '(':
                if(top < (sizeof(stack) / sizeof(char)))
                {
                    top++;
                    stack[top] = op;
                    sLen = top;
                    while(0!=sLen)
                    {
                        mSqToCqList[i].stack[top-sLen]=stack[sLen];
                        sLen--;
                    }
                    mSqToCqList[i].stack[top]='\0';
                    if(0!=i)                    
                    {
                        len = strlen(&mSqToCqList[i-1].out[0]);
                        memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);                        
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out);  
                        //pOut++;                
                    }
                    //增加调测代码
                    //printf("1stack[%d]:%c\n",top,op);
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while(priority(stack[top]) >= priority(op))
                {
                    //printf("%c\n", stack[top]);
                    if(0==i)
                    {
                        //mSqToCqList[i].out[0] = stack[top];
                        printf("input digital list is error!\n");   
                        //pOut++;  
                    }
                    else
                    {
                        if(0 == pOut)
                        {
                            len = strlen(&mSqToCqList[i-1].out[0]);
                            memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);
                        }
                        mSqToCqList[i].out[len+pOut]=stack[top];                           
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out);     
                        pOut++;  
                                  
                    }
                    //printf("2stack[%d]:%c\n", top,stack[top]);
                    top--;
                    sLen = top;
                    while(0!=sLen)
                    {
                        mSqToCqList[i].stack[top-sLen]=stack[sLen];
                        sLen--;
                    }
                    mSqToCqList[i].stack[top]='\0';
                }
                if(top < (sizeof(stack) / sizeof(char)))
                {
                    top++;
                    stack[top] = op;
                    sLen = top;
                    while(0!=sLen)
                    {
                        mSqToCqList[i].stack[top-sLen]=stack[sLen];
                        sLen--;
                    }
                    mSqToCqList[i].stack[top]='\0';
                    if(0!=i)
                    {
                        len = strlen(&mSqToCqList[i-1].out[0]);
                        memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);                      
                                       
                    }
                    //增加调测代码
                    //printf("3stack[%d]:%c\n", top,op);
                }
                pOut =0;                
                break;
            case ')':
                while(stack[top] != '(')
                {
                    //printf("%c\n", stack[top]);
                    //printf("4stack[%d]:%c\n", top,stack[top]);
                    if(0==i)
                    {
                        mSqToCqList[i].out[0] = stack[top];                        
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out); 
                        //pOut++;    
                    }
                    else
                    {
                        if(0 == pOut)
                        {
                            len = strlen(&mSqToCqList[i-1].out[0]);
                            memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);
                        }
                        mSqToCqList[i].out[len+pOut]=stack[top];                           
                        //printf("out[%d] is %s\n",i,mSqToCqList[i].out);     
                        pOut++;              
                    }
                    top--;
                }
                top--;
                sLen = top;
                pOut = 0;
                while(0!=sLen)
                {
                    mSqToCqList[i].stack[top-sLen]=stack[sLen];
                    sLen--;
                }
                mSqToCqList[i].stack[top]='\0';
                break;
            default:
                //printf("->%c\n", op);
                if(0==i)
                {
                    mSqToCqList[i].out[0] = op;                    
                    //printf("out[%d] is %s\n",i,mSqToCqList[i].out);    
                    //pOut++;
                }
                else
                {
                    len = strlen(&mSqToCqList[i-1].out[0]);
                    memcpy(&mSqToCqList[i].out[0],&mSqToCqList[i-1].out[0],len);
                    mSqToCqList[i].out[len]=op;                    
                    len = strlen(&mSqToCqList[i-1].stack[0]);
                    memcpy(&mSqToCqList[i].stack[0],&mSqToCqList[i-1].stack[0],len);
                    //pOut++;                
                }                                
                break;
        }
        i++;
    }
}

int priority(char op)
{
    int p;
    
    switch(op)
    {
        case '+':
        case '-':
            p = 1;
            break;
        case '*':
        case '/':
            p = 2;
            break;
        default:
            p = 0;
            break;
    }
    return p;
}

void debugPostfixPrintf(mSQTOCQ *PostfixList)
{
    char *op="OP";
    char *stack="STACK";
    char *out="OUT";
    int i=0,stackMaxLen=0;
    int stackStart = 0, outStart = 0;
    if(NULL == PostfixList)
    {
        printf("debugPostfixPrintf input point is null!\n");
        return;
    }

    while('\0'!=PostfixList[i].op[0] && i<MAX)
    {
        if(strlen(&PostfixList[i].stack[0])>stackMaxLen)
        {
            stackMaxLen = strlen(&PostfixList[i].stack[0]);
        } 
        i++;
    }
    //printf("loop i is %d\n",i);
    i=0;        
    
    if(stackMaxLen<strlen(stack))
    {
        stackMaxLen = strlen(stack);
    }

    stackStart = 8;
    outStart = 10 + stackMaxLen;
    printf("\n");
    debugPostfixPrintLine(op,stack,stackStart,out,outStart);
    printf("\n");    
    while('\0'!=PostfixList[i].op[0] && i<MAX)
    {
        debugPostfixPrintLine(PostfixList[i].op,PostfixList[i].stack,stackStart,PostfixList[i].out,outStart);
        i++;
        printf("\n");        
    }
    
    return;
}

void debugPostfixPrintLine(char *op,char *stack,int stackStart,char *out,int outStart)
{
    int i=0;
    if(NULL==op || NULL==stack || NULL==out)
    {
        printf("debugPostfixPrintLine input point is NULL\n");
        return;
    }

    while(i <= outStart)
    {
        if(2 == i)
        {
            if(' ' == *op)
            {
                printf("NULL");
                i=i+4;
            }
            else
            {
                printf("%s",op);
                i=i+strlen(op); 
            }
            
        }
        else if(stackStart == i)
        {
            if('\0' == *stack)
            {
                printf("NULL");
                i=i+4;
            }
            else
            {
                printf("%s",stack);
                i=i+strlen(stack); 
            }
            
        }
        else if(outStart == i)
        {
            if('\0' == *out)
            {
                printf("NULL");
                i=i+4;
            }
            else
            {
                printf("%s",out);
                i=i+strlen(out);  
            }            
        }        
        else
        {
            printf(" "); 
            i++;     
        }            
    }    
    return;
}

double evalPf(char* postfix) 
{
    double stack[80] = {0.0};
    char temp[2];
    char token;
    int top = 0, i = 0;
    temp[1] = '\0';
    while(TRUE) 
    {
        token = postfix[i];
        switch(token) 
        {
            case '\0':
                //printf("ans = %f\n", stack[top]);
                return stack[top];
            case '+': 
            case '-': 
            case '*': 
            case '/':
                printf("stack[%d]:%lf stack[%d]:%lf new stack[%d]:%lf\n",top,stack[top],top-1,stack[top-1],top-1,cal(stack[top], token, stack[top-1]));
                stack[top-1] =
                cal(stack[top], token, stack[top-1]);
                
                top--;
                break;
            default:
                if(top < sizeof(stack) / sizeof(float)) 
                {
                    temp[0] = postfix[i];
                    top++;
                    stack[top] = atof(temp);
                }
            break;
        }
        i++;
    }
}
double cal(double p1, char op, double p2) 
{
	switch(op) 
	{
		case '+':            
		    return p1 + p2;
		case '-':
		    return p2 - p1;
		case '*':
		    return p1 * p2;
		case '/':
		    return p2 / p1;
	}    
}
