"""
一、字典的相关操作：
d.keys()：获取所有的key数据；
d.values()：获取所有的value数据；
d.item()：将字典中的数据转成key-value的形式，其中key-value以元组类型进行展现；
d.get(key,default)：获取字典中指定键key的值，若不存在则输出default(不写则默认输出None)；
d.pop(key,default)：key存在时获取相应的value，同时删除1key-value对，否则输出default；
d.popitem()：随机从字典取出一个key-value对，结果为元组，同时将该key-value从字典中删除；
d.clear()：清空字典中所有的key-value对；

二、字典生成式：
    1.d = {key:value for key in range()}
    2.d = {key:value for key,value in zip(lst1,lst2)}
"""
### 示例1 字典的相关操作方法
print("--------------------- 示例1 -------------------------")
d={1001:'李梅',1002:'王华',1003:'张峰'}
print(d)  # {1001: '李梅', 1002: '王华', 1003: '张峰'}

# 向字典中添加元素
d[1004]='张丽丽' # 直接使用赋值运算符向字典中添加元素
print(d)  # {1001: '李梅', 1002: '王华', 1003: '张峰', 1004: '张丽丽'}
print()

# 获取字典中的所有key
keys=d.keys()    
print(keys)          # dict_keys([1001, 1002, 1003, 1004])
print(list(keys))    # [1001, 1002, 1003, 1004]
print(tuple(keys))   # (1001, 1002, 1003, 1004)
print()

# 获取字典中所有的value
values=d.values()
print(values)
print(list(values))
print(tuple(values))
print()

# 将字典中的数据转成key-value的形式，以元组的方式进行展现
lst=list(d.items())
print(lst)

# 再将其转成字典类型
d=dict(lst)
print(d)
print()

# 使用pop函数删除元素
print(d.pop(1001))
print(d)
print(d.pop(1008,'不存在')) # 即字典d中1008这个key不存在

# 随机删除
print(d.popitem())
print(d)
print()

# 清空字典中所有的元素
d.clear()
print(d)
# python中一切皆对象，每个对象都有一个布尔值
print(bool(d)) # 空字典的布尔值为false(空元组、空列表等也是False)


### 示例2 字典生成式
print("--------------------- 示例2 -------------------------")
import random
d={item:random.randint(1,100) for item in range(4)}
print(d)

# 创建两个列表
lst=[1001,1002,1003]
lst2=['陈梅梅','王一一','李丽丽']
d={key:value for key,value in zip(lst,lst2)}
print(d)   