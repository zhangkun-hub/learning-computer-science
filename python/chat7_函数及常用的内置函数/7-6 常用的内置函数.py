"""
一、常用的数据类型转换函数：
    1.bool(obj)：获取指定对象obj的布尔值；
    2.str(obj)：获取指定对象obj转成字符串类型；
    3.int(x)：将x转成int类型；
    4.float(x)：将x转成float类型；
    5.list(sequence)：将序列sequence转成列表类型；
    6.tuple(sequnece)：将序列sequence转成元组类型；
    7.set(sequence)：将序列sequence转成集合类型；
    8.dict(sequence)：将序列sequence转成字典类型。

二、常用的数学函数：
    1.abs(x)：获取x的绝对值；
    2.divmod(x,y)：获取x除以y的商和余数；
    3.max(sequence)：获取序列sequence的最大值；
    4.min(sequence)：获取序列sequence的最小值；
    5.sum(iter)：对可迭代对象进行求和运算；
    6.pow(x,y)：获取x的y次幂；
    7.round(x,d)：对x进行保留d位小数，结果四舍五入。

三、常用的迭代器操作函数：
    1.sorted(iter)：对可迭代对象进行排序；
    2.reversed(sequence)：反转序列生成新的迭代器对象；
    3.zip(iter1,iter2)：将iter1与iter2打包成元组并返回一个可迭代的zip对象(以短序列为主)；
    4.enumerate(iter, start=n)：根据iter对象创建一个enumerate对象，start=n表示序号从n开始；
    5.all(iter)：判断可迭代对象iter中所有元素的布尔值是否都为True；
    6.any(iter)：判断可迭代对象iter中所有元素的布尔值是否都为False；
    7.next(iter)：获取迭代器的下一个元素；
    8.filter(fun,iter)：将序列iter依次执行函数fun，然后将结果为True的保留并返回一个迭代器对象；
    9.map(fun,iter)：将序列iter依次执行函数fun，然后将结果返回一个迭代器对象。

四、常用的其他内置函数：
    1.format(value,format_spec)：将value以format_spec格式进行显示；
    2.len(s)：获取s的长度或s元素的个数；
    3.id(obj)：获取对象的内存地址；
    4.type(x)：获取x的数据类型；
    5.eval(s)：执行s这个字符串所表示的Python代码。
"""
### 示例1 常用的数据类型转换函数
print("--------------------- 示例1 -------------------------")
print('非空字符串的布尔值：', bool('hello'))  # True
print('空字符串的布尔值：', bool(''))  # False

print('空列表的布尔值：', bool([]))  # False
print('空列表的布尔值：', bool(list()))  # False

print('空元组的布尔值：', bool(()))  # False
print('空元组的布尔值：', bool(tuple()))  # False

print('空字典的布尔值：', bool({}))   # False
print('空字典的布尔值：', bool(dict()))  # False

print('空集合的布尔值：', bool(set()))  # False
print()

print('非0数值型的布尔值：', bool(123)) # True
print('整数0的布尔值：', bool(0)) # False
print('浮点数0.0的布尔值：', bool(0.0)) # False
print()

# 将其他类型转成字符串类型
lst=[10,20,30]
print(type(lst),lst) # <class 'list'> [10, 20, 30]
s=str(lst)
print(type(s),s) # <class 'str'> [10, 20, 30]

# 注意事项(以下是不能进行转换的，会报错)
# print(int('98.7'))
# print(int('a'))


### 示例2 常用的数学函数
print("--------------------- 示例2 -------------------------")
print('绝对值：', abs(100), abs(-100), abs(0)) # 绝对值： 100 100 0
print('商和余数：', divmod(13,4))  # 商和余数： (3, 1)
print('最大值：', max([10,4,56,78,4])) # 最大值： 78
print('最小值：', min([10,4,56,78,4])) # 最小值： 4
print('最小值：', min('hello')) # 最小值： e
print('求和：', sum([10,34,45])) # 求和： 89
print('2的3次幂：', pow(2,3)) # 2的3次幂： 8
print()

print('四舍五入：', round(3.1415926)) # 四舍五入： 3
print('四舍五入(保留两位小数)：', round(3.1415926, 2)) # 四舍五入(保留两位小数)： 3.14
print('四舍五入(对个位进行)：', round(314.15926, -1))  # 四舍五入(对个位进行)： 310.0
print('四舍五入(对十位进行)：', round(314.15926, -2))  # 四舍五入(对十位进行)： 300.0


### 示例3 常用的迭代器操作函数
print("--------------------- 示例3 -------------------------")
lst = [54, 56, 77, 4, 567, 34]
# 排序操作
asc_lst=sorted(lst)
desc_lst=sorted(lst, reverse=True)
print('原列表：', lst)  # 原列表： [54, 56, 77, 4, 567, 34]
print('升序：', asc_lst) # 升序： [4, 34, 54, 56, 77, 567]
print('降序：', desc_lst) # 降序： [567, 77, 56, 54, 34, 4]
print()

# reversed反向
new_lst=reversed(lst)
print(type(new_lst)) # <class 'list_reverseiterator'>(表示迭代器对象)
print(list(new_lst)) # [34, 567, 4, 77, 56, 54]
print()

# zip
x=['a', 'b', 'c', 'd']
y=[10,20,30,40,50]
zipobj = zip(x,y)
print(type(zipobj)) # <class 'zip'>
print(list(zipobj)) # [('a', 10), ('b', 20), ('c', 30), ('d', 40)]
print()

# enumerate
enum = enumerate(y, start=1) # start表示序号从1开始
print(type(enum)) # <class 'enumerate'>
print(tuple(enum)) # ((1, 10), (2, 20), (3, 30), (4, 40), (5, 50))
print()

# all与any
lst = [54, 56, 77, 4, 567, 34]
lst2=[10, 20, '', 30]
lst3=['', [], {}, set(), 0, 0.0]
print(all(lst)) # True
print(all(lst2)) # False
print(any(lst2)) # True
print(any(lst3)) # False
print()

# next
x=['a', 'b', 'c', 'd']
y=[10,20,30,40,50]
zipobj = zip(x,y)
print(next(zipobj)) # ('a', 10)
print(next(zipobj)) # ('b', 20)
print(next(zipobj)) # ('c', 30)
print(next(zipobj)) # ('d', 40)
print()

# filter
def fun(num):
    return num%2  # 奇数为True，偶数为False
obj = filter(fun, range(10)) # 将序列0-9通过函数fun进行筛选，将输出布尔值为True的保留
print(type(obj)) # <class 'filter'>
print(list(obj)) # [1, 3, 5, 7, 9]
print()

# map
obj2 = map(fun, range(10))
print(type(obj2)) # <class 'map'>
print(list(obj2)) # [0, 1, 0, 1, 0, 1, 0, 1, 0, 1]


### 示例4 常用的其他内置函数
print("--------------------- 示例4 -------------------------")
## format的使用
# 数值型默认右对齐(>)，'20'表示前面的宽度
print(format(3.14, '20'))   #                 3.14
print(format(3.14, '*>20')) # ****************3.14

# 字符串默认左对齐(<)，'20'表示后面的宽度
print(format('hello', '20'))   # hello
print(format('hello', '*<20')) # hello***************

# 居中对齐
print(format('hello', '*^20')) # *******hello********