#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
struct common
{
	int a;
	int b;
};
typedef struct common COMMON;
void Free_Memory(char *str)
{
	if(NULL == str)
	{
		printf("Free_Memory Error!\n");
		return;
	}
	free(str);
	str = NULL;
	return;
}
#if 0
void strlong(int **str1,int **str2)
{	
	*str1 = malloc(sizeof(int)*3);	
	(*str1)[0] = 1;
	(*str1)[1] = 10;
	(*str1)[2] = 100;

	*str2 = malloc(sizeof(int));
	str2[0][0] = 2;
	*(str2[1]) = 20;
	str2[0][2] = 200;
}
int main()
{    	
	int **str1 = NULL;
	int **str2 = NULL;
	int i;	
	str1 = (int **)malloc(sizeof(int *));
	str2 = (int **)malloc(sizeof(int *)*3);
    strlong(str1,str2);
    printf("Longer string1: %d %d %d\n", (*str1)[0],str1[0][1],(*str1)[2]);
	printf("Longer string2: %d %d %d\n", str2[0][0],*(str2[1]),str2[0][2]);
    return 0;
}
#endif




