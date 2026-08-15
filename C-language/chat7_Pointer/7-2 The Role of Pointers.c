/*
指针的作用：
1.操作其他函数中的变量(关键点在与内存地址具有唯一性)
    注意：函数中的变量是局部变量，函数结束则变量也结束。此时在其他函数中，就无法通过指针使用了，
            如果不想使函数中的变量被回收，可以在变量定义前面加static关键字成为全局变量

2.函数返回多个值(因为正常函数只能返回一个值)

3.函数的结果和计算状态分开()

4.方便的操作数组和函数(该内容具体见后面3-5节内容)
*/
#include<stdio.h>

void swap(int* p1, int* p2);   // 变量数据交换函数

int* method();   // 具有全局变量static的函数

void getMaxAndMin(int arr[], int len, int* max, int* min);   // 求最大值和最小值的函数

int getRemainder(int num1, int num2, int* res);  // 求余数的函数

int main()
{
    // 示例1 指针的作用1：操作其他函数中的变量
    printf("------------- 示例1 --------------\n");   
    // 1.定义两个变量
    int a = 10;
    int b = 20;

    // 2.调用swap函数
    printf("调用前：%d, %d\n", a, b); // 调用前：10, 20
    swap(&a, &b); // 传递变量a跟b的内存地址
    printf("调用后：%d, %d\n", a, b); // 调用后：20, 10

    // 注意：函数中的变量是局部变量，如果要使函数里的变量不随函数而消失，则要成为全局变量
    int* p = method(); // method函数里有全局变量
    printf("%d\n", *p); 
    printf("\n");


    // 示例2 指针的作用2：函数返回多个值
    printf("------------- 示例2 --------------\n"); 
    // 1.定义数组
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int len = sizeof(arr) / sizeof(int);

    // 2.调用getMaxAndMin函数求最大值和最小值
    int max = arr[0];
    int min = arr[0];
    getMaxAndMin(arr, len, &max, &min);

    printf("数组的最大值为：%d\n", max);
    printf("数组的最小值为：%d\n", min);
    printf("\n");


    // 示例3 指针的作用3：函数的结果和计算状态分开
    printf("------------- 示例3 --------------\n"); 
    // 1.定义两个变量
    int a2 = 10;
    int b2 = 3;
    int b3 = 0;
    int res1 = 0;
    int res2 = 0;

    // 2.调用函数获取余数
    int flag1 = getRemainder(a2, b2, &res1);  // flag是状态，0表示正常，1表示不正常(除数为0)
    int flag2 = getRemainder(a2, b3, &res2);

    // 3.对状态进行判断
    if (!flag1)
    {
        printf("获取到的余数为：%d\n", res1);
    }
    else
    {
        printf("错误，余数为0\n");
    }

    if (!flag2)
    {
        printf("获取到的余数为：%d\n", res2);
    }
    else
    {
        printf("错误，除数为0\n");
    }


    return 0;
}


// 形参为两个指针变量，而调用该函数所传递的是两变量的内存地址(注意：内存地址具有唯一性)
void swap(int* p1, int* p2)  
{
    // 此时交换的是p1指向的变量和p2指向的变量的值
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


int* method()  
{
    static int a = 10;  // 全局变量，此时变量一直保存到程序结束
    return &a;
}


void getMaxAndMin(int arr[], int len, int* max, int* min) 
{
    // 求数组的最大值
    *max = arr[0];

    for (int i = 1; i < len; i++)
    {
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
    }

    // 求数组的最小值
    *min = arr[0];

    for (int i = 1; i < len; i++)
    {
        if (arr[i] < *min)
        {
            *min = arr[i];
        }
    }    
}


int getRemainder(int num1, int num2, int* res)  
{
    if (num2 == 0) // 除数不能为0
    {   
        // 停止
        return 1;
    }
    *res = num1 % num2;
    return 0;
    // 返回值：表示计算的状态，0为正常，1为不正常

}