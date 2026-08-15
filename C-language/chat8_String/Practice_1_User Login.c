/*
模拟用户登录
*/
#include<stdio.h>
#include<string.h>

int main()
{
    // 1，定义两个变量表示正确的用户名和密码
    char* rightUsername = "zhangsan";
    char* rightPassword = "1234qwer";

    // 通过循环进行输入登录操作
    for (int i = 1; i <= 3; i++)
    {
        // 2.键盘录入两个字符串，表示用户的用户名和密码
        printf("请输入用户名\n");
        char username[100];
        scanf("%s", username);

        printf("请输入密码\n");
        char password[100];
        scanf("%s", password);

        printf("%s\n", username);
        printf("%s\n", password);

        // 3.判断是否正确
        if (!strcmp(username, rightUsername) && !strcmp(password, rightPassword))
        {
            printf("登录成功\n");
            break;
        }
        else
        {
            if (i == 3)
            {
                printf("用户%s被锁定，请联系黑马程序员官方账号", username);
            }
            else
            {
                printf("登录失败，还剩下%d次机会", 3 - i);
            }
        }
    }

    return 0;
}