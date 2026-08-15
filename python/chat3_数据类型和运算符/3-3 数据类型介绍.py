"""
数据的五种类型：整数类型、浮点数类型、复数类型、字符串类型、布尔类型。
    注意：他们都是python当中的不可变数据类型。

其中布尔类型：用来表示"真"值或"假"值的数据类型，
    在python中用标识符True或False表示布尔类型的值，其中True表示整数1，False表示整数0。
    注：在python中一切皆对象，而所有对象的布尔值见下面：
        以下对象在布尔上下文中被视为 False：
        1. 空值：None
        2. 假值：False
        3. 数值零：0, 0.0, 0j
        4. 空序列：'', (), [], {}
        5. 空集合：set(), frozenset(), range(0)
        6. 自定义对象的 __len__() 返回 0
        7. 自定义对象的 __bool__() 返回 False

        其他所有对象都被视为 True
"""

### 示例1 整数类型的四种表示形式
print("--------------------- 示例1 -------------------------")
num=987 # 默认是十进制，表示整数
num2=0b1010100011 # 使用二进制表示整数(0b或0B)
num3=0o765 # 使用八进制表示整数(0o或0O)
num4=0x87ABF # 使用16进制表示整数(0x或0X)
print(num)
print(num2) # 打印的都是各种进制转换成十进制的结果
print(num3)
print(num4)

### 示例2 浮点数类型的使用
print("--------------------- 示例2 -------------------------")
height=187.6 # 身高
print(height)
print(type(height)) # type()查看height这个变量的数据类型

x=10
y=10.0
print('x的数据类型：',type(x)) # int
print('y的数据类型：',type(y)) # float

x=1.99E1413
print('科学计数法：',x,'x的数据类型：',type(x))

print(0.1+0.2) # 不确定的尾数问题：0.30000000000000004
print(round(0.1+0.2,1)) # round(x,n)表示对浮点数x保留n位小数

### 示例3 复数类型的使用
print("--------------------- 示例3 -------------------------")
x=123+456j
print(x)
print('实数部分：',x.real)
print('虚数部分：',x.imag)

### 示例4 字符串类型的使用
print("--------------------- 示例4 -------------------------")
city='深圳'
address="深圳市南方科技大学"
print(city)
print(address)
# 多行字符串
info='''地址：深圳市南方科技大学
     收件人：张琨
     手机号：188000000
'''
info2="""地址：深圳市南方科技大学
     收件人：张琨
     手机号：188000000
"""
print(info)
print()
print(info2)
print(type(info2))

### 示例5 布尔类型的使用
print("--------------------- 示例5 -------------------------")
x=True
print(x)
print(type(x))
print(x+10) # 11-->1+,说明True布尔值为1
print(False+10) # 10-->0+10，说明False布尔值为0

print('----------')
print(bool(18)) # 测试整数18的布尔值为True
print(bool(0),bool(0.0)) # 测试0与0.0的布尔值都为False
#总结：非0的整数布尔值都是True
print(bool('北京欢迎你')) # True
print(bool('')) # False
#所有非空字符串的布尔值都是True
print(bool(False))
print(bool(None))
# 所有情况的布尔值见课程P16