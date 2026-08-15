/*
生成1-100之间的随机数，然后用键盘录入去猜，猜中为止，最多10次
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    // 1.生成1-100随机数
    srand(time(NULL));
    int number = rand() % 100 + 1;

    // 2.利用循环 + 键盘录入去猜
    int guess; // 猜的数字变量
    
    for (int i = 1; i <= 10; i++)
    {
        printf("请输入您要猜的数字：\n");
        scanf("%d", &guess);

        // 与随机数比较
        if (guess < number)
        {
            printf("小了，您还有 %d 次机会", 10 - i);
        }
        else if (guess > number)
        {
            printf("大了，您还有 %d 次机会", 10 - i);
        }
        else 
        {
            printf("猜中了，您总共猜了 %d 次", i);
            break;
        }
    }

    return 0;
}

