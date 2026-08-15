/*
字符串模式匹配的KMP算法：
一、next数组：
    (1)字符串的前缀后缀：(设字符串s='abcab')
        (a)前缀：除最后一个字符外的所有从头开始的连续子串。比如字符串s前缀为：a、ab、abc、abca。
        (b)后缀：除第一个字符外的所有以尾结束的连续子串。比如字符串s后缀为：b、ab、cab、bcab。
        (c)最长公共前后缀的长度：前缀集合和后缀集合的最长公共元素长度。
            比如对于字符串s，其公共前后缀为: ab；最长公共前后缀为: ab，其长度为2

    (2)next数组：对于位置索引i，next[i]表示模式串的切片[0:i]这个子串的最长公共前后缀的长度，
                其中next[0]设为-1。


二、KMP算法(以下面具体实例来描述)：
    具体实例：
        主串:      a   b   a   a   b   a   a   b   a   c   a   c   a   a   b   a  
        模式串:    a   b   a   a   b   c 
        next数组: -1   0   0   1   1   2
        位置索引：[0]  [1] [2] [3] [4] [5]

    KMP算法匹配步骤：
        1.从头开始进行第一次匹配，
        2.如果匹配失败，去找寻第一个匹配失败的字符所处在模式串的位置索引，此处为5。
        3.去看数组next[5]的元素值，此处为2。
        4.移动模式串，使得匹配失败时主串的位置索引5与模式串的位置索引next[5]=2对齐，再次匹配
            对齐之后的模式串的字符，而对齐之前模式串的字符无需再匹配了(因为一定相同)。
        5.如果仍然匹配失败，就再重复2-4的操作。


三、时间复杂度计算：设n是主字符串长度，m是模式串长度。
    1.计算next数组的时间复杂度为O(m)（因为要遍历模式串）

    2.进行KMP算法匹配的时间复杂度为O(n)
        解释：主串指针i只前进，不后退，最长便是n次循环。在KMP算法的整个匹配中，主串字符匹配成功便
            比较一次，失败则比较两次(见下面kmp代码中的while循环内容)，那么即使在最坏情况下，主串
            字符没有一个匹配成功过，整个KMP算法最多比较2n次，所以时间复杂度为O(n)。

    3.总的时间复杂度为：O(n + m)
*/
#include<stdio.h>
#include<string.h>


/*
getNext函数：传入模式串pattern与数组next，通过该函数体计算next数组
计算思路：
    1.将模式串pattern(长度为m)分成前缀字符串和后缀字符串两个部分：
        (1)后缀字符串为切片pattern[1:m-1]，将其作为主字符串str，用i表示其索引；
        (2)前缀字符串为切片pattern[0:m-2]，将其作为新的模式串pat2，用j表示其索引。
    2.按照kmp算法思路将模式串pat2与主串str进行模式匹配，凡匹配成功的部分，即str[i]==pat2[j]，可
        得到next[i+1]=j，由此便可求出next数组。
*/ 
void getNext(char* pattern, int* next)
{
    int m = strlen(pattern); // 模式串pattern长度
    int i = 0;    // 主指针(用于遍历模式串)与后缀指针(后缀字符串str的索引)，并计算next[i+1]的值
    int j = -1;   // 前缀指针，表示前缀字符串pat2的索引
    next[0] = -1;

    // 通过循环计算next数组的next[i+1]的值
    while (i < m - 1)
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

// kmp算法：传入主字符串str和模式串pattern，通过该函数体进行字符串模式匹配，如果不匹配则返回-1
int kmp(char* str, char* pattern)
{
    int i = 0;               // i记录主字符串str索引
    int j = 0;               // j记录模式串pattern索引
    int n = strlen(str);     // n记录主字符串str长度
    int m = strlen(pattern); // m记录模式串pattern长度

    // 求解next数组
    int next[100]; 
    getNext(pattern, next);

    // 进行kmp算法循环
    while (i < n && j < m)
    {
        // 当str的第i个索引字符与pattern的第j个索引字符匹配时，i与j自增从而检验下一个字符是否匹配
        // j==-1是pattern[0]与str[i]不匹配情形，通过i与j自增，检验str[i+1]与pattern[0]是否匹配
        if (j == -1 || str[i] == pattern[j])
        {
            i++;
            j++;
        }
        // 当str的第i个索引字符与pattern的第j个索引字符不匹配时的情形
        // 操作：移动模式串，使得匹配失败时str的位置索引i与模式串的位置索引next[j]对齐，再次匹配
        else
        {
            j = next[j];
        }
    }

    // 通过kmp算法的循环求出字符串匹配的位置i-j并返回，但不匹配则返回-1
    if (j == m)
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

int main()
{
    char* str = "abaabaabacacaabaabcc"; // 主字符串
    char* pattern = "abaabc";           // 模式串
    int len = strlen(pattern);          // 模式串长度
    int next[len];                      // next数组

    // 求解next数组
    getNext(pattern, next);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", next[i]); // -1 0 0 1 1 2
    }
    printf("\n");
    
    // KMP算法
    printf("%d\n", kmp(str, pattern));  // 13


    return 0;
}