/*
隐式转换:把一个取值范围小(即字节占用小的)的转成取值范围大的，并且是程序自动进行隐式转换操作
    (其中取值范围从大到小排列：double > float > long long > long > int > short > char)
    作用:实现不同数据类型的计算
    
*/
#include<stdio.h>

int main()
{
    // 规则注意1.取值范围小的和范围大的计算，小的会自动提升为大的，再进行计算
    int a = 10;
    double b = 12.3;
    double c = a + b; // a+b进行计算时先提升a为double类型，再计算，结果便为double类型
    printf("%lf\n", c);
    printf("%zu\n", sizeof(c));
    printf("------------------------\n");
    
    // 规则注意2.short、char类型的数据在运算时，先提升为int，再进行计算
    short d = 10;
    short e = 20;
    int f = d + e; // short类型的d+e计算时先提升为int再计算，所以结果为int类型
    printf("%d\n", f);
    printf("%zu\n", sizeof(f));

    return 0;
}