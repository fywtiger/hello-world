#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
