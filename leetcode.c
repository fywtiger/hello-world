#include "Mylib.h"
/********************************************************************
004：给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
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
/*解题思路：以一个队列为基础，将另外一个队列逐个插入到这个队列中，如果插入的位置大于两个队列的中位置，说明中位值就在第一个基础队列
中，区分一下奇偶数来获取中位值，如果插入位置小于中位位置，将取出值插入到基础队列中，然后再取下一个直到等于中位值，到达中位值后如果总
长队列是奇数，则中位就就是这个要插入的值，如果是偶数则需要再判断一下在中位的右侧值是基础队列的值还是待取出队列的值，然后再计算中位均
值，由于时间复杂度要小于O(log(m + n))，所以查询插入位置的时候不能够遍历，要使用二分法等算法*/
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
041：给定一个未排序的整数数组，找出其中没有出现的最小的正整数。
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
289：根据百度百科，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在1970年发明的细胞自动机。
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
554：你的面前有一堵方形的、由多行砖块组成的砖墙。 这些砖块高度相同但是宽度不同。你现在要画一条自顶向下的、穿过最少砖块的垂线。
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
解题思路：每行的砖墙的边界位置就相当于前面砖墙的总厚度，将对应位置标识为1，其他地方都是0，然后再按照列计算每行的值，值最大的地方就是
穿越最少的地方，用行数减去该值就是穿越的最小厚度。
|1、 3、 2、 4|      |= === == ====|      |1001010001|
|2、 2、 4、 2|------|== == ==== ==|------|0101000101|
|3、 3、 3、 1|      |=== === === =|      |0010010011|
|1、 5、 1、 3|      |= ===== = ===|      |1000011001|

*************************************************************************/
int leastBricks(int** wall, int wallSize, int* wallColSize)
{
    int i=0,j=0,insertResult=0;    
    int wallColSizeEx=0;
    int wallColSizeExAll=0;     
    Result_List resultList[20000]={0};
    int listLen = 0;
    int maxCount = 0;    
    
    for(i=0;i<wallColSize[0];i++)
    {
        wallColSizeExAll = wallColSizeExAll + wall[0][i];
    }
    
    for(i=0;i<wallSize;i++)
    {              
        wallColSizeEx=0;        
        for(j=0;j<wallColSize[i];j++)
        {
            wallColSizeEx = wallColSizeEx + wall[i][j];            
            if(0!=wallColSizeEx && wallColSizeEx!=wallColSizeExAll) 
            {
                insertResult = insertOneToResultList(resultList,wallColSizeEx,listLen);
                listLen = listLen + insertResult;                
            }               
        }
    }
    maxCount = queryMaxCountFromList(resultList,listLen);  
    return (wallSize - maxCount);
}
/******************************************************************************************************
 以每一行每一堆砖块的宽度作为键值建表，如果存在则count+1，不存在就插入一个，暂时不优化算法，插入时遍历全表
 ******************************************************************************************************/
int insertOneToResultList(Result_List *resultList,int value,int listLen)
{
    int i=0;    
    for(i=0;i<listLen;i++)
    {
        if(value == resultList[i].value)
        {
            resultList[i].count++;
            return 0;
        }
    }
    resultList[listLen].value = value;
    resultList[listLen].count = 1;
    return 1;
}
/******************************************************************************************************
 查询链表中count值最大的结果返回，此处就是砖缝最多的点，用行号减去该值就是最小需要穿透的墙的行数
 ******************************************************************************************************/
