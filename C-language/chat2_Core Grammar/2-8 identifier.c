/*
标识符：代码中所有我们自己起的名字，比如变量名、函数名

命名的硬性要求:(注意：代码文件名的硬性要求无2、3条，但其名字后要加.c,而c++文件则为.cpp)
    1.必须由数字、字母、下划线(_)组成; 
    2.不能以数字开头; 
    3.不能是关键字; 
    4.区分大小写
命名的软性建议:
    1.用英文单词，见名知意;
    2.变量名：全部小写;
    3.代码文件名：全部小写，单词之间用下划线隔开，开头可以用数字
*/
#include<stdio.h>

int main()
{
    int arr[] = {10,20,50,70,200,90};
    int length = sizeof(arr)/sizeof(arr[0]);
    int max = arr[0];
    for (int i=0; i<length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("%d\n", max);

    return 0;
}