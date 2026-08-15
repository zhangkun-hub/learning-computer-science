/*
一、函数指针：
    1.格式：返回值类型 (*指针名) (形参类型列表) = 函数名     # 注意形参的名字要去掉

    2.作用：利用函数指针，可以动态调用函数

二、函数指针数组：
    1.格式：返回值类型 (*指针名[n]) (形参类型列表) = {函数名1,函数名2,...,函数名n};

    2.条件：只有形参的数目和类型完全相同,且返回值数目类型也一样的函数,才能放到同一个函数指针数组中
*/
#include<stdio.h>

// 示例1的两个函数
void method1();
int method2(int num1, int num2);

// 示例2的四个函数
int add(int numm1, int num2);
int subtract(int numm1, int num2);
int mutiply(int numm1, int num2);
int divide(int numm1, int num2);

int main()
{
    // 示例1 函数指针与调用函数
    printf("------------- 示例1 --------------\n");
    // 1.定义指针指向两个函数
    void (*p1)() = method1;
    int (*p2)(int, int) = method2;

    // 2.利用函数指针去调用函数
    p1();                  // method1
    int num = p2(10, 20);  // method2
    printf("%d\n", num);   // 30



    
    // 示例2 函数指针数组
    printf("------------- 示例2 --------------\n");
    /*
    题目：定义加、减、乘、除四个函数
        要求：用户键盘录入三个数字，前两个表示参与计算的数字，第三个表示调用的函数，
        第三数字示例：1: 加法；2: 减法；3: 乘法；4: 除法
    */
    // 1.定义一个数组去装四个函数的指针(也叫函数指针数组)
   int (*arr[4])(int, int) = {add, subtract, mutiply, divide};

    // 2.用户录入三个数据
    printf("请录入两个数字参与计算\n");
    int num1;
    int num2;
    scanf("%d%d", &num1, &num2);

    printf("请录入一个数字表示要进行的计算(1:加法; 2:减法; 3.乘法; 4.除法)\n");
    int choose;
    scanf("%d", &choose);

    // 3.根据用户的选择，来调用不同的函数
    int res = (arr[choose - 1])(num1, num2);  // 索引从0开始，所以为choose - 1

    // 4.输出打印
    printf("计算结果为：%d\n", res);


    return 0;
}

// 示例1的两个函数
void method1()
{
    printf("method1\n");
}


int method2(int num1, int num2)
{
    printf("method2\n");
    return num1 + num2;
}

// 示例2的四个函数
int add(int num1, int num2)
{
    return num1 + num2;
}

int subtract(int num1, int num2)
{
    return num1 - num2;
}

int mutiply(int num1, int num2)
{
    return num1 * num2;
}

int divide(int num1, int num2)
{
    return num1 / num2;
}