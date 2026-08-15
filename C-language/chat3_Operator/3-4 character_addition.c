/*
字符的算术运算操作：
一、两字符(或字符与整型)算术运算操作：
    先将字符通过ASCII码转换成数字，再进行算术运算，最后以int类型返回该结果。

二、给字符类型变量赋值整型数字：也是通过ASCII码转换成对应字符再赋值。
*/

//
//
#include<stdio.h>

int main()
{
    //字符对应数字的结果
    printf("%d\n", 'a'); // 97
    printf("%d\n", 'A'); // 65
    printf("%d\n", '0'); // 48
    printf("%d\n", '4'); // 52
    printf("------------------------\n");

    char a = 'x';
    char b = 'y';
    char c = '4';
    char d = '0';
    int i = a + b;
    int j = a + 1;
    int k = c - d;
    int l = c * d;
    printf("%d\n", i); // 241
    printf("%d\n", j); // 121
    printf("%d\n", k); // 4
    printf("%d\n", l); // 2496 = 52(4的ASCII码) * 48(0的ASCII码)

    return 0;
}