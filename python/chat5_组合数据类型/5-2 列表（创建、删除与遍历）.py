"""
一、列表：是指一系列按特定顺序排列的元素组成。
    其使用[]定义列表，元素与元素之间使用“英文的逗号”分隔(注:元素的数据类型可以是任意的,甚至是序列)

二、列表的创建：
    1.直接用[]创建，即：列表名 = [element1, element2,..., elementN]
    2.使用内置函数list()创建，即：列表名 = list(序列)

三、列表的删除：del 列表名

四、列表的特点：
    1.有序：元素按添加顺序排列
    2.可变：创建后可修改（增删改元素）
    3.允许重复元素
    4.使用方括号 []定义

五、作用：
    1.存储有序数据集合
    2.需要频繁修改数据的场景
    3.栈、队列等数据结构实现
"""

### 示例1 列表的创建与删除
print("--------------------- 示例1 -------------------------")
# 直接使用[]创建列表
lst=['hello','world',98,100.5] # 此时列表中元素分别是每个逗号对应一个元素
print(lst)
# 可以使用内置函数list()创建列表
lst2=list('hello world')
lst3=list(range(1,10,2)) # 从1开始到10结束，步长为2，不包含10
print(lst2)
print(lst3)
# 创建全零列表
hL = [0 for x in range(5)]
print(hL)

# 列表是序列中的一种，对序列的操作符，运算符，函数均可以使用
print('-'*40)
print(lst+lst2+lst3) # 序列的相加操作
print(lst*3) # 序列的相乘操作
print(len(lst))
print(len(lst2))
print(min(lst3))
print(lst2.count('o')) # 统计o的个数
print(lst2.index('o')) # o在列表lst2中第一次出现的位置

# 列表的删除操作
lst4=[10,20,30]
print(lst4)
# 删除列表
del lst4
# print(lst4)   NameError: name 'lst4' is not defined. Did you mean: 'lst'?


### 示例2 列表的遍历
print("--------------------- 示例2 -------------------------")
lst=['hello','world','python','php']
# 第一种遍历方式：使用遍历循环for遍历元素列表
for item in lst: # item是自己定义的变量名
    print(item)

# 第二种遍历方式：使用for循环，range()函数，len()函数，根据索引进行遍历
for i in range(0,len(lst)):
    print(i,'-->',lst[i])

# 第三种遍历方式：enumearte()函数，可以得到两个值，其中第一个是序号(不是索引)，第二个是元素
for index,item in enumerate(lst): # index与item是自己定义的变量名
    print(index,item) # 注意输出的index是序号不是索引 所以其值可以修改
# 手动修改序号的起始值
for index,item in enumerate(lst,start=1): # 修改起始元素序号为1
    print(index,item)
for index,item in enumerate(lst,1): # 与14号代码相同,即start=可以不写
    print(index,item)