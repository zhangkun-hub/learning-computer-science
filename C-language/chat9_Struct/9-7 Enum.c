/*
一、枚举型(Enum)：用于定义一组具体名字的整型常量，使代码更易读和维护。

二、使用方式：
    1.格式：
        enum 枚举名 {
            标识符1,     // 默认被赋值为0
            标识符2,     // 默认被赋值为1
            ...
        };

        注：各标识符的值也可以自己设定(但必须是整型)，比如：标识符1 = 100,...

    2.声明枚举变量：enum 枚举名 变量名 = 标识符i;  # 此时便把标识符i的值赋值给枚举变量

    3.起别名：格式与结构体基本一致。


三、共用体的特点：
    1.本质是整型常量：枚举值实际上是int类型，可以直接参与整数运算。

    2.自动递增：未指定值的枚举项会自动比前一项大1。

    3.类型安全较弱：C语言中枚举变量可被赋任意整数值(如today = 100)，虽不会报错，但可能破坏语义。

    4.作用域独立：枚举成员属于全局作用域(C语言中)，需注意命名冲突。

    5.内存存储：枚举变量占int大小，存储单个整数值(因为枚举变量只能赋值一个标识符的值)。
*/
#include<stdio.h>

// 示例1枚举型
enum weekday {
    MONDAY,    // 0
    TUESDAY,   // 1
    WEDNESDAY, // 2
    THURSDAY,  // 3
    FRIDAY,    // 4
    SATURDAY,  // 5
    SUNDAY     // 6
};

// 示例2枚举型
typedef enum year{
    last_year = 1999,
    this_year,  // 未指定值的枚举项自动比前一项大1，即2000
    next_year = 2002
}year;


int main()
{  
    // 示例1 枚举型的默认值使用
    printf("------------- 示例1 --------------\n");  
    enum weekday a;
    a = MONDAY;
    enum weekday b;
    b = TUESDAY;
    
    printf("%d\n", a); // 0
    printf("%d\n", b); // 1


    // 示例2 枚举型的赋值使用
    printf("------------- 示例2 --------------\n");  
    year x = last_year;
    year y = this_year;
    year z = next_year;

    printf("%d\n", x); // 1999
    printf("%d\n", y); // 2000
    printf("%d\n", z); // 2002


    return 0;
}