//if语句：表示判断，即如果满足条件，才可以执行指定的代码
/*if语句格式1：
if (关系表达式)
{
    语句体;
}

if语句格式2：
*/
#include<stdio.h>

int main()
{
    /*if语句格式1：
    if (关系表达式)
    {
        语句体;
    }
    */
    //需求：判断变量a里面记录的值是否大于10，如果成立，就打印语句：真的大于10
    int a = 12;
    if (a > 10)
    {
        printf("真的大于10\n");
    }

    //细节1：在c语言中，如果判断的结果是一个数字，非0表示条件成立(即真命题)，0表示条件不成立(即假命题)
    //细节2：如果大括号里的语句体只有一行，那么大括号可以省略不写(可读性不强，所以一般都要写)
    int b = 20;
    if (b > 10)
        printf("真的大于10\n");
    printf("----------------------\n");

    /*if语句格式2：
    if (关系表达式)          if (关系表达式)
    {                       {
        语句体A;                语句体A;
    }               等价     }else{
    else                        语句体B;
    {                       }
        语句体B;
    }
    */
    int satisfy = 1;
    if (satisfy)
    {
        printf("终身大事全凭父母做主\n");
    }
    else
    {
        printf("女儿还想孝敬父母两年\n");
    }
    printf("----------------------\n");

    /*if语句格式3：
    if (关系表达式A)          
    {                       
        语句体A;                
    }                    
    else if(关系表达式B)                        
    {                       
        语句体B;
    }
    else if(关系表达式C)                        
    {                       
        语句体C;
    }
    ……
    else
    {
        语句体N;
    }
    */
    //练习：通过游戏氪金数目来判断自己在游戏中的VIP等级
    int money;
    printf("请输入您在游戏中的氪金总额度\n");
    scanf("%d", &money);

    if (money == 0)
    {
        printf("0冲玩家");
    }  
    else if (money >= 1 && money <= 99)
    {
        printf("尊贵的VIP1\n");
    }
    else if (money >= 100 && money <= 499)
    {
        printf("尊贵的VIP2\n");
    }
    else if (money >= 500 && money <= 999)
    {
        printf("尊贵的VIP3\n");
    }
    else if (money >= 1000 && money <= 1999)
    {
        printf("尊贵的VIP4\n");
    }
    else 
    {
        printf("顶级的VIP5\n");
    }

    return 0;
}