"""
一、通过PySpark进行创建RDD对象后进行数据计算的还需要准备的工作：告诉PySpark自己的python环境路径
    方法如下：
        import os      # 导入os模块
        os.environ["PYSPARK_PYTHON"] = "python解释器的路径"   

        注：查询anaconda虚拟环境(包括base环境)中python解释器的路径，
            1.通过“conda activate myenv”进入虚拟环境myenv中(base环境则无此操作)。
            2.输入：python -c "import sys; print(sys.executable)" 命令，即可得到python解释器
                    的绝对路径。

二、算子f的映射关系定义：(算子就是函数或者方法，但算子是标准化名称)
    1.f:(T) -> U
        映射含义：只接受一个参数传入，参数类型不限。返回一个返回值，返回值类型不限。

    2.f:(T) -> T
        映射含义：只接受一个参数传入，参数类型不限。返回一个返回值，但返回值类型与参数类型必须相同。

    3.f:(T, T) -> T
        映射含义：接受两个参数传入，参数类型不限但要一致。返回一个返回值，类型与参数类型必须相同。

    

三、通过PySpark进行数据计算(展示前3种方法)：
    1.map()算子：接收一个函数f，将RDD对象中的元素逐个进行函数f操作(一条条处理)，返回新的RDD对象。
        语法：rdd对象.map(f)
             # f是一个函数(方法)，其映射关系为：f:(T) -> U

    2.flatMap()算子：对RDD执行跟map完全相同的操作，但最后进行解除嵌套操作。
        (1)解除嵌套含义：
            lst = [[1, 2], [3, 4], [5, 6]]  # 嵌套的列表
            lst2 = [1, 2, 3, 4, 5, 6]       # 解除嵌套后的列表

        (2)语法：rdd对象.flatMap(f)
             # f是一个函数(方法)，其映射关系为：f:(T) -> T

    3.reduceByKey()算子：
        (1)要求：RDD对象必须是KV对的形式，即每个元素都是一个二元元组。

        (2)功能：将所有KV对按照key分组，然后根据你提供的聚合逻辑，对组内KV对的value进行聚合操作。

        (3)语法：rdd对象.reduceByKey(f)
             # f是一个函数(方法)，其映射关系为：f:(T, T) -> T

        (4)注意：函数f只负责聚合操作(不参与分组)，其聚合逻辑例子如下：
            比如某组的value是[1,2,3]，函数为lambada x,y: x+y，则聚合逻辑为：
                先将1和2进行聚合，得到3；再将上一个聚合结果3和3进行聚合，得到6；最终结果为6。

        (5)整个reduceByKey()算子举例：
                已知[('a',1), ('a',2), ('b',2), ('b',5), ('b',8)]，函数为lambda x, y: x+y，
            则结果为：[('a', 3), ('b', 15)]。
"""
from pyspark import SparkConf, SparkContext
import os

### 设置python环境路径
os.environ["PYSPARK_PYTHON"] = "D:\Anaconda\envs\Calculation\python.exe"

### 建立SparkContext对象
conf = SparkConf().setMaster("local[*]").setAppName("test_spark_app")
sc = SparkContext(conf=conf)



### 示例1 map()算子
print("--------------------- 示例1 -------------------------")
### 准备一个RDD对象
rdd1 = sc.parallelize([1, 2, 3, 4, 5])


### 通过map()算子对RDD对象进行操作(此处将全部数据都乘10)
## 定义一个函数
def func(x):
    return x * 10

## 调用map()算子
rdd2 = rdd1.map(func)
print(rdd2.collect())     # [10, 20, 30, 40, 50]

## 注：以上简单函数可以通过匿名函数简化为一行代码并直接输入map()算子中
# rdd2 = rdd1.map(lambda x: x * 10)


### 扩展：链式调用多种map()算子
rdd3 = rdd1.map(lambda x: x * 10).map(lambda x: x + 5)
print(rdd3.collect())     # [15, 25, 35, 45, 55]



### 示例2 flatMap()算子
print("--------------------- 示例2 -------------------------")
### 准备一个RDD对象
rdd4 = sc.parallelize(["itheima itcast 666", "itheima itheima itcast", "python itheima"])


### 通过flatMap()算子将列表中每个单词提取出来(其中涉及将lambda函数结果运行后对嵌套列表的解除操作)
rdd5 = rdd4.flatMap(lambda x: x.split(" "))
print(rdd5.collect())     



### 示例3 reduceByKey()算子
print("--------------------- 示例3 -------------------------")
### 准备一个RDD对象
rdd6 = sc.parallelize([('男', 99), ('男', 88), ('女', 44), ('女', 33), ('女', 55)])

### 通过reduceByKey()算子求出男生和女生两组成绩之和
rdd7 = rdd6.reduceByKey(lambda x, y: x + y)
print(rdd7.collect())




### 停止SparkContext对象的运行（停止PySpark程序）
sc.stop()
