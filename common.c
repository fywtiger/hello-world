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
#if 0
int main(int argc, char const *argv[])
{
	int TaskList[8]={0};
	int taskListLen = 8;
	int i;
	TaskList[0] = 1;

	printf("before sort tasks sum List:[");
	for(i=0;i<taskListLen;i++)
	{
		printf("%c:%d ",(i+'A'),TaskList[i]);
	}
	printf("]\n");
	sortTaskList(TaskList,&taskListLen);
	printf("after sort tasks sum List:[");
	for(i=0;i<taskListLen;i++)
	{
		printf("%c:%d ",(i+'A'),TaskList[i]);
	}
	printf("]\n");
	return 0;
}

void sortTaskList(int *TaskList,int *taskListLen)
{
    int i=0, j=0, maxValue=0, maxSite=0;

    for(j=0;j<*taskListLen;j++)
    {
        maxValue = 0;        
        for(i=j;i<*taskListLen;i++)
        {
            if(TaskList[i]>maxValue)
            {
                maxValue = TaskList[i];
                maxSite = i;
				printf("loop[%d][%d] maxValue:%d maxSite:%d\n",j,i,maxValue,maxSite);
            }
        }
        TaskList[maxSite] = TaskList[j];
        TaskList[j] = maxValue;

		printf("loop[%d][%d] TaskList[%d]:%d value:%d\n",j,i,maxSite,TaskList[maxSite],TaskList[j]);
    }
    return;
}
#endif