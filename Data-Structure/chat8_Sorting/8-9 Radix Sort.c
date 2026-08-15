/*
基数排序：
一、介绍：基数排序（Radix Sort）是一种非比较型的整数排序算法。它通过将整数按位数切割成不同的数字，
    然后按每个位数分别进行排序。

二、核心思想与关键特性：
    1.思想：将整数按位排序，从最低位(Least Significant Digit)或最高位(Most Significant Digit)
        开始，依次对每一位进行排序。

    2.关键特性：
        非比较排序：不通过比较元素大小来排序
        稳定排序：保持相等元素的相对顺序
        线性时间复杂度：在特定条件下可达到O(n)
        适用于整数和字符串：可扩展处理其他数据类型

    3.两种实现方式
        LSD（Least Significant Digit，最低位优先）：从最低位开始排序
        MSD（Most Significant Digit，最高位优先）：从最高位开始排序


三、算法步骤(LSD基数排序为例)：
    步骤1：找出数组中最大数字，确定最大位数d。
    步骤2：初始化10个桶（0-9），从左到右排列。
    步骤3：从最低位（个位）开始，到最高位结束：
        a. 遍历数组，根据当前位的数字将元素分配到对应的桶(处于相同桶的按数组顺序从上到下排列)。
        b. 按从上到下、从左到右的顺序收集所有桶中的元素，覆盖原数组。
        c. 移动到下一位（十位、百位等）。
    步骤4：完成所有位的排序后，数组有序。


四、基数排序的特点
    ✅ 优点
        线性时间复杂度：O(nk)，其中k是最大位数
        稳定排序：保持相等元素的相对顺序
        适合整数排序：对整数排序非常高效
        可扩展性：可处理字符串、日期等数据类型
        可并行化：每轮排序可并行处理

    ⚠️ 缺点
        仅适用于特定数据类型：主要是整数和定长字符串
        需要额外空间：需要O(n+k)的额外存储空间
        不适合浮点数：需要特殊处理
        k可能较大：如果数字范围很大，效率会降低
        不适用于通用比较排序：只能用于可分解为键的数据


五、时间复杂度分析
    情况	        时间复杂度	    说明
    最优情况	    O(nk)	        与输入顺序无关，必须进行k轮
    平均情况	    O(nk)	        每轮计数排序O(n)
    最坏情况	    O(nk)	        同上
    空间复杂度	    O(n+k)	        需要计数数组和输出数组

    详细分析：
        k：最大数字的位数
        b：基数（十进制为10）
        每轮计数排序：O(n + b)
        总时间：O(k × (n + b)) = O(nk) 当b是常数时


六、LSD与MSD比较
    特性	    LSD基数排序	         MSD基数排序
    方向	    从最低位到最高位	 从最高位到最低位
    稳定性	    稳定	             稳定
    适用性	    定长数据	         变长数据
    实现复杂度	 较简单	             较复杂（需要递归）
    性能	    适合位数相同的数据	  适合字符串排序
    空间复杂度	 O(n+k)	             递归栈空间


七、总结
        基数排序是一种高效的整数排序算法，通过按位排序实现线性时间复杂度。虽然适用场景有限，但在
    处理整数、字符串等可分解数据时性能优异。

    1.核心价值：
        线性时间复杂度：O(nk)，当k较小时非常快
        稳定排序：保持相等元素的相对顺序
        适合特定数据类型：整数、字符串、日期等
        可扩展性：可处理多关键字排序

    2.实际应用：
        数据库索引构建
        字符串字典序排序
        大量整数排序
        多关键字排序场景

    3.局限性：
        仅适用于可分解为键的数据
        需要额外存储空间
        不适用于通用比较排序
        对浮点数需要特殊处理
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define RADIX 10  // 十进制：桶的数量为10（0~9）

// 获取数num在第pos位上的数字（pos = 1(个位), 2(十位), 3(百位),...）
int getDigit(int num, int pos)
{
    int radix = 1;
    for (int i = 1; i < pos; i++)
    {
        radix *= 10;
    }
    return (num / radix) % 10;
}

// 获取数组data中最大数字的最大位数digit。
int getMaxDigit(int *data, int len)
{
    // 获取最大数字max
    int max = data[0];
    for (int i = 1; i < len; i++)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }

    // 获取最大数字max的最大位数digit
    int digit = 0;
    while (max != 0)
    {
        digit++;
        max /= 10;
    }

    return digit;
}

// 基数排序
void radixSort(int *data, int len)
{
    int maxDigit = getMaxDigit(data, len); // 获取最大位数，决定排序轮数
    int bucket[RADIX][MAX];                // 定义10个桶，每个桶最多装 MAX 个元素
    int count[RADIX];                      // 每个桶中的元素数量

    for (int pos = 1; pos <= maxDigit; pos++) // 从个位开始，依次对每一位进行排序
    {
        // 清空计数器，准备新一轮
        memset(count, 0, sizeof(count)); // memset(arr,i,size)表示将数组arr所有值设置为i

        // 分配阶段：将每个元素放入对应的桶中
        for (int i = 0; i < len; i++)
        {
            int digit = getDigit(data[i], pos);        // 获取当前位置的数字
            bucket[digit][count[digit]] = data[i];     // 放入对应桶中
            count[digit]++;                            // 桶的元素数量+1
        }

        // 收集阶段：按桶的顺序重新收集数据到数组data中
        int index = 0;
        for (int i = 0; i < RADIX; i++) // 依次从0到9号桶取出数据
        {
            for (int j = 0; j < count[i]; j++)
            {
                data[index++] = bucket[i][j];
            }
        }
    }
}


// 主函数测试
int main(int argc, char const *argv[])
{
    // 待排序数组
    int data[] = {170, 201, 321, 95, 843, 996, 57, 8, 241, 30};
    int len = sizeof(data) / sizeof(data[0]);

    // 对数组进行基数排序
    radixSort(data, len);

    // 输出排序后的结果
    for (int i = 0; i < len; i++)
    {
        printf("%d ", data[i]); // 8 30 57 95 170 201 241 321 843 996
    }
    return 0;
}