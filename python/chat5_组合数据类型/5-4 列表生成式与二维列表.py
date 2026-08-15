### 示例1 列表生成式(只需一步)
print("--------------------- 示例1 -------------------------")
import random  # random模块可以提供生成伪随机数的各种函数。
lst=[item for item in range(1,11)]
print(lst)

lst=[item*item for item in range(1,11)]
print(lst)


# random.randint(a, b)生成[a, b]范围内的随机整数,
# 注：下划线_本身也是变量,用于表示无特定意义的变量,比如此处_变量单纯循环,并没有参与列表元素的操作
lst=[random.randint(1,100) for _ in range(10)] 
print(lst)

# 从序列中选择符合条件的元素组成新的列表
lst=[i for i in range(10) if i%2==0]
print(lst)


### 示例2 二维列表创建、遍历与列表生成式
print("--------------------- 示例2 -------------------------")
# 创建二维列表(每行中括号数据对应的矩阵为行数据)
lst=[
    ['城市','环比','同比'],
    ['北京',102,103],
    ['上海',104,503],
    ['深圳',100,39],
]
print(lst)

# 遍历二维列表使用双层for循环，生成表格形式
for row in lst: # 行
    for item in row: # 列
        print(item,end='\t')
    print() # 换行

# 列表生成式生成一个4行5列的二维列表
lst2=[[j for j in range(i,i+5)] for i in range(4)]
print(lst2)