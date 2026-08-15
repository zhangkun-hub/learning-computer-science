"""
一、元组：不可变序列,用()来定义,元素与元素之间使用英文的逗号分隔
        注意:1.元素的数据类型可以是任意的,甚至是序列；
            2.元组只有一个元素时逗号也不能省；
            3.因为是不可变序列，所以没有增、删、改、查等操作。

二、元组的创建方式：
    1.直接使用()创建，即：元组名 = (element1, element2,..., elementN)
    2.使用函数tuple()创建，即：元组名 = tuple(序列)

三、删除方式：del 元组名

四、元组的特点：
    1.有序：元素按添加顺序排列
    2.不可变：创建后不能修改，即无增、删、改、查等操作
    3.允许重复元素
    4.使用圆括号 ()定义  
    5.逗号必须要有，哪怕只有一个元素k，也必须写成(k,)形式  

五、作用：
    1.存储不应改变的数据集合
    2.用作字典键（因为不可变）
    3.函数返回多个值
    4.比列表更快的遍历速度    

六、元组的访问、切片、遍历等操作与各种序列都是完全相同的。

七、元组生成式(需要两步)：例如：
    t=(i for i in range())       
    t=tuple(t)
"""
### 示例1 元组的创立与删除
print("--------------------- 示例1 -------------------------")
# 使用小括号创建元组
t=('hello',[10,20,30],'python','world')
print(t)

# 使用内置函数tuple()创建元组
t=tuple('helloworld')
print(t)

t=tuple([10,20,30,40])
print(t)

print('10在元组中是否存在：',(10 in t))
print('10在元组中是否不存在',(10 not in t))
print('最大值',max(t))
print('最小值',min(t))
print('len',len(t))
print('t.index:',t.index(10))
print('t.count',t.count(10))

# 如果元组中只有一个元素，则逗号不能省，否则只是单纯的整数、浮点数等类型
t=(10)
print(t,type(t))
y=(10,)
print(y,type(y))

# 元组的删除
del t
# print(t) 已删除不存在，故输出t会报错


### 示例2 元组元素的访问与遍历
print("--------------------- 示例2 -------------------------")
t=('hello',[10,20,30],'python','world')
# 根据索引访问元组
print(t[0])
t2=t[0:3:2] # 元组支持切片操作
print(t2)

# 元组的遍历
for item in t:
    print(item)
print()

for i in range(len(t)):
    print(i,t[i])
print()

for index,item in enumerate(t):
    print(index,'--->',item)
print()

for index,item in enumerate(t,start=11):
    print(index,'--->',item)


### 示例3 元组生成式
print("--------------------- 示例3 -------------------------")
t=(i for i in range(1,4))
print(t) #是个生成器对象，不是元组
#t=tuple(t) 此时已是元组,但因为不是生成器,无法用下面的next代码取出元素而报错,所以这里加“ # ”
#print(t)
# 遍历
#for item in t:
#    print(item)

# 取出生成器里的元素方式：next方法
print(t.__next__())
print(t.__next__())
print(t.__next__())

t=tuple(t)
print(t) # 由于next已将t中生成器的所有元素全部取出，此时t已无元素