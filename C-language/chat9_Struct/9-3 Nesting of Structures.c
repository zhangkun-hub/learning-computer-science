/*
结构体的嵌套：如果结构体中的成员的类型是其他结构体，就用到了结构体的嵌套
    具体使用方式见下面示例的内容
*/
#include<stdio.h>
#include<string.h>

// Student结构体中用来嵌套的结构体
struct Message
{
    char phone[12];
    char mail[100];
};

// 示例的结构体
struct Student
{
    char name[100];
    int age;
    char gender;
    double height;
    struct Message msg;  // 结构体的嵌套部分
};

int main()
{
   // 示例 结构体的嵌套
    printf("------------- 示例 --------------\n");  
    // 1.定义学生类型的变量
    struct Student stu;

    // 2.给里面的每一个成员进行赋值
    strcpy(stu.name, "zhangsan"); 
    stu.age = 23;
    stu.gender = 'M';  
    stu.height = 1.78;

    // 给嵌套的结构体进行赋值
    strcpy(stu.msg.phone, "123121123");
    strcpy(stu.msg.mail, "2081862810@qq.com"); 

    // 3.输出打印
    printf("学生1的信息为：\n");
    printf("姓名为：%s\n", stu.name);
    printf("年龄为：%d\n", stu.age);
    printf("性别为：%c\n", stu.gender);
    printf("身高为：%lf\n", stu.height);

    // 打印嵌套字符串
    printf("手机号为：%s\n", stu.msg.phone);
    printf("邮箱为：%s\n", stu.msg.mail);
    printf("\n");


    // 扩展：对嵌套字符串的批量赋值法
    struct Student stu2 = {"lisi", 24, 'F', 1.65, {"123433456", "123@qq.com"}};

    printf("学生2的信息为：\n");
    printf("姓名为：%s\n", stu2.name);
    printf("年龄为：%d\n", stu2.age);
    printf("性别为：%c\n", stu2.gender);
    printf("身高为：%lf\n", stu2.height);
    printf("手机号为：%s\n", stu2.msg.phone);
    printf("邮箱为：%s\n", stu2.msg.mail);



    return 0;
}
