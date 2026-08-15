"""
读取文件数据中的文件hello.txt，统计文件中每个单词出现的次数。
"""
from pyspark import SparkConf, SparkContext
import os

### 1.设置python环境路径并构建执行环境入口对象
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"
conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
sc = SparkContext(conf=conf)


### 2.读取数据文件，取出全部单词
## 2.1 读取数据文件，构建RDD对象
rdd = sc.textFile("./文件数据/hello.txt")  # 相对chat14的路径

## 2.2 取出全部单词
word_rdd = rdd.flatMap(lambda line: line.split(" "))


### 3.统计每个单词出现的次数
## 3.1 将每个单词转换为（单词，1）的形式
word_one_rdd = word_rdd.map(lambda word: (word, 1))  

## 3.2 对每个单词进行分组并统计次数
word_count_rdd = word_one_rdd.reduceByKey(lambda a, b: a + b)

### 3.3 打印结果
print(word_count_rdd.collect())    



### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()
