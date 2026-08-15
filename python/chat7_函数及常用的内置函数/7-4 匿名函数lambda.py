"""
一、匿名函数lambda：是指没有名字的函数，这种函数只能使用一次，
        
二、使用场景：一般是在函数的函数体只有一句代码且只有一个返回值时，可以使用匿名函数来简化

三、语法：s = lambda 传入参数: 函数体(一行代码)
        解释: 
            传入参数：就是匿名函数的形式参数，如：x,y表示接收2个形式参数。
            函数体：就是函数的执行逻辑，要注意只能写一行，无法写多行代码。
            s：函数的返回值。
"""
### 示例1 匿名函数的使用
print("--------------------- 示例1 -------------------------")
## 正常函数
def calc(a,b):
    return a+b

print(calc(10,20)) # 30

## 匿名函数
s = lambda a,b: a+b  # s就是一个匿名函数，简化代码并达到正常函数的效果
print(type(s)) # 数据类型是函数类型<class 'function'>

# 匿名函数的调用
print(s(10,20)) # 30


### 示例2 通过匿名函数进行列表取值
print("--------------------- 示例2 -------------------------")
lst=[10,20,30,40,50]
for i in range(len(lst)):
    result = lambda x: x[i] # 根据索引取值
    print(result(lst))


### 示例3 通过匿名函数进行排序
print("--------------------- 示例2 -------------------------")
# 通过匿名函数对下面列表中的成绩进行排序
student_scores=[
    {'name':'陈美美','score':98},
    {'name':'王一一','score':95},
    {'name':'张天乐','score':100},
    {'name':'白雪儿','score':65}
]

student_scores.sort(key=lambda x:x.get('score'), reverse=True)
print(student_scores)
# 解释：sort()是列表的排序方法，其参数key是指定排序的依据，reverse=True是降序排序
# lambda x:x.get('score')是个匿名函数，获取函数字典x的键'score'对应的值
# 当sort()执行时，参数key会将列表student_scores的每个元素提取出来，并循环代入匿名函数的形参x中