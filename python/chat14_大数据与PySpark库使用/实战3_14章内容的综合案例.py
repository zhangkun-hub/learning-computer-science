"""
读取文件search_log.txt，转换成RDD，并完成：
    1.打印输出：热门搜索时间段（小时精度）Top3。
    2.打印输出：热门搜索关键词Top3。
    3.打印输出：统计黑马程序员关键字在哪个时段被搜索最多。
    4.将数据转换成JSON格式，保存到文件中。
"""
from pyspark import SparkConf, SparkContext
import os

### 一、设置python与hadoop环境路径
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"
os.environ["HADOOP_HOME"] = "D:\hadoop-3.0.0" 

### 二、构建执行环境入口对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
conf.set("spark.default.parallelism", "1")    
sc = SparkContext(conf=conf)

### 三、读取文件，转换成RDD对象
file_rdd = sc.textFile("./文件数据/search_log.txt")


### 四、对RDD对象中的数据进行处理，完成需求1-3
## 需求1：热门搜索时间段Top3（小时精度）
# 1.1 取出全部的时间并转换为小时
# 1.2 转换为（小时，1）的二元元组
# 1.3 Key分组聚合Value
# 1.4 排序（降序）
# 1.5 取前3
result1 = file_rdd.map(lambda x: (x.split("\t")[0][:2], 1)).\
        reduceByKey(lambda a, b: a + b).\
            sortBy(lambda x: x[1], ascending=False, numPartitions=1).\
                take(3)            # \为续行符，表示当前行代码未结束，但太长了所以下一行续写
print("需求1的结果：", result1)


## 需求2：热门搜索词Top3
# 2.1 取出全部的搜索词
# 2.2（词，1）二元元组
# 2.3 分组聚合
# 2.4 排序
# 2.5 Top3
result2 = file_rdd.map(lambda x: (x.split("\t")[2], 1)).\
        reduceByKey(lambda a, b: a + b).\
            sortBy(lambda x: x[1], ascending=False, numPartitions=1).\
                take(3)
print("需求2的结果：", result2)


## 需求3：统计黑马程序员关键字在什么时段被搜索的最多
# 3.1 过滤内容，只保留黑马程序员关键词
# 3.2 转换为（小时，1）的二元元组
# 3.3 Key分组聚合Value
# 3.4 排序（降序）
# 3.5 取前1
result3 = file_rdd.map(lambda x: x.split("\t")).\
        filter(lambda x: x[2] == "黑马程序员").\
            map(lambda x: (x[0][:2], 1)).\
                reduceByKey(lambda a, b: a + b).\
                    sortBy(lambda x: x[1], ascending=False, numPartitions=1).\
                        take(1)
print("需求3的结果：", result3)


### 五、将数据转换成JSON格式，保存到文件中
# 5.1 将数据转换成JSON格式的RDD
# 5.2 写出为文件
file_rdd.map(lambda x: x.split("\t")).\
    map(lambda x: {"time": x[0], "user_id": x[1], "key_word": x[2], "rank1": x[3], "rank2": x[4], "url": x[5]}).\
        saveAsTextFile("./输出文件/output_json")



### 六、停止SparkContext对象的运行（停止PySpark程序）
sc.stop()