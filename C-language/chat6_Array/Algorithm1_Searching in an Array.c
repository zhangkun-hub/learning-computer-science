/*
数组的查找算法：基本查找、二分查找、插值查找、
                分块查找、哈希查找、树表查找、斐波那契查找
以下只介绍前三种，后四种以后会介绍

1.基本查找(顺序查找)：按照数组索引顺序一个一个查找，如果找到了，就返回数据对应的索引。

2.二分查找(折半查找)：每次通过中间索引的元素值与查找值进行比较来排除一半的查找范围。
            前提条件：数据排列必须有序(比如从小到大排列)。

3.插值查找(二分查找改进)：通过数组两端点求索引与元素的线性关系,将查找值代入求出索引,最后二分查找。
        注：1.前提条件：数据排列必须有序(比如从小到大排列)，且尽可能线性均匀一点。

            2.线性公式：mid = min + (num - arr[min]) * (max - min) / (arr[max] - arr[min])。
                    其中mid便是二分查找的中间索引，num为要查找的数据值。
*/
#include<stdio.h>


// 每个方法都定义一个函数，用于查找数组中的数据num，并返回所在的索引，如果数组中没有num，则返回-1
// 1.基本查找函数
int order(int arr[], int len, int num);

// 2.二分查找函数
int binarySearch(int arr[], int len, int num);

// 3.插值查找函数
int interpolationSearch(int arr[], int len, int num);

int main()
{
    // 示例1 基本查找
    printf("------------- 示例1 --------------\n");  
    // 1.定义数组
    int arr[] = {11,22,55,77,44};
    int len = sizeof(arr) / sizeof(int);    

    // 2.定义变量表示要查找的数据
    int num = 22;

    // 3.调用基本查找函数order查找数据
    int index = order(arr,len,num);

    // 4.输出索引
    printf("%d\n", index);
    printf("\n");


    // 示例2 二分查找
    printf("------------- 示例2 --------------\n");  
    // 1.定义数组
    int arr2[] = {7,23,79,81,103,127,131,147};    
    int len2 = sizeof(arr2) / sizeof(int);

    // 2.定义变量表示要查找的数据
    int num2 = 131;

    // 3.调用二分查找函数binarySearch查找数据
    int index2 = binarySearch(arr2,len2,num2);

    // 4.输出索引
    printf("%d\n", index2);
    printf("\n");


    // 示例3 插值查找
    printf("------------- 示例3 --------------\n");  
    // 1.定义数组
    int arr3[] = {7,23,79,81,103,127,131,147};    
    int len3 = sizeof(arr3) / sizeof(int);

    // 2.定义变量表示要查找的数据
    int num3 = 147;

    // 3.调用插值查找函数interpolationSearch查找数据
    int index3 = interpolationSearch(arr3,len3,num3);

    // 4.输出索引
    printf("%d\n", index3);

    return 0;
}

// 基本查找函数
int order(int arr[], int len, int num)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return -1;
}

// 二分查找函数
int binarySearch(int arr[], int len, int num)
{
    // 1.确定查找范围
    int min = 0;
    int max = len - 1;

    // 2.利用循环不断地进行查找
    while (min <= max)
    {
        // 确定中间变量
        int mid = (min + max) / 2;
        // 比较(注意，mid是索引不是数据)
        if (arr[mid] < num)
        {
            // 要查找数据在右边
            min = mid + 1;
        }
        else if (arr[mid] > num)
        {
            // 要查找数据在左边
            max = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    // 3.如果min大于max，表示数据不存在，返回-1
    return -1;
}


// 插值查找函数(只需要将二分查找函数的mid计算公式改成上面的线性公式即可)
int interpolationSearch(int arr[], int len, int num)
{
    // 1.确定查找范围
    int min = 0;
    int max = len - 1;

    // 2.如果查找值超出数组最大最小值，表示数据不存在，返回-1
    if (num > arr[max] || num < arr[min])
    {
        return -1;
    }
    
    // 3.利用循环不断地进行查找
    while (min <= max)
    {
        // 确定中间变量(改进线性插值公式计算mid)
        int mid = min + (num - arr[min]) * (max - min) / (arr[max] - arr[min]);

        // 比较(注意，mid是索引不是数据)
        if (arr[mid] < num)
        {
            // 要查找数据在右边
            min = mid + 1;
        }
        else if (arr[mid] > num)
        {
            // 要查找数据在左边
            max = mid - 1;
        }
        else
        {
            return mid;
        }
    }
}