/*
插入排序(Insertion sort)：
一、核心思想：将待排序元素看作手中的牌，每次从桌上摸一张牌，插入到手中有序牌的正确位置。

二、算法步骤：
    1. 从第二个元素开始（索引i=1），将其视为"待插入元素"
    2. 与前一个元素比较：
        - 如果前一个元素更大，将前一个元素后移一位
        - 继续向前比较，直到找到正确位置
    3. 将待插入元素放入正确位置
    4. 重复步骤1-3，直到所有元素都处理完

三、复杂度：
    1.时间复杂度：O(n²)（平均/最坏），O(n)（最好）。
    2.空间复杂度：O(1) (原地排序)。

四、特点：
    1.稳定排序
    2.应用场景：小规模数据或基本有序序列（如优化快速排序的小数组处理）。

四、插入排序的改进————折半插入排序
    1.核心思想：在已排序部分使用二分查找确定插入位置，然后移动元素并插入。

    2.算法步骤：
        (1)从第二个元素开始（i=1），将其作为待插入元素key
        (2)在已排序区间[0, i-1]中使用二分查找：
            a. 设置low=0, high=i-1
            b. 当low≤high时：
                    mid = (low+high)/2
                    如果key < arr[mid]，则high = mid-1
                    否则，low = mid+1
            c. 循环结束时，low的位置就是key应该插入的位置
        (3)将[low, i-1]区间的元素全部右移一位
        (4)将key放入arr[low]位置
        (5)重复1-4，直到所有元素处理完毕

    3.复杂度：
        (1)时间复杂度：
            比较次数：O(n log n)
            移动次数：O(n²)
            总时间复杂度：O(n²)
        (2)空间复杂度：O(1) (原地排序)。

    4.特点：
        (1)稳定排序
        (2)数据基本有序或对稳定性有要求时效果较好。
*/
#include <stdio.h>

// ================================== 插入排序 =====================================
void insertSort(int* data, int len)
{
    int key; // 用于暂存当前待插入的元素
    for (int i = 1; i < len; i++) // 从第二个元素开始逐个插入
    {
        key = data[i];          // 将当前元素保存为 key
        int j = i - 1;          // 从已排序序列的最后一个元素开始向前比较

        // 向前查找插入位置，移动比 key 大的元素
        while(j >= 0 && data[j] > key)
        {
            data[j+1] = data[j]; // 将比 key 大的元素后移
            j--;                 // 向前继续比较
        }

        // 找到插入位置后，将 key 插入
        data[j+1] = key;
    }
}


// ================================== 折半插入排序 =====================================
void binaryInsertSort(int* data, int len)
{
    int low, high, mid;
    int key;

    // 从第二个元素开始遍历，将其插入到前面已经排好序的子序列中
    for (int i = 1; i < len; i++)
    {
        key = data[i];      // 记录当前待插入的值
        low = 0;            // 设置当前有序序列的最小下标
        high = i - 1;       // 设置当前有序序列的最大下标

        // 使用折半查找法找出 key 应该插入的位置（即 low 最终的位置）
        while(low <= high)
        {
            mid = (low + high) / 2;
            if (data[mid] > key)
            {
                high = mid - 1; // 插入点在左半边
            }
            // 注意：当data[mid] = key时也进行low = mid + 1操作，因为这样才是稳定排序
            else 
            {
                low = mid + 1;  // 插入点在右半边
            }
        }

        // 从后往前依次将大于 key 的元素后移，为 key 腾出位置
        int j = i - 1;
        while(j >= low)
        {
            data[j+1] = data[j];
            j--;
        }

        // 插入 key 到正确的位置
        data[low] = key;
    }
}



int main(int argc, char const *argv[])
{
    // 数组建立
    int data1[] = {47, 35, 60, 95, 77, 15, 28}; // 初始化数组
    int len1 = sizeof(data1) / sizeof(data1[0]);  // 计算数组长度

    int data2[] = {47, 35, 60, 95, 77, 15, 28}; // 初始化数组
    int len2 = sizeof(data2) / sizeof(data2[0]);  // 计算数组长度


    // 1. 插入排序
    insertSort(data1, len1); 

    // 输出排序后的结果
    for(int i = 0; i < len1; i++)
    {
        printf("%d ", data1[i]); // 15 28 35 47 60 77 95
    }
    printf("\n");


    // 2. 折半插入排序
    binaryInsertSort(data2, len2);

    // 输出排序后的结果
    for(int i = 0; i < len2; i++)
    {
        printf("%d ", data2[i]); // 15 28 35 47 60 77 95
    }
    
    return 0;
}