"""
一、通过PySpark进行数据计算(展示后3种方法)：(注：数据计算的方法远不止这6种)
    1.filter()算子：对数据进行过滤，保留满足条件的数据。
        (1)语法：rdd对象.filter(f)
             # f是一个函数(方法)，其映射关系为：f:(T) -> bool
             # 表示传入任意类型的参数，但返回值必须是bool类型，即True/False。

        (2)功能：对于RDD对象中的每个元素，都会将其作为参数传入函数f中进行判断，如果函数f返回
                True，则保留该元素；如果函数f返回False，则过滤掉该元素。

    2.distinct()算子：对RDD对象中的元素进行去重操作。
        语法：rdd对象.distinct()
             # distinct()算子不需要传入任何参数。
    
    3.sortBy()算子：对RDD对象中的元素进行排序操作。
        (1)语法：rdd对象.sortBy(f, ascending=False, numPartitions=1)
             # f是一个函数(方法)，其映射关系为：f:(T) -> U。f用来告知按照rdd中哪个数据进行排序。
             # 比如：lambda x: x[1]表示按照rdd中元素的第二列元素进行排序。
             # ascending参数表示排序方式，默认为True，表示升序；False，则表示降序。
             # numPartitions表示排序后RDD对象的分区数，默认为1，表示排序后RDD对象只有一个分区。
             # 返回值为元素排序后的RDD对象。
        
        (2)注意：如果排序后RDD对象的分区数大于1，则每个分区内的元素是有序的，但整个RDD对象中的元素
                不是全局有序的；如果排序后RDD对象的分区数为1，则整个RDD对象中的元素是全局有序的。
"""
from pyspark import SparkConf, SparkContext
import os

## 设置python环境路径并构建执行环境入口对象
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"
conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
sc = SparkContext(conf=conf)


### 示例1 filter()算子
print("--------------------- 示例1 -------------------------")
## 准备一个RDD对象
rdd1 = sc.parallelize([1, 2, 3, 4, 5])

## 对RDD对象中的元素进行过滤（保留所有偶数）
rdd2 = rdd1.filter(lambda num: num % 2 == 0)
print(rdd2.collect())  # 输出：[2, 4]


### 示例2 distinct()算子
print("--------------------- 示例2 -------------------------")
## 准备一个RDD对象
rdd3 = sc.parallelize([1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7 , 8, 8, 9, 9, 10])

## 对RDD对象中的元素进行去重操作
rdd4 = rdd3.distinct()
print(rdd4.collect())  # 输出：[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]


### 示例3 sortBy()算子
print("--------------------- 示例3 -------------------------")
## 准备一个RDD对象
rdd5 = sc.parallelize([('python', 6), ('itheima', 7), ('itcast', 4), ('spark', 4), ('pyspark', 3)])

## 对RDD对象中的元素进行排序操作（按照第二个元素进行降序排序）
rdd6 = rdd5.sortBy(lambda x: x[1], ascending=False, numPartitions=1)
print(rdd6.collect())  # 输出：[('itheima', 7), ('python', 6), ('itcast', 4), ('spark', 4), ('pyspark', 3)]





### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()