"""
程序的组织结构：顺序结构、选择/分支结构(见后面if/switch语句)、循环结构(见后面for/while循环)
"""
### 示例 顺序结构语句
# 赋值运算符的顺序 从右到左
name='张琨'
age=24
a=b=c=d=100 # 链式赋值
a,b,c,d='room' # 字符串分解赋值
print(a)
print(b)
print(c)
print(d)
print('--------输入输出语句也是典型的顺序结构---------')
name=input('请输入您的姓名：')
age=eval(input('请输入您的年龄：'))
luck_number=eval(input('请输入您的幸运数字：'))
print('姓名：',name)
print('年龄：',age)
print('幸运数字：',luck_number)
