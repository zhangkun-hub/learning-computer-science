/*
一、共用体(也叫联合体、共同体，Union)：适用于一种数据可能有多种类型的情形。

二、使用方式：
    1.格式：与结构体基本一致，只需要把结构体的struct改成union即可。

    2.赋值：每次只能给共用体的一个数据类型进行赋值，因为给下一个数据赋值完会覆盖上一个数据。

    3.起别名：格式与结构体基本一致。


三、共用体的特点：
    1.所以变量都使用同一个内存空间(共享内存)；

    2.所占内存大小 = 最大成员的长度（也受内存对齐的影响，即最终总大小是最宽成员的整数倍）；
        注：最大成员与最宽成员有区别：比如示例2中100长度的字符串是最大成员，但double是最宽成员。

    3.每次只能给一个变量进行赋值，因为第二个变量会覆盖原有的数据。

    
四、与结构体的区别：
    结构体:
        1.特点：是一种事物中包含多个属性；
        2.存储方式：各存各的。
        3.内存占用：各个变量的总和（受内存对齐影响）。

    共用体:
        1.特点：是一个属性有多种类型；
        2.存储方式：存一起，多次存会覆盖；
        3.内存占用：最大类型（受内存对齐影响）。
*/
#include<stdio.h>
#include<string.h>


// 示例1的共用体
union MoneyType1
{
    int moneyi;
    double moneyd;
    char moneystr[100];
};

// 示例2的共用体
union MoneyType2
{
    int moneyi;
    double moneyd;
    char moneystr[100];
};


int main()
{
    // 示例1 共用体的使用
    printf("------------- 示例1 --------------\n");   
    // 1.利用共用体定义钱的变量
    union MoneyType1 money1;

    // 2.赋值
    // money1.moneyi = 9999;
    // money1.moneyd = 123.32;
    strcpy(money1.moneystr, "100万");


    // 3.打印
    // printf("%d\n", money1.moneyi);
    // printf("%lf\n", money1.moneyd);
    printf("%s\n", money1.moneystr);


    // 示例2 共用体的内存占用情况
    printf("------------- 示例2 --------------\n");  
    // 1.利用共用体定义钱的变量
    union MoneyType2 money2;  
    
    // 2.获取内存地址
    printf("%p\n", &(money2.moneyi));   // 000000000061FD70
    printf("%p\n", &(money2.moneyd));   // 000000000061FD70
    printf("%p\n", &(money2.moneystr)); // 000000000061FD70

    printf("%zu\n", sizeof(money2.moneyi));   // 4
    printf("%zu\n", sizeof(money2.moneyd));   // 8
    printf("%zu\n", sizeof(money2.moneystr)); // 100
    printf("%zu\n", sizeof(money2));          // 104
    /*
    解释：
        共用体成员中最大成员为字符串，所占内存为100，但因为其本质是100个字符组成的数组，
        所以其宽度实际为1字节，而最宽成员为double，为8字节，
        由于共用体所占最终内存必须为最宽成员的整数倍，而100不是8的整数倍，所以需补位到104才行。
    */


    // 3.第二个变量会覆盖原有的数据
    money2.moneyi = 9999;
    money2.moneyd = 123.32;
    // printf("%d\n", money2.moneyi); // -515396076（内存覆盖导致错误结果）
    printf("%lf\n", money2.moneyd); // 123.320000


    return 0;
}