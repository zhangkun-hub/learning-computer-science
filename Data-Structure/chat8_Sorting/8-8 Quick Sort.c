/*
快速排序：
一、核心思想：
    1.分治思想：选取一个基准元素，将数组分成两部分，使得左边部分的所有元素都小于基准，右边部分的所有
        元素都大于基准，然后递归地对左右两部分进行同样的操作。

    2.分区操作（Partition）：分区是快速排序的核心，有多种实现方式：
        Lomuto分区方案：简单易懂
        Hoare分区方案：原始方案，更高效
        三向切分：处理大量重复元素


二、算法步骤(Lomuto分区方案)：
    步骤1：选择基准元素（pivot）
        - 通常选择最后一个元素、第一个元素、中间元素或随机元素
    
    步骤2：分区操作
        - 初始化两个指针：i（已处理部分的末尾）和j（当前处理元素）
        - 遍历数组，将小于基准的元素交换到左侧
        
    步骤3：递归排序
        - 对基准左侧的子数组递归排序
        - 对基准右侧的子数组递归排序


三、快速排序的特点
    1.优点
        平均性能优秀：平均时间复杂度O(n log n)
        原地排序：空间复杂度O(log n)，只需要递归栈空间
        实际应用中最快：常数因子小，实际运行通常比其他O(n log n)算法快
        缓存友好：顺序访问模式，缓存命中率高
        可分治并行：容易并行化实现

    2.缺点
        最坏情况O(n²)：当数组已有序或逆序时
        不稳定排序：相等元素的相对顺序可能改变
        递归深度：最坏情况递归深度为O(n)，可能导致栈溢出
        基准选择敏感：性能依赖于基准的选择


四、时间复杂度分析
    情况	     时间复杂度	    说明
    最优情况	 O(n log n)	    每次分区都能将数组均匀分成两半
    平均情况	 O(n log n)	    随机数据的期望性能
    最坏情况	 O(n²)	        每次分区都极不均匀（如已排序数组）
    空间复杂度	 O(log n)	    递归栈的深度

    详细分析：
        每次分区操作需要O(n)时间
        如果每次分区都能将数组均匀分成两半，递归深度为log₂n
        总时间：O(n) × O(log n) = O(n log n)
        最坏情况：递归树退化为链表，深度为n，总时间O(n²)


五、总结
        快速排序是实际应用中最快的通用排序算法，其分治思想和原地排序特性使其在内存排序中表现优异。
    虽然最坏情况O(n²)，但通过随机化和优化策略可以避免。

    1.核心价值：
        实际性能最优：平均情况O(n log n)且常数因子
        原地排序：空间复杂度O(log n)
        缓存友好：顺序访问模式
        可分治并行：易于并行实现

    2.实际应用：
        编程语言标准库（C++的qsort，Java的Arrays.sort()）
        数据库查询优化
        实时系统
        大数据处理

    3.现代发展：
        内省排序：快速排序+堆排序混合
        双轴快速排序：Java 7+的默认排序算法
        并行快速排序：多核CPU上的高效实现
        GPU快速排序：利用GPU并行计算
*/
#include <stdio.h>

// 辅助函数partition：
// 作用：将数组data的子数组(下标从low开始，high结束)划分为左右两个部分，并返回基准值的最终位置
int partition(int* data, int low, int high)
{
    // 选择最左侧元素作为基准值
    int pivot = data[low];
    
    // 当 low 与 high 没有相遇时，继续循环
    while(low < high)
    {
        // 从右向左寻找第一个比 pivot 小的数
        while(low < high && data[high] >= pivot)
        {
            high--;
        }
        // 将较小值填入左侧low位置
        data[low] = data[high];
        
        // 从左向右寻找第一个比 pivot 大的数
        while(low < high && data[low] <= pivot)
        {
            low++;
        }
        // 将较大值填入右侧high位置
        data[high] = data[low];
    }
    // 当 low == high 时，即找到 pivot 应该放置的位置
    data[low] = pivot;

    return low; // 返回 pivot 的最终位置
}


// 快速排序主函数(采用递归方式)
void quickSort(int* data, int low, int high) // low与high分别记录子数组两端元素下标值
{
    int pivot;  // 记录基准元素的下标(此处取子数组的第一个元素为基准元素)

    // 当low >= high时说明子数组长度 <= 0，无需进行分区和排序操作
    if (low < high)
    {
        // 对当前区间进行划分，并获取 pivot 的位置
        pivot = partition(data, low, high);
        
        // 对 pivot 左侧子数组递归进行快速排序
        quickSort(data, low, pivot - 1);
        
        // 对 pivot 右侧子数组递归进行快速排序
        quickSort(data, pivot + 1, high);
    }
}


int main(int argc, char const *argv[])
{
    // 待排序数组
    int data[] = {47, 35, 60, 95, 77, 15, 28};
    int len = sizeof(data) / sizeof(data[0]);
    
    // 执行快速排序
    quickSort(data, 0, len-1);
    
    // 输出排序后的结果
    for(int i = 0; i < len; i++)
    {
        printf("%d ", data[i]); // 15 28 35 47 60 77 95
    }
    return 0;
}