"""
一、字典：根据一个信息查找另一个信息的方式构成了“键(key)值(value)对”，它是可变但无序的序列。

二、字典的创建方式：
    1.使用{}直接创建字典，即：字典名 = {key1:value1, key2:value2,...}
    2.使用函数dict()创建，即：字典名 = dict(key1=value1, key2=value2,...)
    3.使用函数zip()创建，需要两步：1.a = zip(lst1,lst2)，其lst1为键序列，lst2为值序列。
                                2.字典名 = dict(a)
    注：空字典的创建为：{}

三、删除方式：del 字典名

四、字典的特点：
    1.无序（Python 3.7+ 保留插入顺序，但主要按key访问）
    2.键值对存储结构
    3.字典中每个键必须唯一且为不可变数据类型（字符串、数字、元组），而值随意
    4.字典本身是可变序列：可修改、添加、删除键值对
    5.使用花括号 {}定义

五、作用
    1.存储映射关系
    2.快速查找（基于哈希表）
    3.配置信息存储

六、字典元素的访问取值：(注:若keyN不存在，则d[keyN]会报错，但d.get(keyN)输出None)
    设字典名为d，则 d[keyN] 或 d.get(keyN) 输出键keyN对应的值valueN

七、字典的遍历：
    1.遍历key与对应value的所组成的一个元组：
        for element in d.items():
            pass
            
    2.分别遍历出key和value：
        for key,value in d.items():
            pass
"""
### 示例1 字典的创建与删除
print("--------------------- 示例1 -------------------------")
# (1)由{}创建字典，形式为d={key1:value1,key2:value2...}
d={10:'cat',20:'dog',30:'pet',20:'zoo'}
print(d) # key相同时，value值进行了覆盖

# (2)zip函数创建字典，形式为zip(lst1,lst2)
lst1=[10,20,30,40]
lst2=['cat','dog','pet','zoo','car']
zipobj=zip(lst1,lst2)
print(zipobj) # 映射的结果是一个zip对象，转换方式有以下两种
# print(list(zipobj)) # 使用内置list函数转换成列表类型，此时列表中元素是一个元组类型
d=dict(zipobj) # 使用内置函数dict转换成字典类型
print(d)
print()

# 使用参数创建字典
d=dict(cat=10,dog=20) # 左侧cat是key,右侧的是value
print(d)

t=(10,20,30) # 是一个元组
print({t:10}) # t是key,10是value,说明元组可以当作字典中的key，因为它是不可变数据类型

# lst=[10,20,30]
# print({lst:10})    # 报错，因为列表是可变数据类型不能作为键


#lst=[10,20,30] # 是一个列表
#print({t:10}) # 报错，说明列表不可以当作字典中的key,因为它是可变数据类型

# 注意字典属于序列,并且是可变数据类型，所以可以用列表的相关函数操作
print('max:',max(d))
print('min:',min(d))
print('len:',len(d))
# 字典中的删除
del d


### 示例2 字典元素的访问和遍历
print("--------------------- 示例2 -------------------------")
d={'hello':10,'world':20,'python':30}
print(d)
# 访问字典中的元素
# (1)使用d[key]
print(d['hello'])
# (2)d.get(key)
print(d.get('hello'))

# 二者之间是有区别的，如果输入的key不存在，则d[key]会报错，但d.get(key)可以指定默认值,如下所示
# print(d['java']) # KeyError: 'java'
print(d.get('java'))     # 输出None,但没有报错
print(d.get('java', '不存在'))   # 输出：不存在


# 字典的遍历
for item in d.items(): #d.item函数将字典中的数据转成key-value的形式，以元组的方式进行展现
    print(item) # 遍历了由key和对应value组成的元组

# 由上可知，在使用for循环遍历时，可以分别获取key,value
for key,value in d.items():
    print(key,'--->',value)