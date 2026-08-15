"""
读取文件数据中的文件orders.txt，并进行计算，需求如下：
    1.各城市销售额排名，从大到小
    2.全部城市，有哪些商品类别在售卖
    3.北京市有哪些商品类型在售卖
"""
from pyspark import SparkConf, SparkContext
import os
import json

### 设置python环境路径并构建执行环境入口对象
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"
conf = SparkConf().setMaster("local[*]").setAppName("test_spark")
sc = SparkContext(conf=conf)

### 读取数据得到RDD
file_rdd = sc.textFile("./文件数据/orders.txt")  # 以chat14为相对路径

### 取出一个个JSON字符串
json_str_rdd = file_rdd.flatMap(lambda x: x.split("|"))

### 将JSON字符串转换成字典对象
dict_rdd = json_str_rdd.map(lambda x: json.loads(x))



### 需求1：各城市销售额排名，从大到小
## 1.1 取出城市和销售额，构建成KV对
city_with_money_rdd = dict_rdd.map(lambda x: (x['areaName'], int(x['money'])))

## 1.2 按照城市进行分组，计算每个城市的总销售额
city_result_rdd = city_with_money_rdd.reduceByKey(lambda x, y: x + y)

## 1.3 按照销售额进行排序(降序)
result1_rdd = city_result_rdd.sortBy(lambda x: x[1], ascending=False,numPartitions=1)

print("需求1的结果(各城市销售额从大到小排名)：", result1_rdd.collect())



### 需求2：全部城市，有哪些商品类别在售卖
## 2.1 取出全部商品类别，并去重
result2_rdd = dict_rdd.map(lambda x: x['category']).distinct()

print("需求2的结果(全部城市的商品类别)：", result2_rdd.collect())



### 需求3：北京市有哪些商品类型在售卖
## 3.1 过滤出北京市的数据
beijing_data_rdd = dict_rdd.filter(lambda x: x['areaName'] == '北京')

## 3.2 取出北京市的商品类别，并去重
result3_rdd = beijing_data_rdd.map(lambda x: x['category']).distinct()

print("需求3的结果(北京市的商品类别)：", result3_rdd.collect())




### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()

