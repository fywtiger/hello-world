#include "Mylib.h"
/********************************************************************
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。
示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0
示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 ********************************************************************/
void findMedianSortedArraysPrint()
{
    char *inputNumList1 = NULL;
    char *inputNumList2 = NULL;
    int *dOutList1 = NULL;
    int *dOutList2 = NULL;
    int dOutListLen1 = 0, dOutListLen2 = 0;
    double result = 0;

    int j = 0;

    inputNumList1 = malloc(sizeof(char) * MAX);
    if (NULL == inputNumList1)
    {
        printf("TscanfDigital malloc input String1 memory is NULL\n");
        return;
    }
    printf("Please input String1 list:\n");
    scanf("%s", inputNumList1);

    dOutList1 = malloc(sizeof(int) * MAX);
    memset(dOutList1, 0, MAX);
    if (FAULT == OutScanfDigitalNum(inputNumList1, dOutList1, &dOutListLen1))
    {
        printf("OutScanfDigitalNum String1 error!\n");
        return;
    }

    printf("dOutList1[%d]:", dOutListLen1);
    for (j = 0; j < dOutListLen1; j++)
    {
        printf("%d ", dOutList1[j]);
    }
    printf("\n");

    inputNumList2 = malloc(sizeof(char) * MAX);
    if (NULL == inputNumList2)
    {
        printf("TscanfDigital malloc input String2 memory is NULL\n");
        return;
    }

    printf("Please input String2 list:\n");
    scanf("%s", inputNumList2);
    dOutList2 = malloc(sizeof(int) * MAX);
    memset(dOutList2, 0, MAX);
    if (FAULT == OutScanfDigitalNum(inputNumList2, dOutList2, &dOutListLen2))
    {
        printf("OutScanfDigitalNum String1 error!\n");
        return;
    }

    printf("dOutList2[%d]:", dOutListLen2);
    for (j = 0; j < dOutListLen2; j++)
    {
        printf("%d ", dOutList2[j]);
    }
    printf("\n");

    result = findMedianSortedArrays(dOutList1, dOutListLen1, dOutList2, dOutListLen2);
    if (FAULT == result)
    {
        printf("findMedianSortedArraysPrint call findMedianSortedArrays result Error!\n");
        return;
    }
    printf("findMedianSortedArrays result:%lf \n", result);

    return;
}
int OutScanfDigitalNum(char *str, int *dOutList, int *dOutListLen)
{
    //unsigned int dOutList[MAX]={0};
    unsigned int dOutListNum = 0;
    unsigned int dInputStrLen = 0;
    int dOutListDigitalFlag = FALSE;
    int i;
    int j = 0;
    if (NULL == str || NULL == dOutList)
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

    *dOutListLen = dOutListNum;
    return SUCCESS;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int j = 0;
    int inSite = 0;
    int AllMidSite = 0;
    int *nums = NULL;
    int numsSize = 0;
    double dresult = 0;

    printf("input num1[%d]:", nums1Size);
    for (j = 0; j < nums1Size; j++)
    {
        printf("%d ", nums1[j]);
    }
    printf("\n");

    printf("input num2[%d]:", nums2Size);
    for (j = 0; j < nums2Size; j++)
    {
        printf("%d ", nums2[j]);
    }
    printf("\n");
    nums = malloc(sizeof(int) * (nums1Size + nums2Size));
    if (NULL == nums)
    {
        printf("findMedianSortedArrays malloc memory for nums Error!\n");
        return -1;
    }
    memcpy(nums, nums1, sizeof(int) * nums1Size);
    numsSize = nums1Size;
    AllMidSite = (nums1Size + nums2Size) % 2 ? (nums1Size + nums2Size) / 2 : (nums1Size + nums2Size) / 2 - 1;

    for (j = 0; j < nums2Size; j++)
    {
        inSite = insertNumToList(nums2[j], nums, numsSize);
        //printf("num2[%d]:%d insertNumToList site is %d,AllMidSite is %d\n",j,nums2[j],inSite,AllMidSite);
        if (inSite < AllMidSite)
        {
            if (inSite < numsSize)
            {
                memmove(&nums[inSite + 1], &nums[inSite], numsSize - inSite);
            }
            numsSize++;
            nums[inSite] = nums2[j];
        }

        if (inSite == AllMidSite)
        {
            //printf("===================\n");
            if (0 != (nums1Size + nums2Size) % 2)
            {
                //printf("!==================0\n");
                dresult = (double)nums2[j];
                free(nums);
                return dresult;
            }
            else
            {
                if ((j + 1) == nums2Size)
                {
                    //printf("================== j:%d\n",j);
                    dresult = ((double)nums2[j] + (double)nums[inSite]) / 2;
                    free(nums);
                    return dresult;
                }
                else
                {
                    if (nums2[j + 1] <= nums[inSite])
                    {
                        //printf("==================nums2[%d][%d]:%d %d,nums[%d]:%d\n",j,j+1,nums2[j],nums2[j+1],inSite,nums[inSite]);
                        dresult = ((double)nums2[j] + (double)nums2[j + 1]) / 2;
                        free(nums);
                        return dresult;
                    }
                    else
                    {
                        //printf("==================nums2[%d]:%d %d,nums[%d]:%d\n",j,nums2[j],inSite,nums[inSite]);
                        dresult = ((double)nums2[j] + (double)nums[inSite]) / 2;
                        free(nums);
                        return dresult;
                    }
                }
            }
        }

        if (inSite > AllMidSite)
        {
            if (0 != (nums1Size + nums2Size) % 2)
            {
                dresult = (double)nums[AllMidSite];
                free(nums);
                return dresult;
            }
            else
            {
                dresult = (double)(nums[AllMidSite] + nums[AllMidSite + 1]) / 2;
                free(nums);
                return dresult;
            }
        }
    }
    return -1;
}
int insertNumToList(int iNum, int *numList, int numListLen)
{
    int endSite = 0;
    int startSite = 0;
    int nSite = 0;
    endSite = numListLen - 1;

    if (iNum >= numList[endSite])
    {
        return numListLen;
    }
    if (iNum <= numList[startSite])
    {
        return 0;
    }
    while (endSite > startSite)
    {
        nSite = (endSite + startSite) / 2;
        if (iNum < numList[nSite])
        {
            endSite = nSite;
        }
        else if (iNum > numList[nSite])
        {
            startSite = nSite + 1;
            nSite++;
        }
        else
        {
            return nSite;
        }
    }
    return -1;
}
/*********************************************************************
给定一个未排序的整数数组，找出其中没有出现的最小的正整数。
示例 1:
输入: [1,2,0]
输出: 3
示例 2:
输入: [3,4,-1,1]
输出: 2
示例 3:
输入: [7,8,9,11,12]
输出: 1
说明:
你的算法的时间复杂度应为O(n)，并且只能使用常数级别的空间。
在真实的面试中遇到过这道题？
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/first-missing-positive
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *************************************************************************/
int firstMissingPositive(int *nums, int numsSize)
{
    int mixNumber=-1;
    int i=0,j=0;
    int *sortNum=NULL;
    int maxValue=-1,maxValueSite=0,sortNumSize=0;

    sortNum = malloc(sizeof(int)*numsSize);
    memset(sortNum,0,sizeof(int)*numsSize);
    sortNumSize = numsSize;
    while (sortNumSize>0)
    {
		maxValue = -1;
        for(i=0;i<numsSize;i++)
        {            
            if(nums[i]>maxValue)
            {
                maxValue = nums[i];
                maxValueSite = i;
            }
        }

        if(-1 == maxValue&&sortNumSize==numsSize)
        {
            free(sortNum);
            return 1;
        }
        else if(maxValue>0)
        {
            nums[maxValueSite] = -1;
            sortNum[j] = maxValue; 			        
            j++;
        }   
		sortNumSize--;   		     
    }	
	if(sortNum[j-1]>1)
	{
		mixNumber = 1; 
	}
	else
	{
		for(i=j-1;i>1;i--)
		{
			if((sortNum[i-1]-sortNum[i])>1)
			{
				return (sortNum[i]+1);
			}   
		}
		mixNumber = sortNum[0]+1;    
	}    
    free(sortNum);
    return mixNumber;
}

