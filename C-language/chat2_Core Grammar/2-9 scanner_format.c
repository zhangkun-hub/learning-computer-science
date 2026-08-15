//键盘录入scanf：是scanner format的缩写，是c语言提供的一个函数(即很多代码打包成的整体)
//作用：获取用户在键盘上输入的数据，并赋值给变量

//直接用scanf会导致缓存区溢出而警告，因此建议用scanf_s或者加#define _CRT_SECURE_NO_WARNINGS忽略警告
#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>

int main()
{
    //1.定义一个变量用来接收数据
    int a;

    //2.键盘录入
    printf("请输入一个整数：");
    scanf("%d", &a);//scanf两个参数含义跟printf基本一致，但&符号为固定格式(其含义见指针内容)

    /*
    注意:scanf("%d\n", &a)的键盘录入必须写：变量a数字+\n，负责会一直循环键盘录入的_，直到录入\n才结束
        scanf("你的年龄%d", &a)的键盘录入必须写：你的年龄+变量a数字，否则打印的a值有问题
    */

    //3.打印
    printf("变量a里面的值为：%d\n", a);
    printf("------------------------\n");

    //练习1.键盘录入女朋友名字，要求格式：我亲亲女朋友的名字为：xxx
    char str[100];//定义字符串变量，其中设置其占用内存为100
    printf("请输入您女朋友的名字：\n");
    scanf("%s", &str);
    printf("我亲亲女朋友的名字为：%s\n", str);

    //练习2.键盘录入自己的年龄，格式为：我的年龄为：xx岁
    int age;
    printf("请输入您的年龄：\n");
    scanf("%d",&age);
    printf("我的年龄为：%d岁\n",age);
    
    return 0;
}