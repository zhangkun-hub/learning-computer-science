"""
一、PySpark支持多种数据格式的输入，在输入完成后，都会得到一个：RDD类的对象


二、RDD对象：
    1.介绍：RDD全称为：弹性分布式数据集（Resilient Distributed Datasets）

    2.特点：PySpark针对数据的处理，都是以RDD对象作为载体，即：
        (1)数据存储在RDD内。

        (2)各类数据的计算方法，也都是RDD的成员方法。

        (3)RDD的数据计算方法，返回值依旧是RDD对象。

        
三、Python数据容器转RDD对象：  
    1.方式：PySpark提供了SparkContext类对象的成员方法parallelize()，可以将Python中的数据容器
        （如list、set、dict等）转换为RDD对象。

    2.注意：
        (1)parallelize()方法的参数必须是一个可迭代对象(即各种序列)，因此不能直接传入一个整数等
                非可迭代对象，否则会报错。

        (2)字符串会被拆分出来，变成一个个字符元素，存入RDD对象。
                比如"ho wd"会被拆分成['h', 'o', ' ', 'w', 'd']，存入RDD对象。

        (3)字典仅有key会被存入RDD对象，value不会被存入RDD对象。
                比如{"a": 1, "b": 2, "c": 3}会被拆分成['a', 'b', 'c']，存入RDD对象。

                
四、文件数据转RDD对象：
    (1)转换方式：PySpark提供了SparkContext类对象的成员方法textFile()，可以将文件数据转换为RDD对象。
                即：RDD对象 = SparkContext对象.textFile("文件路径")
        
    (2)数据存入方式为：以文本文件的每一行作为一个元素，存入RDD对象中。

                
五、RDD对象的内容查看：可以通过“RDD对象.collect()”获取RDD对象内容，进行查看。
"""
### 示例1 Python数据容器转RDD对象
print("--------------------- 示例1 -------------------------")
### 导包
from pyspark import SparkConf, SparkContext

### 创建SparkConf类对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")

### 基于SparkConf类对象创建SparkContext类对象，即执行环境入口对象
sc = SparkContext(conf=conf)

### 通过parallelize()方法将Python数据容器转换为RDD对象
rdd1 = sc.parallelize([1, 2, 3, 4, 5])           # 列表
rdd2 = sc.parallelize((1, 2, 3, 4, 5))           # 元组
rdd3 = sc.parallelize("hello world")             # 字符串
rdd4 = sc.parallelize({"a": 1, "b": 2, "c": 3})  # 字典
rdd5 = sc.parallelize({1, 2, 3, 4, 5})           # 集合

### 打印RDD对象的内容
print(rdd1.collect())     # [1, 2, 3, 4, 5]
print(rdd2.collect())     # [1, 2, 3, 4, 5]
print(rdd3.collect())     # ['h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd']
print(rdd4.collect())     # ['a', 'b', 'c']
print(rdd5.collect())     # [1, 2, 3, 4, 5]

### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()


### 示例2 文件数据转RDD对象
print("--------------------- 示例2 -------------------------")
### 导包
from pyspark import SparkConf, SparkContext

### 创建SparkConf类对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")

### 基于SparkConf类对象创建SparkContext类对象，即执行环境入口对象
sc = SparkContext(conf=conf)

### 通过textFile()方法将文件数据转换为RDD对象
rdd1 = sc.textFile("./文件数据/hello.txt")    # 相对文件夹chat14的相对路径

### 打印RDD对象的内容
print(rdd1.collect())    # 以文本文件的每行为一个元素，存入RDD对象中

### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()