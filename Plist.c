#include "Mylib.h"

typedef struct nList
{
    unsigned int no;
    unsigned int value;
    struct nList *next;
}DigitalList;

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

