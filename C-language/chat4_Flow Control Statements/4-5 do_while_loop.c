/*
一、do...while循环：先通过do执行一次循环体，然后再进行while循环，所以循环体至少会执行一次。

二、与for/while区别循环结构区别：
    在开头先执行循环体,之后则完全一样。(所以一般用于输入账号密码等先执行循环体再对循环体循环的场景)

三、do...while循环语法格式：
初始化语句;
do
{
    循环体语句;
    条件控制语句;
} while (条件判断语句);

*/
#include <stdio.h>

int main()
{
    // 利用do...while打印1~5
    int i = 1;
    do
    {
        printf("%d\n", i);
        i++;
    } while (i <= 5);

    return 0;
}