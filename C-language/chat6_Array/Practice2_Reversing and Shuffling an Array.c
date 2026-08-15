#include<stdio.h>
#include <stdlib.h> 
#include <time.h>

int main()
{
    // 示例1 反转数组
    printf("------------- 示例1 --------------\n");  
    // 1.定义数组
    int arr[] = {33, 5, 22, 44, 55};
    int len = sizeof(arr) / sizeof(int);    

    // 2.遍历打印数组
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");

    // 3.反转数组(从两端索引元素开始交换，然后索引依次向内靠拢进行元素交换)
    int l = 0;
    int m = len - 1;
    while (l < m)
    {
        int temp = arr[l]; // 交换变量的过程中需要新变量进行临时储存
        arr[l] = arr[m];
        arr[m] = temp;

        l++;
        m--;
    }

    // 4.遍历打印数组
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");


    // 示例2 打乱数组
    printf("------------- 示例2 --------------\n");  
    // 1.定义数组
    int arr2[] = {1, 2, 3, 4, 5};    
    int len2 = sizeof(arr2) / sizeof(int);

    // 2.遍历数组，得到每个元素，让这个元素跟随机索引处的元素进行交换
    // 设置种子
    srand(time(NULL));
    for (int i = 0; i < len2; i++)
    {
        // 获取随机索引，索引范围0~4
        int index = rand() % len2;
        // 拿着i指向的元素，跟index指向的元素进行交换
        int temp = arr2[i]; 
        arr2[i] = arr2[index];
        arr2[index] = temp;
    }

    // 4.遍历打印数组
    for (int i = 0; i < len2; i++)
    {
        printf("%d\n", arr2[i]);
    }



    return 0;
}