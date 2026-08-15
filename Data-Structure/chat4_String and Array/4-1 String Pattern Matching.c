/*
字符串的模式匹配(String Pattern Matching)：
一、基本概念：
    (1)主字符串（Text）：被搜索的较长字符串，长度记为 n。
    (2)模式串（Pattern）：要查找的较短字符串，长度记为 m。
    (3)模式匹配：在文本中第一次找到与模式串完全相同的一段连续子串，并返回其起始位置。

二、c语言自带的字符串模式匹配函数：strstr(具体见示例1)
    语法：strstr(s1, s2)  
        # 参数：s1是主字符串，s2是模式串
        # 返回值：s2第一次出现在s1的位置索引对应的内存地址

三、字符串模式匹配的实现思想：
    1.朴素匹配：
        (1)思想：通过双层循环，第一层遍历主字符串，第二层遍历模式串，将模式串与字符文本进行
                一个字符一个字符的核对，找寻第一个完全匹配的位置。
        (2)代码：见下面示例2代码。
        (3)时间复杂度：O(n*m)，n是主字符串长度，m是模式串长度。

    2.KMP算法：
        (1)思想与代码见3-2节内容。
        (2)时间复杂度：O(n + m)，n是主字符串长度，m是模式串长度。
*/
#include<stdio.h>
#include<string.h>

// 示例2对应的朴素匹配的函数
// 函数返回主字符串str中查找模式串pattern第一次出现的位置索引，没有就返回-1
int strMatch(char* str, char* pattern) 
{
    // 获取字符串长度(结束符'\0'不会计入)
    int n = strlen(str);
    int m = strlen(pattern);

    // 遍历主字符串str
    for (int i = 0; i <= (n - m); i++)
    {
        // 遍历模式串pattern判断是否完全匹配
        int j = 0;   // 用于记录模式串的索引值(从0开始)
        while (j < m)
        {
            // 对应字符匹配则i与j自增，以判断下一个字符是否匹配
            if (str[i] == pattern[j])
            {
                i++;
                j++;
            }
            // 对应字符不匹配就将主字符串str的索引i返回到之前未遍历模式串时的值，并退出while循环
            else
            {
                i = i - j; 
                break;
            }
        }
        // 第一次完全匹配时，函数返回该匹配所对应str的位置索引
        if (j == m)
        {
            return i - j;
        }
    }
    // 没有完全匹配的位置，则返回-1
    return -1;
}


int main()
{
    // 示例1 自带的字符串模式匹配strstr函数
    printf("------------- 示例1 --------------\n"); 
    char s1[] = "abcbbabc";
    char s2[] = "ba";
    // 打印s1所有字符的内存地址
    for (int i = 0; i < 8; i++)
    {
        printf("%p\t", &s1[i]); 
    }
    printf("\n");

    // 通过strstr函数进行模式串s2的模式匹配
    printf("%p\n", strstr(s1, s2)); // 打印结果正好是s1第4个索引(从0开始)对应的内存地址


    // 示例2 朴素匹配
    printf("------------- 示例2 --------------\n"); 
    char* str = "abcabaabcabc";
    char* pattern = "abaa";
    int pos = strMatch(str, pattern);
    printf("%d\n", pos);



    return 0;
}