"""
一、函数：是将一段实现功能的完整代码,使用函数名称进行封装,通过函数名称进行调用,达到一次编写多次调用

二、内置函数：输出函数print()、输入函数input()、列表定义函数list()、...

三、自定义函数：
    def 函数名称(参数列表):
        函数体
        return 返回值   # 注意：return是不是必须要写的

四、函数的调用：变量 = 函数名(参数列表)       # 注意：如果没有return，则直接写：函数名(参数列表)

五、形参与实参：函数定义处的参数列表是形参、函数调用处的参数列表是实参

六、函数的返回值return：函数的运行结果使用return关键字进行返回。
        特点:1.return可以出现在函数中的任意一个位置，用于结束函数；
            2.返回值可以是一个值，或多个值，如果返回的值是多个，结果是一个元组类型；
            3.解包赋值：对于返回的多个值，可以用多个变量进行解包赋值，见74行代码示例。
"""
### 示例1 函数的定义和调用
print("--------------------- 示例1 -------------------------")
# 函数的定义
def get_sum(num): # num是形参
    s = 0
    for i in range(1, num+1):
        s+=i
    print(f"1到{num}之间的累加和为：{s}")

# 函数的调用(括号里的数字是实参)
get_sum(10) # 1-10之间的累加和
get_sum(100) # 1-100之间的累加和
get_sum(1000) # 1-1000之间的累加和
print()

# 注意对于无返回值的函数，直接打印结果是None
print(get_sum(10))


### 示例2 函数的返回值使用
print("--------------------- 示例2 -------------------------")
## 定义有一个返回值的函数
def calc2(a,b):
    s=a+b
    return s

# 调用
get_s = calc2(1,2)
print(get_s)

# 嵌套调用
get_s2 = calc2(calc2(1,2), 3)
print(get_s2)
print()

## 定义有多个返回值的函数
def get_sum2(num):
    s=0        # 累加和
    odd_sum=0  # 奇数和
    even_sum=0 # 偶数和
    for i in range(1,num+1):
        if i%2 != 0:
            odd_sum+=i  # 奇数和
        else:
            even_sum+=i # 偶数和
        s+=i  # 累加和
    return odd_sum, even_sum, s

# 调用
result=get_sum2(10)
print(type(result))  # 元组类型<class 'tuple'>
print(result)        # (25, 30, 55)
print()

# 解包赋值
a,b,c=get_sum2(20)
print(a)
print(b)
print(c)