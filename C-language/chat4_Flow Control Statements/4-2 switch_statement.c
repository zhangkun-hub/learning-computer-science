/* 
switch语句：进行表示式值的匹配，即如果其值与对应case的值匹配，则执行对应case的代码，
    都不匹配则执行default代码。

switch语句基本格式：
switch(表达式){
    case 值1:
        语句体1;
        break;
    case 值2:
        语句体2;
        break;  
    ……
    default:
        语句体n;
        break;  
}

注意细节：
    1.表达式：计算结果只能是(字符/整数)；
    2.case：值只能是(字符/整数)的常量，不能是变量。并且各个case值不允许重复；
    3.break：表示中断、结束的意思，此处为结束swtich语句(注:可以用在各个场合不止局限于switch语句)；
    4.default：所有情况都不匹配，执行该处的内容
        注：default可以写在任意位置(但一般写在最后以保证可阅读性)，甚至可以省略不写。

switch与if的区别：
    1.适用范围：if包含所有switch的适用场景，而反之不能，也就是if适用范围大于switch； 
    2.模式匹配：switch是对有限个case进行匹配，10个左右；而if一般对一个范围进行判断匹配；
    3.执行效率：switch的执行效率要高于if！！！所以对于几个case情形，建议用switch。
*/
#include <stdio.h>

int main() {
    // 1.定义变量
    int number = 3;

    // 2.利用switch语句进行匹配
    switch (number)
    {
        case 1:
            printf("当前的数字是1\n");
            break;
        case 2:
            printf("当前的数字是2\n");
            break;   
        case 3:
            printf("当前的数字是3\n");
            break; 
        default:
            printf("当前的数字是其他\n");
            break;
    }
    
/*
补充：case穿透规则：
    先根据小括号中表达式的结果去匹配对应的case，然后执行该case里的代码，最后遇到break则
直接结束整个switch。但是，如果没有遇到break，就会继续执行下面case中的代码，直到遇到break，
或者把整个switch中所有代码全部执行完，才会结束。
    注意：case穿透只会往下穿，不会往上执行。
*/
    // case穿透具体实践：
    printf("----------------------\n");
    int number_2 = 3;
    switch (number_2)
    {
        default:
            printf("当前的数字是其他\n");
            break;
        case 3:
            printf("当前的数字是3\n");
            //break;     
        case 1:
            printf("当前的数字是1\n");
            //break;
        case 2:
            printf("当前的数字是2\n");
            //break;      
    }

    return 0;
}

