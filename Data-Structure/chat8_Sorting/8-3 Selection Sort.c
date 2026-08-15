/*
选择排序(Selection sort)：
一、核心思想：在未排序序列中找出最小（大）元素，存放到排序序列的起始位置，然后继续从剩余未排序元素
    中寻找最小（大）元素，放到已排序序列的末尾。

二、算法步骤：
    1. 初始状态：整个数组为未排序部分
    2. 从索引i=0开始，遍历n-1轮（最后一次只剩1个元素，自动有序）
    3. 每轮操作：
        a. 假设当前位置i的元素为最小值
        b. 在[i, n-1]范围内通过比较操作寻找实际的最小值索引
        c. 如果找到的最小值不在位置i，则交换两者
    4. 重复直到所有元素有序

三、复杂度：
    1.时间复杂度：O(n²)（任何情况）。
    2.空间复杂度：O(1) (原地排序)。

四、特点：
    1.不稳定排序。
    2.应用场景：数据量小且对稳定性无要求。
*/
#include <stdio.h>

// 交换数组中下标的为 m 和 n 的两个元素
void swap(int* data, int m, int n)
{
    int temp = data[m];
    data[m] = data[n];
    data[n] = temp;
}

// 简单选择排序函数
void selectSort(int* data, int len)
{
    int min; // 记录最小值的下标

    // 外层循环：控制每一轮的起始位置
    for (int i = 0; i < len; i++)
    {
        // 假设当前位置 i 是最小值
        min = i;
        // 内层循环：从当前位置 i 向后寻找最小值的位置
        for (int j = i; j < len; j++)
        {
            // 如果发现比当前最小值还小的元素，更新最小值的位置
            if (data[min] > data[j])
            {
                min = j;
            }
        }
        // 如果找到的最小值不是当前位置，则进行交换
        if (i != min)
        {
            swap(data, i, min);
        }
    }
}



int main(int argc, char const *argv[])
{
    // 初始化数组
    int data[] = {47, 35, 60, 95, 77, 15, 28};
    // 计算数组长度
    int len = sizeof(data) / sizeof(data[0]);
    // 执行选择排序
    selectSort(data, len);
    // 输出排序后的结果
    for(int i = 0; i < len; i++)
    {
        printf("%d ", data[i]); // 15 28 35 47 60 77 95
    }
    return 0;
}