//三元运算符(三元表达式、问号冒号运算符)：含义见下面例子
//格式：关系表达式? 表达式1: 表达式2;
//含义：如果关系表达式成立，则执行表达式1，如果不成立，则执行表达式2
#include<stdio.h>

int main()
{
    //练习1.获取两变量的较大值(三元运算符表示)
    int a = 10;
    int b = 20;
    int c = a > b ? a : b;//表示如果a>b成立，则输出a，否则，输出b
    printf("%d\n", c);
    printf("%d\n", a > b ? a : b);

    //练习2.获取三个变量中的最大值
    int d = 10;
    int e = 30;
    int f = 20;
    int temp = d > e ? d : e;
    int max = c > temp ? c : temp;
    printf("%d\n", max);

    return 0;
}