/*
一、C语言的使用手册地址：http://zh.cppreference.com
        (有各种疑惑都可以看该内容得到解答)

二、头文件：头文件是C语言中一种特殊的源文件，通常以.h为扩展名，除了c语言自带的也可以自定义头文件。
        主要用于声明程序元素（如函数、变量、宏定义、结构体等），而不是定义实现。

三、头文件作用作用：
    1.声明函数接口；
    2.定义宏和常量；
    3.定义数据类型；
    4.包含其他头文件。

四、头文件的类型(注意：系统/库头文件用尖括号 <> 声明；自定义头文件用双引号 "" 声明)：
    1.c语言库头文件：
        #include <stdio.h>     // 标准输入输出
        #include <stdlib.h>    // 标准库函数
        #include <string.h>    // 字符串处理
        #include <math.h>      // 数学函数     
    2.系统头文件：
        #include <windows.h>   // Windows API
        #include <unistd.h>    // Unix标准函数
    3.自定义头文件：
        #include "myheader.h"  // 用户自定义

五、详细举例C语言自带的常用头文件：
    1.stdio.h：
        (1)printf()：打印；
        (2)scanf()：输入。

    2.math.h：
        (1)pow()：幂；
        (2)sqrt()：平方根；
        (3)ceil()：向上取整(进一法)；
        (4)floor()：向下取整(去尾法)；
        (5)abs()：整数类型取绝对值。

    3.time.h：
        time()：获取当前时间。
*/
#include <stdio.h>
#include <math.h>
#include <time.h>

int main()
{
    // 一、math.h头文件
    // 1.pow() 幂运算
    double res1 = pow(2, 3);
    printf("%lf\n", res1);

    // 2.sqrt() 平方根
    double res2 = sqrt(8);
    printf("%lf\n", res2);

    // 3.ceil() 向上取整(进一法)，比如12.3或12.7向上取整都为13
    double res3 = ceil(12.3);
    printf("%lf\n", res3);

    // 4.floor() 向上取整(去尾法)，比如12.3或12.7向下取整都为12
    double res4 = floor(12.7);
    printf("%lf\n", res4);

    // 5.abs() 整数类型取绝对值
    int res5 = abs(-13);
    printf("%d\n", res5);

    // 二、time.h头文件
    // time函数：形参表示获取的当前时间是否需要在其他地方进行存储，一般不需要，所以写 NULL
    //          返回值a：long long类型。含义：从c语言诞生1970.1.1开始，过了a秒。
    long long res = time(NULL);
    printf("%lld\n", res);  // 输出结果可以用工具狗网站的时间戳转换器来验证和转换

    return 0;
}