/*********************************************************************
根据百度百科，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。
给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞具有一个初始状态 live（1）即为活细胞， 
或 dead（0）即为死细胞。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
根据当前状态，写一个函数来计算面板上细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
示例:
输入:             输出: 
[                [
  [0,1,0],         [0,0,0],
  [0,0,1],         [1,0,1],
  [1,1,1],         [0,1,1],
  [0,0,0]          [0,1,0]
]                ]
https://leetcode-cn.com/problems/game-of-life/
行：boardSize  列：boardColSize
*************************************************************************/
void gameOfLife(int** board, int boardSize, int* boardColSize)
{
    int i=0,j=0;
    int ** boardEx=NULL;
    int boardExSize=0,boardExColSize=0,nLiveSum=0;

    boardExSize = boardSize+2;
    boardExColSize = *boardColSize+2;
    boardEx = (int **)malloc((sizeof(int *))*boardExSize);
    for(i=0;i<boardExSize;i++)
    {
        boardEx[i] =(int *)malloc(sizeof(int)*boardExColSize);
        for(j=0;j<boardExColSize;j++)
        {
            if(0==i||(boardExSize-1==i))
            {
                boardEx[i][j] = 0;
            }
            else if(0==j||(boardExColSize-1)==j)
            {
                boardEx[i][j] = 0;
            }    
            else
            {
                boardEx[i][j] = board[i-1][j-1];
            }   
        }
    }
    for(i=1;i<(boardExSize-1);i++)
    {
        for(j=1;j<(boardExColSize-1);j++)
        {
            nLiveSum=boardEx[i-1][j-1]+boardEx[i-1][j]+boardEx[i-1][j+1]+boardEx[i][j-1]+boardEx[i][j+1]+boardEx[i+1][j-1]+boardEx[i+1][j]+boardEx[i+1][j+1];
            if(1==board[i-1][j-1])
            {
                if(nLiveSum<2)
                {
                    board[i-1][j-1]=0;
                }
                else if(nLiveSum>3)
                {
                    board[i-1][j-1]=0;
                }   
            }
            else if (0==board[i-1][j-1])
            {
                if(3 == nLiveSum)
                {
                    board[i-1][j-1]=1;
                }
            }
        }
    }
    for(i=0;i<boardExSize;i++)
    {
        free(boardEx[i]);
    }
    free(boardEx);
    return;
}

