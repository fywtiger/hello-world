#include "Mylib.h"

typedef int (*C_scanfDigitalNum)(char *str);
typedef int (*C_scanfDigitalString)(char *str);
typedef struct ScanfDigitalClass
{
	C_scanfDigitalNum CscanfDigitalNum;
	C_scanfDigitalString CscanfDigitalString;
} C_ScanfDigital;

int TscanfDigital()
{
	char *inputNumList;
	C_scanfDigitalString CscanfDigitalString;
	C_ScanfDigital CscanfDigita;

	inputNumList = malloc(sizeof(char) * MAX);

	if (NULL == inputNumList)
	{
		printf("TscanfDigital malloc input memory is NULL\n");
		return FAULT;
	}
	printf("Please input String list:\n");
	scanf("%s", inputNumList);
	//scanf("%s",inputNumList);

	CscanfDigita.CscanfDigitalNum = scanfDigitalNum;
	if (FALSE == CscanfDigita.CscanfDigitalNum(inputNumList))
	{
		printf("scanfDigitalNum is error!\n");
		Free_Memory(inputNumList);
		return FAULT;
	}

	CscanfDigitalString = scanfDigitalString;
	if (FALSE == CscanfDigitalString(inputNumList))
	{
		printf("scanfDigitalNum is error!\n");
		Free_Memory(inputNumList);
		return FAULT;
	}
	Free_Memory(inputNumList);
	return SUCCESS;
}

int scanfDigitalNum(char *str)
{
	unsigned int dOutList[MAX] = {0};
	unsigned int dOutListNum = 0;
	unsigned int dInputStrLen = 0;
	int dOutListDigitalFlag = FALSE;
	int i;
	int j = 0;
	if (NULL == str)
	{
		printf("scanfDigitalNum input point is NULL\n");
		return FAULT;
	}
	dInputStrLen = strlen(str);
	for (i = 0; i < dInputStrLen; i++)
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
		{
			dOutList[j] = dOutList[j] * 10 + *(str + i) - '0';
			if (FALSE == dOutListDigitalFlag)
			{
				dOutListNum++;
			}
			dOutListDigitalFlag = TRUE;
		}
		else
		{
			if (TRUE == dOutListDigitalFlag)
			{
				j++;
			}
			dOutListDigitalFlag = FALSE;
		}
	}

	printf("ScanfDigitalNumList have %d Digital:\n", dOutListNum);
	for (i = 0; i < dOutListNum; i++)
	{
		printf("Digitala[%d]:%d\n", i, dOutList[i]);
	}
	return SUCCESS;
}

int scanfDigitalString(char *str)
{
	unsigned int dOutList[MAX] = {0};
	unsigned int dOutListNum = 0;
	unsigned int dInputStrLen = 0;
	int dOutListDigitalFlag = FALSE;
	int i;
	int j = 0;
	if (NULL == str)
	{
		printf("scanfDigitalNum input point is NULL\n");
		return FAULT;
	}
	dInputStrLen = strlen(str);
	for (i = 0; i < dInputStrLen; i++)
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
		{
			dOutList[j++] = *(str + i) - '0';
			if (FALSE == dOutListDigitalFlag)
			{
				dOutListNum++;
			}
			dOutListDigitalFlag = TRUE;
		}
		else
		{
			if (TRUE == dOutListDigitalFlag)
			{
				dOutList[j++] = ' ';
			}
			dOutListDigitalFlag = FALSE;
		}
	}

	printf("ScanfDigitalNumList have %d DigitalString:\n", dOutListNum);
	if (dOutListNum != 0)
	{
		printf("DigitalaString[0]:");
	}
	for (i = 0, dOutListNum = 0; i < j; i++)
	{
		if (' ' == dOutList[i])
		{
			printf("\nDigitalaString[%d]:", dOutListNum);
			dOutListNum++;
		}
		else
		{
			printf("%d", dOutList[i]);
		}
	}
	return SUCCESS;
}
