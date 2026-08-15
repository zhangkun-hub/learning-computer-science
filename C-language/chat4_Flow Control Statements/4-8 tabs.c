/*
\t(制表符)：长度可变的大空格。
    原理：会根据前字母的个数在后面补空格，让整体的长度达到8或者8的倍数，最少补1个，最多补8个。
            注意:1.前面字母长度已经达到8，则会直接补长度为8的空格；
                2.汉字的长度是2.
    作用：打印表格数据的时候，可以对齐。
*/
#include <stdio.h>

int main()
{
    printf("name\t\tage\tgender\thobby\n");
    printf("zhangkun\t23\t男\t篮球\n");

    return 0;
}