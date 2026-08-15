/*
计算幂级数列：1^1 + 2^2 + 3^3 + 4^4 + 5^5 +...+ 10^10。
    注意：结果过大需要用long long类型

注意：c语言中没有幂运算，只能通过幂运算定义来自己手写代码或者通过第三方库<math.h>来实现。

其中第三方库<math.h>的使用如下：
#include <math.h>
double result = pow(2, 3);    // pow(底数, 指数) 返回 double 类型，此处为计算 2³ = 8
*/

#include <stdio.h>

int main()
{
    long long res = 0; // 定义一个变量，用于累加最终的结果

    // 外循环：依次表示1 - 10
    for (int i = 1; i <= 10; i++)
    {
        long long pow = 1; // 表示用于储存n^n的结果变量
        
        // 内循环：表示外循环内的数字的幂运算
        for (int j = 1; j <= 1; j++)
        {
            pow = pow * i;
        }
        
        res = res + pow; // 级数求和
    }

    // 打印
    printf("%lld\n", res);

    return 0;
}