/*********************************************************************
你的面前有一堵方形的、由多行砖块组成的砖墙。 这些砖块高度相同但是宽度不同。你现在要画一条自顶向下的、穿过最少砖块的垂线。
砖墙由行的列表表示。 每一行都是一个代表从左至右每块砖的宽度的整数列表。
如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。你需要找出怎样画才能使这条线穿过的砖块数量最少，并且返回穿过的砖块数量。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。
示例：
输入: [[1,2,2,1],
      [3,1,2],
      [1,3,2],
      [2,4],
      [3,1,2],
      [1,3,1,1]]
输出: 2
提示：
每一行砖块的宽度之和应该相等，并且不能超过 INT_MAX。
每一行砖块的数量在 [1,10,000] 范围内， 墙的高度在 [1,10,000] 范围内， 总的砖块数量不超过 20,000。
https://leetcode-cn.com/problems/brick-wall/
行：wallSize  列：wallColSize
*************************************************************************/
int leastBricks(int** wall, int wallSize, int* wallColSize)
{
    int i=0,j=0;    
    int wallColSizeEx=0;
    int wallColSizeExAll=0;
    int **wallEx=NULL;
    int rNum=0;
    //int *result;
    int result[10000]={0};
    
    wallEx = (int **)malloc(sizeof(int *)*wallSize);    
    for(j=0;j<wallColSize[0];j++)
    {
        wallColSizeExAll = wallColSizeExAll + wall[0][j];
    }
    
    for(i=0;i<wallSize;i++)
    {
        wallEx[i] = (int *)malloc(sizeof(int) * wallColSizeExAll);        
        memset(wallEx[i],0,sizeof(int) * wallColSizeExAll);        
        wallColSizeEx=0;        
        for(j=0;j<wallColSize[i];j++)
        {
            wallColSizeEx = wallColSizeEx + wall[i][j];            
            wallEx[i][wallColSizeEx-1] = 1;                     
        }
    }
    
    //result = malloc(sizeof(int) * wallColSizeExAll);    
    for(j=0;j<(wallColSizeExAll-1);j++)
    {
        //result[j] = 0;
        for(i=0;i<wallSize;i++)
        {
            result[j] = result[j] + wallEx[i][j];
        }
        if(result[j]>rNum)
        {
            rNum = result[j];
        }
    }     

    for(i=0;i<wallSize;i++)
    {
        free(wallEx[i]);
    }
    free(wallEx);
    return (wallSize - rNum);
}
/******************************************************************************************************************
给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。任务可以以任意顺序执行，
并且每个任务都可以在 1 个单位时间内执行完。CPU 在任何一个单位时间内都可以执行一个任务，或者在待命状态。
然而，两个相同种类的任务之间必须有长度为 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
你需要计算完成所有任务所需要的最短时间。
示例 1：
输入: tasks = ["A","A","A","B","B","B"], n = 2
输出: 8
执行顺序: A -> B -> (待命) -> A -> B -> (待命) -> A -> B.
注：
任务的总个数为 [1, 10000]。
n 的取值范围为 [0, 100]。
链接：https://leetcode-cn.com/problems/task-scheduler
结题思路:
将无序的任务列表转换为一个相同任务的调度列表，然后按照任务的数量从大到小做排序，按照贪婪算法的结题思路，当间隔冷却为N的话，
每次都把前面N+1个任务顺序调度了，每次调度后将对应类型的任务数减1，如果某种类型剩余的任务数已经为0，也需要填充一次rumtime，
然后在重新做一次剩余统计队列的排序，直到所有的任务都被调度完毕，需要注意最后一次调度的时候N次循环是做不完的，需要将循环次数加入
到runTime
**********************************************************************************************************************/
int leastInterval(char *tasks, int tasksSize, int n)
{
    int runTime=0;
    int i=0;       
    int TaskSumList[26]={0}; 
    int taskListLen=0;
    
    taskListLen = ChangeTaskListToSum(tasks,tasksSize,TaskSumList);
    
    sortTaskList(TaskSumList,&taskListLen);

    while(tasksSize>0)
    {
        for(i=0;i<=n;i++)
        {
            if(TaskSumList[i]>0)
            {
                TaskSumList[i]--;
                tasksSize--;                               
            }
            if(0 != tasksSize)
            {
                runTime++;
            }     
            else
            {
                runTime = runTime+i+1;
                return runTime;
            }                           
        }
        sortTaskList(TaskSumList,&taskListLen);        
    }
    return runTime;
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
            }
        }
        if(maxSite>j)//当TaskList剩余大于0的值小于n后，再循环到为0的时候，后面的值就不需要再排序，避免覆盖
        {
            TaskList[maxSite] = TaskList[j];
            TaskList[j] = maxValue;
        }
    }
    return;
}
/*将输入的调度任务列表转换为一个任务的统计列表，比如
输入List:[ A A A B B B A D E C F Z F D C F X ] 
转换为 sum List:[A:4 B:3 C:2 D:2 E:1 F:3 X:1 Z:1 ]:*/
int ChangeTaskListToSum(char *tasks,int tasksSize ,int *TaskSumList)
{
    int TaskList[26]={0};  
    int taskListLen=0;
    int i,j;

    for(i=0;i<tasksSize;i++)
    {
        j=tasks[i]-'A';
        if(0==TaskList[j])
        {
            taskListLen++;
        }
        TaskList[j]++;        
    }
    
    for(i=0,j=0;i<26;i++)
    {
        if(0!=TaskList[i])
        {
           TaskSumList[j] = TaskList[i];
           j++;
        }
    }    
    return taskListLen;
}