int queryMaxCountFromList(Result_List *resultList,int listLen)
{
    int i=0;
    int maxCount=0;
    for(i=0;i<listLen;i++)
    {
        if(maxCount<resultList[i].count)
        {
            maxCount = resultList[i].count;
        }
    }
    return maxCount;
}
/******************************************************************************************************************
621：给定一个用字符数组表示的 CPU 需要执行的任务列表。其中包含使用大写的 A - Z 字母表示的26 种不同种类的任务。任务可以以任意顺序执行，
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
    int TaskSumList[101]={0}; 
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
                runTime++;                             
            }
            else if(0 != tasksSize)
            {
                runTime++;
            }                                      
        }
        sortTaskList(TaskSumList,&taskListLen);        
    }
    return runTime;
}

void sortTaskList(int *TaskList,int *taskListLen)
{
    int i=0, j=0, maxValue=0;

    for(j=0;j<*taskListLen-1;j++)    
    {           
        for(i=j+1;i<*taskListLen;i++)
        {
            if(TaskList[j]<TaskList[i])
            {
                maxValue = TaskList[i];
                TaskList[i] = TaskList[j];
                TaskList[j] = maxValue;
            }
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
/**********************************************************************************
997:在一个小镇里，按从 1 到 N 标记了 N 个人。传言称，这些人中有一个是小镇上的秘密法官。
如果小镇的法官真的存在，那么：
小镇的法官不相信任何人。每个人（除了小镇法官外）都信任小镇的法官。
只有一个人同时满足属性 1 和属性 2 。
给定数组 trust，该数组由信任对 trust[i] = [a, b] 组成，表示标记为 a 的人信任标记为 b 的人。
如果小镇存在秘密法官并且可以确定他的身份，请返回该法官的标记。否则，返回 -1。
示例 1：
输入：N = 2, trust = [[1,2]]
输出：2
示例 2：
输入：N = 3, trust = [[1,3],[2,3]]
输出：3
示例 3：
输入：N = 3, trust = [[1,3],[2,3],[3,1]]
输出：-1
示例 4：
输入：N = 3, trust = [[1,2],[2,3]]
输出：-1
示例 5：
输入：N = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
输出：3
提示：
1 <= N <= 1000
trust.length <= 10000
trust[i] 是完全不同的
trust[i][0] != trust[i][1]
1 <= trust[i][0], trust[i][1] <= N
链接：https://leetcode-cn.com/problems/find-the-town-judge
解题思路：扫描trust的信息重新统计为一个新的trustList[I][J]，I直接就是小镇中的N中的某个人，J就是他信任的人，直接就用每个人的标号作为
访问下标。在扫描过程中将trust中出现的所有I位置的人放入到trustNum的数组中。如果trustNum<N-1，说明小镇中有人是谁也不信任的，则直接返
回-1，否则就随便选取一个人，然后从trustList列表中找出他信任的所有人，然后再去看trustNum剩下的其他人对应的位置是否也是被信任的，如
果都是1则说明该人员就是被信任人员，如果找出不这么一个人，则返回-1
**********************************************************************************/
int findJudge(int N, int** trust, int trustSize, int* trustColSize)
{
    int i=0,j=0,len=0;
    int trustList[1001][1001]={0};    
    int line=0,col=0;
    int *trustNum,trustNumSite=0,trustValue=0;

    if(1==N)
    {
        return 1;
    }
    trustNum = malloc(sizeof(int)*N);   
    memset(trustNum,0,sizeof(int)*N);
    for(i=0;i<trustSize;i++)
    {
        line = trust[i][0];
        col = trust[i][1];
        trustList[line][col] = 1;        
        for(j=0;j<N;j++)
        {
            if(0 == trustNum[j])
            {
               trustNum[j] = trust[i][0];
               len++;
               break;
            }
            else if(trustNum[j] == trust[i][0])     
            {
                break;
            }       
        }
    }    
   
    if(len < N-1)
    {
        free(trustNum);        
        return -1;
    }
    else
    {
        trustNumSite=trustNum[0];
        for(i=0;i<1001;i++)
        {   
            if(0 != trustList[trustNumSite][i])     
            {
                trustValue = 1;
                for(j=0;j<len;j++)
                {
                    
                    trustNumSite=trustNum[j];        
                    trustValue = trustValue & trustList[trustNumSite][i];
                }
                if(1==trustValue)
                {
                    free(trustNum);
                    return i;
                }      
            }                     
        }
    }

    return -1;
}

