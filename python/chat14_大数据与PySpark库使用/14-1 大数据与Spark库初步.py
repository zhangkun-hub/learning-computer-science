"""
一、Spark：Apache Spark是用于大规模数据(large-scala data)处理的统一(unified)分析引擎。
    1.解释：Spark是一款分布式的计算框架，用于调度成百上千的服务器集群，计算TB、PB等级别的数据。

    2.开发：Spark支持众多语言进行开发，其中Python就是重点支持方向，体现在第三方库(包)PySpark上。

二、PySpark库(包)：
    作用：
        (1)作为Python库进行数据处理。
        (2)提交至Spark集群进行分布式集群计算。

三、PySpark编程模型：
    1.构建执行环境入口对象，即类SparkContext的类对象，这是PySpark编程中一切功能的入口(见下面示例)

    2.使用PySpark的三大基础步骤：
        (1)数据输入：通过SparkContext类对象的成员方法，完成数据的读取操作，读取后得到RDD类对象。

        (2)数据处理计算：通过RDD类对象的成员方法，完成各种数据计算的需求。

        (3)数据输出：将处理完成后的RDD对象，调用各种成员方法完成，写出文件、转换为list等操作。

四、常用简化代码技巧：链式调用
    在Python中，如果一个对象的成员方法返回的还是这个对象本身，那么就可以继续调用这个对象的成员方法，
        这种连续调用的方式就叫链式调用。

    例如：SparkConf类对象的setMaster()方法和setAppName()方法都返回SparkConf类对象本身，所以可以
        进行链式调用，即：
            conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")

            等价于以下三行代码(因为繁琐所以用链式调用写成一行代码)：
            conf = SparkConf()  
            conf = conf.setMaster("local[*]")  
            conf = conf.setAppName("test_spark_app")

    注：链式调用在14-3和14-4节内容的数据计算部分会经常使用到，因为计算的输入和返回值都是RDD对象。
"""
### 示例 构建执行环境入口对象
print("--------------------- 示例 -------------------------")
### 导包
from pyspark import SparkConf, SparkContext


### 创建SparkConf类对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
# 注1：setMaster()为设置spark的运行模式，其中"local[*]"表示本机，即设置spark运行在自己电脑上
# 注2：setAppName()表示给spark程序起一个名称
# 注3：上述代码是链式调用写法，等价于以下三行代码(因为繁琐所以用链式调用写成一行代码)：
# conf = SparkConf()  
# conf = conf.setMaster("local[*]")  
# conf = conf.setAppName("test_spark_app")


### 基于SparkConf类对象创建SparkContext类对象，即执行环境入口对象
sc = SparkContext(conf=conf)


### 打印PySpark的运行版本
print(sc.version)


### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()