/*
一、typedef关键字：
    1.定义：用于为已有的数据类型创建新的名称（别名）。它不创建新类型，只是为现有类型提供替代名称。

    2.使用方式：typedef 已有类型a 新类型名;  // 此后凡是使用类型a，便可直接用新类型名表示。
        比如：
            typedef int ElemType;   // 给int类型起了个ElemType别名
            ElemType a = 10;     // 创建int类型变量a(可以用int的别名ElemType创建)

    3.作用：
        (1)提高代码可读性；
        (2)增强代码可维护性，比如以下代码，只需修改第一行float类型即可全局改变类型：
            typedef float ElemType;  // 如需改为double，只需修改此处float即可
            ElemType salary = 5000.0;

    4.使用范围：
        1.各种数据类型(结构体本身就是数据类型,具体使用见下面第二部分)

        2.指针类型，比如：
            typedef char* String;    // String是指针char*的别名
            String name = "Alice";   // 用别名String创建字符串。

        3.数组(因为本质就是指针)，比如：
            typedef int Vector[3];       // Vector是包含3个int的数组类型
            typedef float Matrix[3][3];  // Matrix是3×3浮点矩阵
            // 使用别名数组
            Vector v = {1, 2, 3};
            Matrix m = {{0}};


二、结构体的起别名操作：
    1.定义：通过别名来简化结构体数据类型的引用与结构体变量的引用。

    2、语法：
        (1)结构体别名的格式
            typedef struct [结构体名字]     # []内容表示可写可不写，随意
            {
                成员1;
                成员2;
                ...
            }别名;

        (2)用结构体别名定义结构体变量与赋值：
            别名 结构体变量名 = {值1, 值2,...};
*/
#include<stdio.h>
#include<string.h>

// 示例1中typedef关键字的使用
// 在main函数外使用typedef关键字起别名，则该别名全局可用
typedef int ElemType;
typedef char* String;
typedef int Vector[3];
typedef float Matrix[3][3];


// 示例2的结构体起别名操作
// 在main函数外定义结构体，则具有全局变量的性质
typedef struct Ultraman   // Ultraman也可以去掉不写
{
    char name[100];
    int attack;
    int defense;
    int blood;
} M;


int main()
{
    // 示例1 typedef关键字的使用
    printf("------------- 示例1 --------------\n");    
    ElemType a = 10;
    String name = "Alice";
    Vector v = {1, 2, 3};
    Matrix m = {{0}};
    printf("%d\n", a);           // 10
    printf("%s\n", name);        // Alice
    printf("%d\n", v[0]);        // 1
    printf("%d\n", v[1]);        // 2
    printf("%d\n", v[2]);        // 3 
    printf("%f\n", m[0][0]);     // 0.0000000


    // 示例2 结构体的起别名操作
    printf("------------- 示例2 --------------\n");   
    // 1.定义三个奥特曼
    M taro = {"泰罗", 100, 90, 500};
    M rem = {"雷欧", 90, 80, 450};
    M eddie = {"艾迪", 120, 70, 600};

    // 2.定义数组
    M arr[3] = {taro, rem, eddie};

    // 3.遍历数组
    for (int i = 0; i < 3; i++)
    {
        M temp = arr[i];
        printf("奥特曼的名字为%s，攻击力是%d，防御力是%d，血量是%d\n", 
            temp.name, temp.attack, temp.defense, temp.blood);
    }




    return 0;
}