void taskRunTime()
{
    char tasks[MAX]={0};
    char input[MAX]={0};
    int i=0;
    int taskSize=0;
    int j=0;
    int runTime;
    int frozenTime=0;
    printf("Please input Tasks List:");
    scanf("%s",input);
    for(i=0;i<strlen(input);i++)
    {
        if(input[i]>='A'&&input[i]<='Z')
        {
            tasks[j] = input[i];
            j++;
            taskSize++;
        }
    }
    printf("\ntasks[%d]:[",taskSize);
    for(i=0;i<taskSize;i++)
    {
        if(i<taskSize-1)
        {
            printf("\"%c\",",tasks[i]);
        }
        else
        {
            printf("\"%c\"]",tasks[i]);
        }
    }
    printf("\n");
    printf("Please input Task Frozen Tinme:");
    scanf("%d",&frozenTime);
    runTime = leastInterval(tasks,taskSize,frozenTime);
    printf("Task List Mix Run Time:%d when frozenTime is %d",runTime,frozenTime);
}
/* C++实现
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) 
    {
        if(tasks.size()==0) 
        {
            return 0;
        }
        //统计各个任务的次数
        int hash[26]={0}, tasksSize = tasks.size();
        for (auto task : tasks)
        {
            hash[task - 'A'] += 1;
        }
        //寻找次数最多的任务maxTaskCnt，maxTasks记录次数最多的任务的个数
        int maxTaskCnt = 0, maxTasks = 0;
        for(int i = 0; i < 26; ++i)
        {
            if(hash[i] > maxTaskCnt) 
            {
                maxTaskCnt = hash[i];
                maxTasks = 1;
            }
            else if(hash[i] == maxTaskCnt)
            {
                maxTasks++;
            }
        }
        //计算需要的最大时间
        int a = tasksSize - maxTaskCnt - maxTasks + 1;//需要插入的个数
        int b = n * (maxTaskCnt - 1);//可插入利用的最大个数
        if(a < b) 
        {//第一种情况，贪心策略，尽量插入间隔
            return (n + 1) * (maxTaskCnt - 1) + maxTasks;
        }
        else {//第二种情况，只要不让相同的任务的距离小于n即可
            return tasksSize;
        }
    }
};
*/