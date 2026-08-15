#include<stdio.h>
#include <stdlib.h> 
#include <time.h>

int main()
{
    // 示例1 求数组的最大值
    printf("------------- 示例1 --------------\n");  
    // 1.定义数组
    int arr[] = {33, 5, 22, 44, 55};
    int len = sizeof(arr) / sizeof(int);    

    // 2.定义变量max，记录数组最大值，其中初始化为数组第1个元素
    int max = arr[0];

    // 3.遍历数组的每个元素,拿着遍历的元素跟max比较,如果小于等于max,不做处理,大于max则赋值给max
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    // 4.输出max
    printf("数组arr的最大值为：%d\n", max);
    printf("\n");


    // 示例2 数组的遍历求和
    printf("------------- 示例2 --------------\n");  
    // 1.定义数组
    int arr2[10] = {0};    
    int len2 = sizeof(arr2) / sizeof(int);

    // 2.生成10个1~100之间的随机数存入数组
    // 设置种子
    srand(time(NULL));
    // 生成随机数
    for (int i = 0; i < len2; i++)
    {
        int num = rand() % 100 + 1;
        // 把随机数存入数组
        arr2[i] = num;
    }

    // 3.利用累加思想求数组中的所有数据的和
    int sum = 0;
    for (int i = 0; i < len2; i++)
    {
        sum = sum + arr2[i];
    }

    // 4.输出
    printf("数组元素的和：%d\n", sum);


    return 0;
}