/**********************************************************************************
1144:给你一个整数数组 nums，每次操作会从中选择一个元素并将该元素的值减少 1。
如果符合下列情况之一，则数组 A 就是 锯齿数组：
每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
返回将数组 nums 转换为锯齿数组所需的最小操作次数。
示例 1：
输入：nums = [1,2,3]
输出：2
解释：我们可以把 2 递减到 0，或把 3 递减到 1。
示例 2：
输入：nums = [9,6,1,6,2]
输出：4
提示：
1 <= nums.length <= 1000
1 <= nums[i] <= 1000
链接：https://leetcode-cn.com/problems/decrease-elements-to-make-array-zigzag
解题：
**********************************************************************************/
int movesToMakeZigzag(int* nums, int numsSize)
{
    int operationStep=-1;    
    switch (numsSize)
    {
        case 1:
            operationStep = 0;
            break;
        case 2:
            operationStep = TwoNumbers(nums);
            break;
        default:
            operationStep = MoreThreeNumbers(nums,numsSize);
            break;        
    }    
    return operationStep;
}

int TwoNumbers(int* nums)
{
    if(nums[0]==nums[1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int MoreThreeNumbers(int* nums,int numsSize)
{
    int i=0;
    int operationStep1 = 0;
    int operationStep2 = 0;
    int flag = 1;
    int numList[1002]={0};
    
    memcpy(numList,nums,sizeof(int)*numsSize);    
    
    for(i=0;i<numsSize-1;i=i+2)
    {
        flag = 1;
        while(flag)
        {
            if(numList[i+1]<=numList[i])
            {
                operationStep2++;
                //printf("11111 numLise[%d]:%d<numList[%d]:%d\n",i+1,numList[i+1],i,numList[i]);
                numList[i]--;
                
            }
            else if(numList[i+1]<=numList[i+2])
            {
                operationStep2++;                
                //printf("22222 numLise[%d]:%d<numList[%d]:%d\n",i+1,numList[i+1],i+2,numList[i+2]);
                numList[i+2]--;
            }
            else 
            {
                flag = 0;
            }
        }
    }

    memcpy(numList,nums,sizeof(int)*numsSize);
    numList[numsSize]=1001;
    
    for(i=0;i<numsSize-1;i=i+2)
    {
        flag = 1;
        while(flag)
        {
            if(numList[i+1]>=numList[i])
            {
                operationStep1++;                
                //printf("33333 numLise[%d]:%d>numList[%d]:%d\n",i+1,numList[i+1],i,numList[i]);
                numList[i+1]--;
            }
            else if(numList[i+1]>=numList[i+2])
            {
                operationStep1++;                
                //printf("44444 numLise[%d]:%d>numList[%d]:%d\n",i+1,numList[i+1],i+2,numList[i+2]);
                numList[i+1]--;
            }
            else 
            {
                flag = 0;
            }
        }
    }
    printf("operationStep1:%d operationStep2:%d\n",operationStep1,operationStep2);
    return (operationStep1<operationStep2?operationStep1:operationStep2);       
}
/*************************************************************************************************
leetcode:406 假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于
或等于h的人数。 编写一个算法来重建这个队列。注意：总人数少于1100人。示例
输入:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
输出:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
链接：https://leetcode-cn.com/problems/queue-reconstruction-by-height
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 *************************************************************************************************/

int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes)
{
    NODE_PEOPLE* peopleList = NULL;
    int i=0,nodeListLen=0;
    NODE_LIST head=NULL,now=NULL;
    int** returnList=NULL;

    peopleList = SortQueueList(people,peopleSize,&nodeListLen);    
    #ifdef DEBUG 
    printf("nodeListLen is %d \n",nodeListLen);
    for(i=0;i<nodeListLen;i++)
    {
        printf("peopleList[%d].height:%d\n",i,peopleList[i].height);
        printf("peopleList[%d].sortSite:",i);
        for(j=0;j<MAX_PEOPLE;j++)
        {
            if(peopleList[i].sortSite[j] == 1)
            {
                printf("%d ",j);
            }
        }
        printf("\n");
    }
    printf("\n");
    #endif
    head = insertNodeList(nodeListLen,peopleList);

    *returnSize = peopleSize;       
    returnList = (int **)malloc(sizeof(int *)*peopleSize);
    *returnColumnSizes = (int *)malloc(sizeof(int)*peopleSize);
    for(i=0;i<peopleSize;i++)
    {
        returnList[i] = (int *)malloc(sizeof(int)*peopleColSize[i]);
        (*returnColumnSizes)[i]=peopleColSize[i];        
    }   
    now = head;
    printf("returnList:");
    while(NULL != now)
    {
        returnList[i][0] = now->height;
        returnList[i][1] = now->site;
        printf("[%d,%d] ",returnList[i][0],returnList[i][1]);
        i++;
        now = now->next;
        free(head);
        head = now;        
    }
    printf("\n");
    free(peopleList);   
    return returnList;    
}

void printList(NODE_LIST head)
{
    printf("List:");
    while(NULL != head)
    {
        printf("[%d,%d] ",head->height,head->site);
        head = head->next;
    }
    printf("\n");
}
/*将people输入的数据按照身高从高到低排序，在每个排序的结构中sortSize表示people中出现的该身高的大于等于自己的值
nodeListLen表示peopleList数组的长度，相同身高被合并到一个数组结构中*/
NODE_PEOPLE* SortQueueList(int** people, int peopleSize, int *nodeListLen)
{
    NODE_PEOPLE* peopleList = NULL;
    NODE_PEOPLE temp;
    int i=0,j=0;
    int nodeHeight=0,sortSite=0;
    peopleList =(NODE_PEOPLE*) malloc(sizeof(NODE_PEOPLE)*peopleSize);
    memset(peopleList,-1,sizeof(NODE_PEOPLE)*peopleSize);
    *nodeListLen = 0;
    for(i=0;i<peopleSize;i++)
    {
        nodeHeight = people[i][0];
        sortSite = people[i][1]; 
        for(j=0;j<peopleSize;j++)       
        {
            if(-1==peopleList[j].height)
            {
                peopleList[j].height = nodeHeight;
                peopleList[j].sortSite[sortSite] = 1;
                *nodeListLen = *nodeListLen+1;
                break;
            }
            else
            {
                if(nodeHeight == peopleList[j].height)
                {
                    peopleList[j].sortSite[sortSite] = 1;
                    break;
                }     
            }
        }
    }      
    for(i=0;i<(*nodeListLen-1);i++)
    {
        for(j=i+1;j<*nodeListLen;j++)
        {
            if(peopleList[i].height<peopleList[j].height)
            {
                memcpy(&temp,&peopleList[i],sizeof(NODE_PEOPLE));
                memcpy(&peopleList[i],&peopleList[j],sizeof(NODE_PEOPLE));
                memcpy(&peopleList[j],&temp,sizeof(NODE_PEOPLE));
            }
        }
    }
  
    return peopleList;
}

NODE_LIST insertNodeList(int nodeListLen,NODE_PEOPLE* peopleList)
{
    NODE_LIST head=NULL,peopleNode=NULL,insertSite=NULL,next=NULL;
    int i,j,z=0,heightSite=0;
    for(i=0;i<nodeListLen;i++)
    {              
        for(j=0;j<MAX_PEOPLE;j++)
        {
            if(peopleList[i].sortSite[j] == 1)
            {                
                peopleNode = malloc(sizeof(struct nodeList));                    
                peopleNode->height = peopleList[i].height;
                peopleNode->site = j;
                heightSite = peopleNode->site;
                peopleNode->next = NULL;
                if(0==heightSite)     
                {
                    next = head;
                    head = peopleNode;
                    head->next = next;   
                    printf("---------------%d----------------\n",z++);                     
                }         
                else
                {
                    insertSite = head;
                    while(heightSite>1)
                    {
                        insertSite=insertSite->next;
                        heightSite--;
                    }
                    next = insertSite->next;
                    insertSite->next = peopleNode;
                    peopleNode->next = next;
                    printf("---------------%d----------------\n",z++);
                }               
                printList(head);
            }
        }        
    }
    return head;
}
/*************************************************************************************************
leetcode406解题优化：直接进行队列排序，不再转换结构
 *************************************************************************************************/
int** reconstructQueue1(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes)
{
    int **SortPeople = NULL,**returnList = NULL;
    NODE_LIST head=NULL,now=NULL;
    int i=0;

    SortPeople = SortQueueList1(people,peopleSize,peopleColSize);
  
    head = insertNodeList1(SortPeople,peopleSize);

    *returnSize = peopleSize;       
    returnList = (int **)malloc(sizeof(int *)*peopleSize);
    *returnColumnSizes = (int *)malloc(sizeof(int)*peopleSize);
    for(i=0;i<peopleSize;i++)
    {
        returnList[i] = (int *)malloc(sizeof(int)*peopleColSize[i]);
        (*returnColumnSizes)[i]=peopleColSize[i];        
    }   
    i=0;
    now = head;
    printf("returnList:");
    while(NULL != now)
    {
        returnList[i][0] = now->height;
        returnList[i][1] = now->site;
        printf("[%d,%d] ",returnList[i][0],returnList[i][1]);
        i++;
        now = now->next;
        free(head);
        head = now;        
    }
    printf("\n");
    for(i=0;i<peopleSize;i++)
    {
        free(SortPeople[i]);
    }
    free(SortPeople);
    return returnList;  

}

int** SortQueueList1(int** people, int peopleSize,int* peopleColSize)
{
    int **SortPeople = NULL;
    int i=0,j=0;
    int temp[2]={0};

    SortPeople = (int **)malloc(sizeof(int *)*peopleSize);
    for(i=0;i<peopleSize;i++)
    {
        SortPeople[i] = (int *)malloc(sizeof(int)*peopleColSize[i]);        
        memcpy(SortPeople[i],people[i],peopleColSize[i]*sizeof(int));
    }
    
    for(i=0;i<peopleSize-1;i++)
    {
        for(j=i+1;j<peopleSize;j++)
        {
            if(SortPeople[i][0]<SortPeople[j][0])
            {
                temp[0] = SortPeople[i][0];
                temp[1] = SortPeople[i][1];
                SortPeople[i][0] = SortPeople[j][0];
                SortPeople[i][1] = SortPeople[j][1];
                SortPeople[j][0] = temp[0];
                SortPeople[j][1] = temp[1];
            }
            else if((SortPeople[i][0]==SortPeople[j][0])&&(SortPeople[i][1]>SortPeople[j][1]))
            {
                temp[0] = SortPeople[i][0];
                temp[1] = SortPeople[i][1];
                SortPeople[i][0] = SortPeople[j][0];
                SortPeople[i][1] = SortPeople[j][1];
                SortPeople[j][0] = temp[0];
                SortPeople[j][1] = temp[1];
            }            
        }
    }
    return SortPeople;
}

NODE_LIST insertNodeList1(int **SortPeople, int peopleSize)
{
    NODE_LIST head=NULL,peopleNode=NULL,insertSite=NULL,next=NULL;
    int i,z=0,heightSite=0;
    for(i=0;i<peopleSize;i++)
    {    
        peopleNode = malloc(sizeof(struct nodeList));                    
        peopleNode->height = SortPeople[i][0];
        peopleNode->site = SortPeople[i][1];
        heightSite = peopleNode->site;
        peopleNode->next = NULL;
        if(0==heightSite)     
        {
            next = head;
            head = peopleNode;
            head->next = next;   
            printf("---------------%d----------------\n",z++);                     
        }         
        else
        {
            insertSite = head;
            while(heightSite>1)
            {
                insertSite=insertSite->next;
                heightSite--;
            }
            next = insertSite->next;
            insertSite->next = peopleNode;
            peopleNode->next = next;
            printf("---------------%d----------------\n",z++);
        }               
        printList(head);
    }
    return head;
}