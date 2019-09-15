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
/**********************************************************************
 * 函数功能：将中序的算式转换为一个前序的算式，并输出前序算式的结果以及每步变换的过程，
 * 然后再讲转换后的前序式的计算机计算过程和结果打印出来
 * 作   者：范亚伟
 * 示   例:
please input infix:
(8*7-6/3)/2+(2*4+6)/7
Get out postfix:
87*63/-2/24*6+7/+                                       
OP    STACK  OUT
  (     (      NULL
  8     (      8
  *     *(     8
  7     *(     87
  -     -(     87*
  6     -(     87*6
  /     /-(    87*6
  3     /-(    87*63
  )     NULL   87*63/-
  /     /      87*63/-
  2     /      87*63/-2
  +     +      87*63/-2/
  (     (+     87*63/-2/
  2     (+     87*63/-2/2
  *     *(+    87*63/-2/2
  4     *(+    87*63/-2/24
  +     +(+    87*63/-2/24*
  6     +(+    87*63/-2/24*6
  )     +      87*63/-2/24*6+
  /     /+     87*63/-2/24*6+
  7     /+     87*63/-2/24*6+7
  NULL  NULL   87*63/-2/24*6+7/+

stack[2]:7.000000 stack[1]:8.000000 new stack[1]:56.000000
stack[3]:3.000000 stack[2]:6.000000 new stack[2]:2.000000
stack[2]:2.000000 stack[1]:56.000000 new stack[1]:54.000000
stack[2]:2.000000 stack[1]:54.000000 new stack[1]:27.000000
stack[3]:4.000000 stack[2]:2.000000 new stack[2]:8.000000
stack[3]:6.000000 stack[2]:8.000000 new stack[2]:14.000000
stack[3]:7.000000 stack[2]:14.000000 new stack[2]:2.000000
stack[2]:2.000000 stack[1]:27.000000 new stack[1]:29.000000
postfix:"87*63/-2/24*6+7/+" Calculation result is 29.000000,
**********************************************************************/
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
/**********************************************************************
运算时由后序式的前方开始读取，遇到运算元先存入堆叠，如果遇到运算子，则由堆叠中取出两个运算元进行对应的运算，
然后将结果存回堆叠，如果运算式读取完毕，那么堆叠顶的值就是答案了， 例如我们计算
12+34+*这个运算式（也就是(1+2)*(3+4)）： 读取堆叠
op  stack
1   1
2   2 1
+   3 // 1+2 后存回
3   3 3
4   4 3 3
+   7 3 // 3+4 后存回
*   21 // 3 * 7 后存回
**********************************************************************/
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
    return FAULT;
}

/**********************************************************************
二叉树的创建，遍历。输入：1,2,3,4,0,5,6,7,8,9,0,0,0,0,0,0,0,10,0,0
Check the PreTree in the following order:1 2 3 4 5 6 7 8 9 10
Check the InOrderTree in the following order:4 7 9 8 6 5 3 2 1 10
Check the TailOrderTree in the following order:9 8 7 6 5 4 3 2 10 1
树形
                                        1
                                       /  \
                                      2    10
                                     / \    |  \
                                    3 NULL NULL NULL
                                   / \
                                  4  NULL
                                 / \
                              NULL  5
                                   / \
                                  6  NULL
                                 / \
                                7   NULL
                               / \
                            NULL  8
                                 / \
                                9  NULL
                               / \
                            NULL  NULL           
**********************************************************************/
//先序创建一棵二叉树  
bitree PerOrderCreateTree()
{
    bitree T; 
    ElementType item;
	scanf("%d",&item);
	if( item == 0 )              //叶节点数据标志：其后根两个0 
	    T = NULL;            //若某一节点为叶子结点，则其左右子树均为NULL，0表示建空树
	else
	{
		T = (struct bitnode*)malloc(sizeof(struct bitnode));
		T->data = item;
		T->left = PerOrderCreateTree();             //递归创建其左子树 
		T->right = PerOrderCreateTree();            //递归创建其右子树 
	} 	
	return T;
}

//中序创建一棵二叉树  
bitree InOrderCreateTree()
{
    bitree T; 
    ElementType item;
	scanf("%d",&item);
	if( item == 0 )              //叶节点数据标志：其后根两个0 
	    T = NULL;            //若某一节点为叶子结点，则其左右子树均为NULL，0表示建空树
	else
	{
		T = (struct bitnode*)malloc(sizeof(struct bitnode));		
		T->left = InOrderCreateTree();             //递归创建其左子树         
        T->data = item;
		T->right = InOrderCreateTree();            //递归创建其右子树 
	} 	
	return T;
}

