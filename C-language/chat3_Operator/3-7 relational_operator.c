/*
关系运算符：用于判断两变量的关系(注意：计算机语言中，1为真命题；0为假命题)
1. a==b 判断a是否等于b;
2. a!=b 判断a是否不等于b;
3. a>b 
4. a>=b
5. a<b
6. a<=b
*/
#include<stdio.h>

int main()
{
    //注意：计算机语言中，判断的真假命题输出为(均为整数)：1为真命题；0为假命题
    int a = 10;
    int b = 20;
    printf("%d\n", a==b);//0
    printf("%d\n", a!=b);//1
    printf("%d\n", a>b);//0
    printf("%d\n", a>=b);//0
    printf("%d\n", a<b);//1
    printf("%d\n", a<=b);//1
    printf("------------------------\n");

    //练习1.数学计算中，判断一个数是否为偶数
    int c = 10;
    printf("%d\n", a % 2 == 0);//1偶数，0奇数

    //练习2.判断一个数是否不超过100
    int number = 200;
    printf("%d\n", number <= 100);

    //练习3.电商项目的支付功能业务，需要判断银行卡余额是否足够
    int pay = 100;//需要支付的钱
    int money = 200;//余额
    printf("%d\n", pay <= money);

    //练习4.电商项目的购买商品业务，需要判断货物库存是否足够
    int buy = 10;
    int ware = 100;
    printf("%d\n", ware >= buy);

    //练习5.点餐项目的筛选商品业务，需要点不低于100元的餐品
    int goods = 500;
    printf("%d\n", goods >= 100);

    return 0;
}