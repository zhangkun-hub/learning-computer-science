/*
一、字符串的常见函数：(需要用到string.h库)
1.strlen：获取字符串的长度(注意：结束标记\0不会计算，也就是本身字符串的长度)；

2.strcat：拼接两个字符串(即将第二个字符串中的全部内容，拷贝到第一个字符串的末尾)；
            条件:1.第一个字符串必须是可以修改的，也就是不能是指针定义；
                2.第一个字符串中剩余的空间要求能容纳拼接的第二个字符串。

3.strcpy：复制字符串(即将第二个字符串中的全部内容，拷贝到第一个字符串中，并将原有内容给覆盖了)；
            条件:1.第一个字符串必须是可以修改的，也就是不能是指针定义；
                2.第一个字符串中剩余的空间要求能容纳第二个字符串的长度。

4.strcmp：比较两个字符串是否相同(完全一样返回0，只要有一个不一样则非0)；
        细节:除了内容外，顺序也必须完全一样，才能叫字符串一样

5.strlwr：将字符串变成小写；
        细节:1.只能转换英文的大小写，不能修改中文的大小写；
            2.如果没有修改，指针定义也可以使用，但如果有修改，则不能用指针定义字符串。

6.strupr：将字符串变成大写。
        细节:1.只能转换英文的大小写，不能修改中文的大小写；
            2.如果没有修改，指针定义也可以使用，但如果有修改，则不能用指针定义字符串。

二、这些函数的使用方式：必须先导入头文件<string.h>才能使用。具体见下面例子
*/
#include<stdio.h>
#include<string.h>

int main()
{
    char* str1 = "abc";                        // 字符串的定义格式2（指针定义）
    char str2[100] = "abc";                    // 字符串的定义格式1
    char str3[5] = {'q', 'w', 'e', 'r', '\0'}; // 字符串的定义格式1
    char str4[100] = "abc";

    printf("--------------------strlen（长度）----------------------\n");
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = strlen(str3);

    printf("%d\n", len1); // 3
    printf("%d\n", len2); // 3
    printf("%d\n", len3); // 4

    printf("--------------------strcat（拼接）----------------------\n");
    strcat(str2, str3);
    printf("%s\n", str2); // abcqwer
    printf("%s\n", str3); // qwer

    printf("--------------------strcpy（拷贝）----------------------\n");
    strcpy(str2, str3);
    printf("%s\n", str2); // qwer
    printf("%s\n", str3); // qwer

    printf("--------------------strcmp（比较）----------------------\n");
    int res1 = strcmp(str1, str2); // 注意，此时str2 = "qwer"
    int res2 = strcmp(str1, str4);   
    printf("%d\n", res1); // -1
    printf("%d\n", res2); // 0

    printf("--------------------strlwr（变小写）----------------------\n");
    char str5[100] = "Abc";
    strlwr(str5); 
    printf("%s\n", str5); // abc

    printf("--------------------strupr（变大写）----------------------\n");
    strupr(str5);
    printf("%s\n", str5); // ABC



    return 0;
}