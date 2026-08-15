/*
一、结构体：
    1.可以理解为自定义的数据类型，跟int、char等数据类型同理(注意是数据类型而非变量)；
    2.是由一批数据组合而成的结构型数据；
    3.里面的每一个数据都是结构体的“成员”。

二、格式：
    1.定义：
        struct 结构体名字
        {
            成员1;
            成员2;
            ...
        }
    
    2.变量定义与赋值：
        格式1(定义赋值分步进行)：
            # 变量定义
            struct 结构体名字 结构体变量名;    

            # 变量赋值
            结构体变量名.成员1 = 值1;        
            结构体变量名.成员2 = 值2;
            ...
            (注意：对字符串的赋值不能直接用双引号赋值而是要用到strcpy函数，具体见示例1)

        格式2(定义赋值同步进行)：
            struct 结构体名字 结构体变量名 = {值1,值2,...}; 
            (注意：此时对于字符串可以直接用双引号""进行赋值)

三、结构体数组：
    格式：struct 结构体名字 结构体数组名[n] = {结构体变量1, 结构体变量2,...结构体变量n};


*/
#include<stdio.h>
#include<string.h>


// 在main函数外定义结构体，则具有全局变量的性质
// 示例1的结构体
struct GirlFriend
{
    char name[100];
    int age;
    char gender;
    double height;
};

// 示例2的结构体
struct Student
{
    char name[100];
    int age;
};


int main()
{
    // 示例1 结构体
    printf("------------- 示例1 --------------\n");   
    // 1.使用结构体定义第一个女朋友类型的变量
    struct GirlFriend gf1;  
    strcpy(gf1.name, "小诗诗"); // 注意：对字符串的赋值要用函数strcpy，而不能直接用""进行赋值 
    gf1.age = 23;
    gf1.gender = 'F';  // 注意字符用单引号，且里面不能写中文，只有字符串可以。
    gf1.height = 1.63;

    // 2.使用结构体定义第二个女朋友类型的变量
    struct GirlFriend gf2;  
    strcpy(gf2.name, "小丹丹"); 
    gf2.age = 24;
    gf2.gender = 'F';  
    gf2.height = 1.62;

    // 3.输出打印
    printf("我女朋友的名字为：%s\n", gf1.name);
    printf("我女朋友的名字为：%d\n", gf1.age);
    printf("我女朋友的名字为：%c\n", gf1.gender);
    printf("我女朋友的名字为：%lf\n", gf1.height);
    printf("\n");

    printf("我女朋友的名字为：%s\n", gf2.name);
    printf("我女朋友的名字为：%d\n", gf2.age);
    printf("我女朋友的名字为：%c\n", gf2.gender);
    printf("我女朋友的名字为：%lf\n", gf2.height);



    // 示例2 结构体数组
    printf("------------- 示例2 --------------\n");  
    // 1.定义三个学生，同时并进行赋值
    struct Student stu1 = {"zhangsan", 23};
    struct Student stu2 = {"lisi", 24};
    struct Student stu3 = {"wangwu", 25};

    // 2.把三个学生放入到数组中
    struct Student stuArr[3] = {stu1, stu2, stu3};

    // 3.遍历数组得到每一个元素
    for (int i = 0; i < 3; i++)
    {
        struct Student temp = stuArr[i];
        printf("学生的信息为：姓名%s，年龄%d\n", temp.name, temp.age);
    }


    return 0;
}