"""
一、Python的异常类型继承树：
    BaseException    # 所有异常的顶级基类，包含系统级异常
    ├── SystemExit
    ├── KeyboardInterrupt
    ├── GeneratorExit
    └── Exception    # BaseException的子类，是通常的异常处理，不包含系统级异常
        ├── ArithmeticError
        ├── LookupError
        ├── TypeError
        ├── ValueError
        ├── OSError
        ├── ...
        └── 其他所有用户定义的异常

二、常见的异常类型：
    1.ZeroDivisionError：除数为0时引发的异常；
    2.IndexError：索引超出范围所引发的异常；
    3.KeyError：字典取值时key不存在的异常；
    4.NameError：使用一个没有声明的变量时引发的异常；
    5.SyntaxError：Python中的语法错误；
    6.ValueError：传入的值错误；
    7.AttributeError：属性或方法不存在的异常；
    8.TypeError：类型不合适引发的异常；
    9.IndentationError：不正确的缩进引发的异常。

三、raise关键字：
    1.定义：抛出一个异常，从而提醒程序出现了异常情况，程序能够正确地处理这些异常情况
        注意：该异常也可以是非程序异常，而是违反逻辑的异常(比如示例1的性别输入不是男或女的情形)

    2.语法结构：raise 异常类型('错误信息')
"""
### 示例1 raise关键字的使用
print("--------------------- 示例1 -------------------------")
try:
    gender = input('请输入您的性别：')
    if gender != '男' and gender != '女':
        raise Exception('性别只能是男或女') # 抛出异常对象的描述信息

    else:
        print('您的性别是：', gender)
    
except Exception as e:  # 将raise抛出的异常对象由该行的Exception捕获，并命名为e(也可以是其他)
    print(e)


### 示例2 常见的异常类型
print("--------------------- 示例2 -------------------------")
# 1.ZeroDivisionError
# print(10/0)

# 2.IndexError
# lst = [10,30,50,90]
# print(lst[4])

# 3.KeyError
# d = {'name':'ysj', 'age':20}
# print(d['gender'])

# 4.NameError
# print(hello)  # 因为hello这个变量没有定义

# 5.SyntaxError
# print('hello)   # 因为字符串的引号少另一半

# 6.ValueError
# print(int('a'))   # a没有办法转成整数

# 7.AttributeError
# i = 10
# print(i.name)  # 整型里没有name这个属性或方法

# 8.TypeError
# print('hello' + 123)

# 9.IndentationError
    # print('hello')  # 缩进不正确