//后序创建一棵二叉树  
bitree TailOrderCreateTree()
{
    bitree T; 
    ElementType item;
	scanf("%d",&item);
	if( item == 0 )              //叶节点数据标志：其后根两个0 
	    T = NULL;            //若某一节点为叶子结点，则其左右子树均为NULL，0表示建空树
	else
	{
		T = (struct bitnode*)malloc(sizeof(struct bitnode));		
		T->left = TailOrderCreateTree();             //递归创建其左子树         
		T->right = TailOrderCreateTree();            //递归创建其右子树 
        T->data = item;
	} 	
	return T;
}

//先序递归周游二叉树
void PerOrderTravel(bitree T)
{
	if( NULL!=T )            // T != NULL 
	{
		printf("%d ",T->data);
		PerOrderTravel(T->left);            //递归先序周游其左子树 
		PerOrderTravel(T->right);           //递归先序周游其右子树 
	}
} 

/**中序遍历 左根右**/
void InOrderTravel(bitree T)
{
    if(T==NULL)
        return;
    InOrderTravel(T->left);
    printf("%d ",T->data);
    InOrderTravel(T->right);
}
 
/**后序遍历 左右根**/
void TailOrderTravel(bitree T)
{
    if(T==NULL)
        return;
    TailOrderTravel(T->left);
    TailOrderTravel(T->right);
    printf("%d ",T->data);
} 
//释放空间
bitree FreeTree(bitree T)
{
	if( NULL!=T )
	{
		FreeTree(T->left);            //递归释放其左子树 
		FreeTree(T->right);           //递归释放其右子树 
		free(T);                      //释放根节点 
		T = NULL;                     //释放指向根节点的指针 
	}
	
	return T;           //返回释放后的根节点NULL 
} 


void PreTreeCreatAndOrder()
{
	bitree root;	
	//printf("Please input a number to Create PreTree:");
	//root = PerOrderCreateTree();               //先序创建一棵二叉树 	
    printf("Please input a number to Create InOrderTree:");
    root = InOrderCreateTree();    

    printf("\n");
	printf("Check the PreTree in the following order:"); 
	PerOrderTravel(root);             //先序周游 	

    printf("\n");
    printf("Check the InOrderTree in the following order:"); 
    InOrderTravel(root);

    printf("\n");
    printf("Check the TailOrderTree in the following order:"); 
    TailOrderTravel(root);

    FreeTree(root);
	return ;
}
/***************************************************************************************************************
 假设卡尔能召唤n种元素，并且身上同时能挂m个元素，则卡尔最多能搓出多少个技能？比如能够召唤1/2/3三种元素，能够挂最多3个元素，
 则能够最多使用10中技能：1/1/1 1/1/2 1/1/3  1/2/2 1/2/3 2/2/2 2/2/3 3/3/1 3/3/2 3/3/3,内容相同顺序不同认为是一种技能
 **************************************************************************************************************/
unsigned int skill(unsigned int elem_num, unsigned int slot_num)
{
    unsigned int skill_num = 0;
    int elem_i_slot_num = 0;

    if (elem_num == 0)
    {
        return 0; //如果卡尔连一种元素都召唤不来，自然搓不出任何技能
    }
    else if (elem_num == 1)
    {
        return 1; //当只能召唤一种元素时，卡尔身上就算同时能挂m个元素，也只能搓出一种技能
    }

    if (slot_num == 0)
    {
        return 1; //当代码运行到此处时，说明卡尔还能召唤1种以上的技能，但此时他身上已经挂满了元素，所以能搓出的技能已经是固定的一种
    }
    else if (slot_num == 1)
    {
        return elem_num; //当卡尔身上只能挂一个元素时，就算能召唤k种元素，也只能搓出k种技能
    }
    //分情况讨论：
    //如果已知第i种元素占0个槽位，则卡尔能搓出技能f(k,m)等于f(k-1, m)；
    //如果已知第i种元素占1个槽位，则卡尔能搓出的技能f(k,m)等于f(k-1, m-1)，
    //以此类推，将第i种元素的所有可能槽位占据情况累加起来，就得到了卡尔所有能搓出的技能，
    //又因为技能跟元素排列顺序无关，所以总技能数就是
    //f(k,m) = f(k-1, m) + f(k-1, m-1) + ... + f(k-1, 0)
    for (elem_i_slot_num = 0; elem_i_slot_num <= slot_num; elem_i_slot_num++)
    {
        skill_num += skill(elem_num - 1, slot_num - elem_i_slot_num);
    }
    return skill_num;
}

void skillPrint()
{
    unsigned int element;
    unsigned int slot;
    unsigned int skill_num;

    printf("Please input Dota element number:");
    scanf("%d", &element);
    printf("Please input slot number:");
    scanf("%d", &slot);

    skill_num = skill(element,slot);
    printf("The skill number is %ld \n",skill_num);
    return;
}
