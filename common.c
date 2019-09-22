#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void Free_Memory(char *str)
{
	if (NULL == str)
	{
		printf("Free_Memory Error!\n");
		return;
	}
	free(str);
	str = NULL;
	return;
}
#if 0

int main()
{	
    unsigned int input=0;
	unsigned int result=0;
	unsigned int printResult=0;
	unsigned int **resultArray=NULL;
	int i=0;
	while (1)
	{		
		result=0;
		printResult =0;
		printf("please input a digital number:");
		scanf("%d", &input);	
		//splitArray(input,1,input,0,node,&result);
		result = getSplitArrayResult(input,1,input);
		result++;
		printf("result is %d\n", result);

		resultArray = malloc(sizeof(unsigned int *)*result);
		for(i=0;i<result;i++)
		{
			resultArray[i] = malloc(sizeof(unsigned int)*input);
			memset(resultArray[i],0,sizeof(unsigned int)*input);
		}
		resultArray[0][input-1]=0;
		resultArray[0][input-2]=input;
		
		splitArray(input,1,input,0,resultArray,&printResult);
		printfSplitNodeArray(resultArray,input,result);
		for(i=0;i<result;i++)
		{
			free(resultArray[i]);
		}
		free(resultArray);
	}
	return 0;
}

void splitArray(unsigned int leftValue,unsigned int rightValue,unsigned int value,int deept,unsigned int **node,unsigned int *result)
{
	unsigned int startValue=0,endValue=0;
	unsigned int i;
	int deeptValue=0;	
	//printf("----result:%d leftValue:%d rightValue:%d\n",*result,leftValue,rightValue);	
	startValue = leftValue-rightValue;
	endValue = (leftValue+1)/2;	
	// printf("====result:%d startValue:%d endValue:%d\n",*result,startValue,endValue);
	for(i=startValue;i>=endValue;i--)
	{
		*result=*result+1;			
		deeptValue = deept+1;
		// printf("------------------deept:%d--------------------\n",deeptValue);
		// printfSplitArray(head,value);
		if(deeptValue>1)
		{
			memcpy(&(node[*result][value-deeptValue+1]),&(node[*result-1][value-deeptValue+1]),sizeof(unsigned int)*(deeptValue-1));		
			// printf("==============deept:%d====================\n",deeptValue);
			// printfSplitArray(node,value);				
		}
		node[*result][value-deeptValue-1] = i;	
		node[*result][value-deeptValue] = leftValue-i;				
		// printf("++++++++++++++++++deept:%d++++++++++++++++++++++\n",deeptValue);	
		//printfSplitNode(node[*result],value);
		// printf("start:%d result:%d leftValue:%d rightValue:%d\n",i,*result,i,leftValue-i);	
		splitArray(i,leftValue-i,value,deeptValue,node,result);		
		// printf("end:%d result:%d leftValue:%d rightValue:%d\n",i,*result,i,leftValue-i);
	}

	return;	
}

void printfSplitNode(unsigned int *node, int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (0 != node[i])
		{
			printf("%d ", node[i]);
		}
	}
	printf("\n");
	return;
}
void printfSplitNodeArray(unsigned int **node, int len, int arrayLine)
{
	int * printList=NULL;	
	int i = 0, j = 0, maxSite=0;
	

	printList = malloc(sizeof(int)*arrayLine);
	for (i = 0; i < arrayLine; i++)
	{
		printList[i] = i;
	}

	for (i = 0; i < arrayLine-1; i++)
	{
		for (j = i+1; j < arrayLine; j++)
		{			
			if (1 == compareNode(node,len,printList[j],printList[i]))
			{
				maxSite = printList[j];
				printList[j] = printList[i];
				printList[i] = maxSite;
			}
		}
	
	}	
	for (i = 0; i < arrayLine; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (0 != node[printList[i]][j])
			{
				printf("%d ", node[printList[i]][j]);
			}
		}
		printf("\n");
	}
	return;
}

int compareNode(unsigned int **node, int len,int compareLift,int compareRight)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		if(node[compareLift][i]>node[compareRight][i])
		{
			if(0 == node[compareRight][i])
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
		}
		else if(node[compareLift][i]<node[compareRight][i])
		{
			if(0!=node[compareLift][i])
			{
				return 1;
			}
			else
			{
				return 0;
			}			
		}		
	}
	return 0;
}
unsigned int getSplitArrayResult(unsigned int leftValue,unsigned int rightValue,unsigned int value)
{
	unsigned int startValue=0,endValue=0,result=0;
	unsigned int i;
	
	startValue = leftValue-rightValue;
	endValue = (leftValue+1)/2;	

	for(i=startValue;i>=endValue;i--)
	{
		result=result+1;					
		// printf("start:%d result:%d leftValue:%d rightValue:%d\n",i,*result,i,leftValue-i);	
		result = result + getSplitArrayResult(i,leftValue-i,value);		
		// printf("end:%d result:%d leftValue:%d rightValue:%d\n",i,*result,i,leftValue-i);
	}

	return result;	
}
#endif
