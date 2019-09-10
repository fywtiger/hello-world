#include "Mylib.h"

int PListPrint()
{
    char *inputNumList;
    
	inputNumList = malloc(sizeof(char)*MAX);	
	if(NULL == inputNumList)
	{
		printf("pListPrint malloc input memory is NULL\n");
		return FAULT;
	}
	printf("Please input String list:\n");
	//scanf_s("%s",inputNumList,MAX);
	scanf("%s",inputNumList);
    if(FALSE == scanfDigitalNumList(inputNumList))
	{
		printf("scanfDigitalNum is error!\n");
		Free_Memory(inputNumList);
		return FAULT;
	}
	Free_Memory(inputNumList);
	return SUCCESS;
}

int scanfDigitalNumList(char *str)
{
    
    DigitalList *nDigitalList;    
    DigitalList *listHead;   
    DigitalList *listNow; 	
	unsigned int dOutListNum=0;
	unsigned int dInputStrLen=0;
	int dOutListDigitalFlag = FALSE;
	int i;

	if(NULL == str)
	{
		printf("scanfDigitalNum input point is NULL\n");
		return FAULT;
	}
	dInputStrLen = strlen(str);
    listHead = NULL;
    listNow = NULL; 

	for(i=0;i<dInputStrLen;i++)
	{
		if( *(str+i)>='0' && *(str+i)<='9')
		{
            if(FALSE == dOutListDigitalFlag)
            {
                nDigitalList = malloc(sizeof(DigitalList));   
                if(NULL==nDigitalList)
                {
                    printf("malloc DigitalList memory ERROR!\n");
                    return FAULT;
                }
                nDigitalList->no=dOutListNum++;
                nDigitalList->value=0;
                nDigitalList->next=NULL;

                if(NULL == listHead)
                {
                    listHead = nDigitalList;
                    listNow = listHead;
                }
                else
                {
                    listNow->next = nDigitalList;
                    listNow = nDigitalList;
                }                
            }
            nDigitalList->value = nDigitalList->value*10+*(str+i)-'0';
			dOutListDigitalFlag = TRUE;
		}
		else
		{
			dOutListDigitalFlag = FALSE;			
		}		
	}

	printf("ScanfDigitalNumList have %d Digital:\n",dOutListNum);
    nDigitalList = listHead;
	while(NULL!=nDigitalList)
	{
		printf("DigitalList[%d]:%d\n",nDigitalList->no,nDigitalList->value);
        listHead = nDigitalList;
        nDigitalList = nDigitalList->next;
        Free_Memory((char *)listHead);
	}   
  
	return SUCCESS;
}

int ChangeDigitalList()
{
    unsigned int tLine;
    unsigned int i;
    unsigned int j;
    unsigned int z;
    unsigned int nline=1;
    unsigned int nTotal;

    printf("Please input a number of line:");
    scanf("%d",&tLine);
    nTotal= (tLine*(tLine+1))>>1;
    for(i=1;i<nTotal;nline++)
    {
        for(j=0;j<(2*tLine-1);j++)
        {
            if(j==tLine-nline)
            {
                for(z=0;z<nline;z++)
                {
                    printf("%d  ",i);
                    i++;
                    j=j+2;
                }               
                
            }
            else
            {
                printf("  ");
            }            
        }
        printf("\n");
    }
    return 0;
}

void DelOnePointFromList()
{
    struct ListNode *node=NULL;
    struct ListNode *nodeHead=NULL;
    struct ListNode *nodeNow=NULL;
    unsigned int value[10]={0};
    char str[20]={0},dstr[20]={0};
    int valueLen=0,dVal=0;
    int i=0;

    printf("please input number string:");
    scanf("%s",str);
    (void)StringToDigitalNum(str,value,&valueLen);    
    while(i<valueLen)
    {
        printf(" %d ",value[i]);
        i++;
    }
    printf("\n");
    i=0;
    while(i<valueLen)
    {
        node = malloc(sizeof(struct ListNode));
        node->val = value[i];
        node->next = NULL;
        if(NULL == nodeHead)
        {
            nodeHead = node;
            nodeNow = node;
        }
        else
        {
            nodeNow->next = node;
            nodeNow = node;
        }       
        i++; 
    }

    nodeNow = nodeHead;
    printf("nodeList is:");
    while(NULL!=nodeNow)
    {
        printf(" %d,",nodeNow->val);
        nodeNow=nodeNow->next;
    }

    printf("\nplease input the value of del node\n");
    scanf("%s",dstr);
    dVal = (int)atof(dstr);
    deleteNode(&nodeHead,dVal);
    nodeNow = nodeHead;
    //nodeNow = deleteNode2(nodeHead,dVal);    

    printf("del node[%d] from list,The List is:",dVal);
    while(NULL!=nodeNow)
    {
        node = nodeNow;
        printf(" %d,",nodeNow->val);
        nodeNow=nodeNow->next;
        free(node);
    }
    return;
}
int StringToDigitalNum(char *str,unsigned int *dOutList,int *dOutListNum)
{
	unsigned int dInputStrLen=0;
	int dOutListDigitalFlag = FALSE;
	int i;
	int j=0;
	if(NULL == str||NULL == dOutList||NULL == dOutListNum)
	{
		printf("scanfDigitalNum input point is NULL\n");
		return FAULT;
	}
	dInputStrLen = strlen(str);
    *dOutListNum = 0;
	for(i=0;i<dInputStrLen;i++)
	{
		if( *(str+i)>='0' && *(str+i)<='9')
		{
			dOutList[j]=dOutList[j]*10+*(str+i)-'0';
			if(FALSE == dOutListDigitalFlag)
			{
				*dOutListNum=*dOutListNum+1;
			}
			dOutListDigitalFlag = TRUE;
		}
		else
		{
			if(TRUE == dOutListDigitalFlag)
			{
				j++;
			}
			dOutListDigitalFlag = FALSE;			
		}		
	}
	return SUCCESS;
}

void deleteNode(struct ListNode** node,unsigned int value) 
{
    struct ListNode *nodeList,*nodePre,*nodeHead;
    nodeList = *node;
    nodeHead = *node;
    nodePre = *node;
    while(NULL!=nodeList)
    {
        if(nodeHead->val == value)
        {
            nodeHead = nodeHead->next;
            *node = nodeHead;
            //free(nodePre);            
            nodeList = nodeHead;
        }

        if(nodeList->val == value)
        {
            nodePre->next = nodeList->next;
            //free(nodeList); 
            nodeList = nodePre->next;
        }
        else
        {
            nodePre = nodeList;
            nodeList = nodeList->next;
        }
        
    }
    return;
}

struct ListNode* deleteNode2(struct ListNode* node,unsigned int value) 
{
    struct ListNode *nodeList,*nodePre,*nodeHead;
    nodeList = node;
    nodeHead = node;
    nodePre = node;
    while(NULL!=nodeList)
    {
        if(nodeHead->val == value)
        {
            nodeHead=nodeHead->next;   
            free(nodePre);         
            nodeList = nodeHead;
        }

        if(nodeList->val == value)
        {
            nodePre->next = nodeList->next;
            free(nodeList); 
            nodeList = nodePre->next;
        }
        else
        {
            nodePre = nodeList;
            nodeList = nodePre->next;
        }
        
    }
    return nodeHead;
}
