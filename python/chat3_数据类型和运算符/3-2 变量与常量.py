### 变量的定义
luck_number=8 # 创建一个整形变量luck_number, 并为其赋值为8

my_name='张琨' # 字符串类型的变量

print('luck_number的数据类型是：',type(luck_number)) # <class 'int'>
print(my_name,'的幸运数字是：',luck_number)

# python动态修改变量的数据类型，通过不同类型的值就可以直接修改
luck_number='北京欢迎你'
print('luck_number的数据类型是：',type(luck_number)) # <class 'str'>

# 在python中允许多个变量指向同一个值
no=number=1024 # no与number都指向了1024这个整数值
print(no,number)
print(id(no)) # 查看对象的内存地址的
print(id(number))

### 常量的定义
pi=3.1415926 # 定义了一个变量
PI=3.1415926 # 定义了一个常量（即用大写表示常量是程序员之间共识，并且常量定义取值后不可随意修改）