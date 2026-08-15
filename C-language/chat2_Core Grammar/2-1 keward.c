//关键字的字母全部小写
#include <stdio.h>

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
//注：以上出现的关键字数目为10个，即深蓝色与粉色的单词(注意#include不是关键字)