"""
eval()函数：用于去掉字符串最外侧的引号，并按照python语句执行去掉引号后的字符串
    注：eval经常与input一起使用
"""

s='3.14+3'
print(s,type(s))
x=eval(s) # 使用eval函数去掉s这个字符串中左右的引号，执行了加法运算
print(x,type(x))

hello='北京欢迎你'
print(hello)
print(eval('hello')) # 输出了北京欢迎你
# print(eval('北京欢迎你')) # NameError: name '北京欢迎你' is not defined

# eval函数经常与input()函数一起使用，用来获取用户输入的数值
age=input('请输入您的年龄：')
print(age,type(age))
age=eval(input('请输入您的年龄：')) # 将字符串类型转换成int类型，相当于int(age)
print(age,type(age))
