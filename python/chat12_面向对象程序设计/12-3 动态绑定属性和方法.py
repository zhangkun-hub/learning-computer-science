"""
动态绑定属性和方法：
    也就是在创建完类型和对象后，可以为对象创建类型里没有的属性或方法，具体见示例1
"""
### 示例1 动态绑定属性和方法
print("--------------------- 示例1 -------------------------")
# 创建一个Student类型
class Student:
    # 类属性
    school='北京XXX教育'

    # 初始化方法
    def __init__(self, xm, age):  # xm,age是方法的参数，是局部变量(作用域是整个__init__方法)
        # 实例属性：self.变量名
        self.name = xm  # 左侧是实例属性，xm是局部变量，这表示将值xm赋值给实例属性self.name
        self.age = age  # 将局部变量的值age赋值给实例属性self.age

    # 实例方法
    def show(self):
        print(f'我叫{self.name}，今年{self.age}岁了')

# 创建两个Student类型的对象
stu = Student('ysj', 18)
stu2 = Student('陈梅梅', 20)

# 查看两个对象的同一属性(属性值不同)
print(stu.name, stu.age)   # ysj 18
print(stu2.name, stu2.age) # 陈梅梅 20

### 为stu2动态绑定一个实例属性
stu2.gender = '男'
print(stu2.name, stu2.age, stu2.gender) # 陈梅梅 20 男

### 动态绑定方法
def introduce():
    print('我是一个普通的函数，我被绑定成了stu2对象的方法')

# 把函数introduce赋值给方法stu2.fun，从而成为一个实例方法(其中fun是自己命名的方法)。
stu2.fun = introduce 

# 此时fun就是stu2对象的实例方法了，可以按照实例方法去调用
stu2.fun() # 我是一个普通的函数，我被绑定成了stu2对象的方法