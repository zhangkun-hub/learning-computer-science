/*
二分查找(折半查找)：
一、核心思想：在有序顺序表中，每次与中间元素比较，根据比较结果将查找范围缩小一半。

二、时间复杂度：平均：O(log n)；最坏：O(log n)

三、特点：
    1.优点：效率极高。
    2.缺点：(1)要求数据必须有序(无序的数据使用二分查找完全无意义)，
            (2)必须支持随机访问(如数组)，插入删除困难。

四、算法步骤：
    1. 设定查找的起始下标为low, 结束下标为high。
    2. 计算中间下标：mid = (low+high)/2 （向下取值，例如4.5取4）。
    3. 比较 array[mid] 与目标值：
        - 相等则返回 mid。
        - 若目标值更大，则 low = mid + 1，在右半区重复步骤2。
        - 若目标值更小，则 high = mid - 1，在左半区重复步骤2。
    4. 当 low > high时，查找失败。
*/
#include <stdio.h>

// 二分(折半)查找函数
// 参数：data:查找表 n:表中元素个数 value:要查找的内容
// 返回值：返回找到的元素下标(没有则返回-1)
int binary_search(int* data, int len, int value)
{
    int low = 0;        // 查找表的起始下标为low
    int high = len - 1; // 假设查找表的结束下标为high
    int mid;

    // 进行二分查找(折半查找)
    while(low <= high)
    {
        mid = (low + high) / 2; // 计算中间下标: mid = (low + high) / 2
        if (value > data[mid])
        {
            low = mid + 1;  // 如果关键字大于a[mid]，则在右半部分继续查找，令low = mid + 1
        }
        else if(value < data[mid])
        {
            high = mid - 1; // 如果关键字小于data[mid]，则在左半部分继续查找，令high = mid - 1
        }
        else
        {
            return mid; // 如果关键字等于data[mid]，查找成功，返回下标
        }
    }
    return -1;
}



int main(int argc, char const *argv[])
{
    int arr[] = {2, 13, 22, 38, 46, 58, 66, 77, 85, 98}; // 查找表
    int len = sizeof(arr) / sizeof(arr[0]);  // 数组长度
    int pos = binary_search(arr, len, 66);   // 调用函数查找66
    printf("%d\n", pos); // 6


    return 0;
}