/*
一、函数：函数就是程序中独立的功能

二、函数的基本格式：
void 函数名()    // 注意：void关键字表示没有返回值
{
    函数体;
}

三、函数的调用：在需要调用函数的代码位置上写上：函数名()   // 小括号不能丢
*/
#include <stdio.h>

void playGame()
{
    printf("选择人物\n");
    printf("准备开局\n");
    printf("开始对线\n");
    printf("碾压崩盘\n");
    printf("问候队友\n");
    printf("疯送人头\n");
    printf("下把继续\n");
}

void sum()
{
    int num1 = 10;
    int num2 = 20;
    int sum = num1 + num2;
    printf("%d\n", sum);
}

int main()
{
    // 调用函数
    playGame();

    printf("---------------\n");
    playGame(); // 再次调用

    printf("---------------\n");
    sum();

    return 0;
}