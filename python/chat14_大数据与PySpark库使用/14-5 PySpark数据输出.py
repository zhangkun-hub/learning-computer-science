"""
一、hadoop_home环境变量设置(在第三部分将RDD对象中的数据保存到文件中需要用到)：
    在“计算机学习”文件夹中找到“hdaoop环境配置文件”文件夹，然后根据视频课程P151的2:00开始学习。

    
二、将RDD对象中的数据转换成Python对象：(不止以下4种算子)
    1.collect算子
        (1)功能：将RDD各个分区内的所有数据，统一收集到Driver端，转换为Python中的list对象。

        (2)语法：rdd对象.collect()     # 返回值是python中list列表对象。

    2.reduce算子
        (1)功能：将RDD各个分区内的所有数据，统一收集到Driver端，然后按照指定的函数规则进行聚合
                计算，最终返回值便是函数计算后的结果(包括数据类型)。

        (2)语法：rdd对象.reduce(f)     
            # f是一个函数(方法)，其映射关系为：f:(T, T) -> T

        (3)注意：函数f的聚合操作逻辑例子如下：
                比如某组的value是[1,2,3]，函数为lambada x,y: x+y，则聚合逻辑为：
            先将1和2进行聚合，得到3；再将上一个聚合结果3和3进行聚合，得到6；最终结果为6。

    3.take算子
        (1)功能：将RDD各个分区内的前n条数据，统一收集到Driver端，转换为Python中的list对象。

        (2)语法：rdd对象.take(n)     # n是要取的元素个数，返回值是python中list列表对象。

    4.count算子
        (1)功能：统计RDD对象中元素的个数。

        (2)语法：rdd对象.count()     # 返回值是元素个数，数据类型为int。

        
三、将RDD对象中的数据保存到文件中：saveAsTextFile算子
    1.功能：将RDD各个分区内的所有数据，保存到指定的文件系统路径中。

    2.语法：rdd对象.saveAsTextFile("文件系统路径")     

    3.对每个区的文件，RDD对象的每个元素数据默认占一行。

    4.注意：默认将数据输出到的文件数是按照分区数来决定的，若只输出到一个文件中，就需要进行设置：
        (1)方式1：SparkConf对象设置属性全局并行度为1，代码示例如下：
            conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
            conf.set("spark.default.parallelism", "1")    # 其中"1"就是全局并行度的值
            sc = SparkContext(conf=conf)

        (2)方式2：通过parallelize方法创建RDD对象时，将第二个参数numSlices值为1，代码示例如下：
            rdd = sc.parallelize([1, 2, 3, 4, 5], numSlices=1)   
            或者：rdd = sc.parallelize([1, 2, 3, 4, 5], 1)    

"""
from pyspark import SparkConf, SparkContext
import os   

### 设置python与hadoop环境路径
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"
os.environ["HADOOP_HOME"] = "D:\hadoop-3.0.0"  # 设置hadoop_home环境变量

### 构建执行环境入口对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
conf.set("spark.default.parallelism", "1")    # 其中"1"就是全局并行度的值(设置分区数的方式1)
sc = SparkContext(conf=conf)


### 示例1 将RDD对象中的数据转换成Python对象
print("--------------------- 示例1 -------------------------")
## 准备一个RDD对象
rdd1 = sc.parallelize([1, 2, 3, 4, 5])

## 1.collect算子
list1 = rdd1.collect()
print(list1)        # 输出：[1, 2, 3, 4, 5]
print(type(list1))  # 输出：<class 'list'>
print()

## 2.reduce算子
num = rdd1.reduce(lambda x, y: x + y)  
print(num)        # 输出：15
print(type(num))  # 输出：<class 'int'>
print()

## 3.take算子
take_list = rdd1.take(3)
print(take_list)        # 输出：[1, 2, 3]
print(type(take_list))  # 输出：<class 'list'>
print()

## 4.count算子
count_num = rdd1.count()
print(count_num)        # 输出：5
print(type(count_num))  # 输出：<class 'int'>



### 示例2 将RDD对象中的数据保存到文件中
print("--------------------- 示例2 -------------------------")
## 准备三个RDD对象
rdd2 = sc.parallelize([1, 2, 3, 4, 5],)     # 注：该方法的第二个参数是numSlices，值表示分区数
rdd3 = sc.parallelize([("hello", 3), ("Spark", 5), ("Hi", 7)])
rdd4 = sc.parallelize([[1, 3, 5], [2, 4, 6], [7, 8, 9]])

## 输出到文件中
rdd2.saveAsTextFile("./输出文件/output1")
rdd3.saveAsTextFile("./输出文件/output2")
rdd4.saveAsTextFile("./输出文件/output3")



### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()