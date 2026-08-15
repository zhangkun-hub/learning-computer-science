/*
冒泡排序(Bubble sort)：
一、定义：冒泡排序（Bubble Sort）是一种简单的比较交换排序算法。它重复遍历待排序序列，比较相邻的
    两个元素，如果它们的顺序错误就交换位置，使得较大的元素像气泡一样逐渐“浮”到序列的顶端（或较小
    元素“沉”到底端）。

二、算法步骤：
    1.第一轮遍历：
        从第一个元素开始，比较相邻的 arr[0]和 arr[1]
        如果 arr[0] > arr[1]，则交换它们
        继续比较 arr[1]和 arr[2]，依此类推
        第一轮结束后，最大的元素会移动到末尾

    2.后续轮次：
        对剩余未排序部分重复上述过程
        每轮遍历的范围逐渐减小（因为末尾已有序）

    3.优化：
        设置标志位，如果某一轮没有发生任何交换，说明序列已完全有序，可提前结束

三、复杂度：
    1.时间复杂度：O(n²)（平均/最坏），O(n)（最好，已有序时）。
    2.空间复杂度：O(1) (原地排序)。

四、特点：
    1.稳定排序。
    2.应用场景：教学示例或小规模基本有序数据。
*/
#include <stdio.h>

// 交换数组中下标为 m 和 n 的两个元素的值
void swap(int* data, int m, int n)
{
    int temp = data[m];
    data[m] = data[n];
    data[n] = temp;
}

// 实现冒泡排序：将数组 data 中的元素按升序排列
void bubbleSort(int* data, int len)
{
    // 外层循环控制“趟数”，共需 len 次比较（严格来说是 len - 1 次）
    for (int i = 0; i < len; i++)
    {
        // 内层循环控制每趟中相邻元素的比较和交换
        // 每次比较到 len - i - 1，因为右侧已经排好序
        for(int j = 0; j < len - i - 1; j++)
        {
            // 如果前一个元素比后一个大，则交换它们
            if (data[j] > data[j + 1])
            {
                swap(data, j, j+1); // 调用 swap 函数进行交换
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    // 定义待排序的整数数组
    int data[] = {47, 35, 60, 95, 77, 15, 28};

    // 计算数组中元素的个数
    int len = sizeof(data) / sizeof(data[0]);

    // 调用冒泡排序函数进行排序
    bubbleSort(data, len);

    // 输出排序后的数组
    for(int i = 0; i < len; i++)
    {
        printf("%d ", data[i]); // 15 28 35 47 60 77 95
    }

    return 0;
}