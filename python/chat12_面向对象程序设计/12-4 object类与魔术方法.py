"""
一、object类：所有类直接或间接的父类。
        特点：所有类都拥有object类的属性和方法(具体定义理解见9-7继承)

二、object类中的方法称为魔术方法：首尾双下划线的实例方法(第一个参数必须是self)，各自都有特殊功能。

三、魔术方法举例：(注意，魔术方法非常多，这里只列举几个常用的)
    1.__init__构造方法：前面9-2已经详细介绍过了。

    2.__str__字符串方法：(例子见示例1)
        (1)作用：控制类的对象转换为字符串的行为。
        (2)返回值：字符串类型，具体内容由该方法体决定。
        注意：没有__str__方法直接打印对象结果：会自动调用__str__，输出内容为该对象内存地址等信息。

    3.__lt__比较判断方法：(例子见示例2)
        (1)作用：对两个对象的某个属性等进行比较(只能进行">"或"<"的比较)
        (2)传入参数：other（表示另一个类对象）
        (3)返回值：True或False
        注意：没有__lt__方法直接对两个对象进行比较会报错。

    4.__le__比较判断方法：(例子见示例3)
        (1)作用：对两个对象的某个属性等进行比较(相比__lt__可以进行">=或"<="的比较)
        (2)传入参数：other（表示另一个类对象）
        (3)返回值：True或False
        （与__lt__类似，只是可以多进行小于等于和大于等于的判断）

    5.__eq__相等判断方法：(例子见示例4)
        (1)作用：对两个对象的某个属性等判断是否相等
        (2)传入参数：other（表示另一个类对象）
        (3)返回值：True或False
        （注意：没有__eq__方法直接对两个对象进行相等判断，是判断两个对象的内存地址是否一致）

"""
class Student:
    def __init__(self, name, age):
        self.name = name   # 学生姓名
        self.age = age     # 学生年龄

    # __str__字符串方法
    def __str__(self):
        return f"Student类对象，name:{self.name}，age:{self.age}"
    
    # __lt__比较判断方法（对两个学生的年龄进行比较）
    def __lt__(self, other):
        return self.age < other.age
    
    # __le__比较判断方法（与__lt__类似，只是可以多进行小于等于和大于等于的判断）
    def __le__(self, other):
        return self.age <= other.age
    
    # __eq__相等判断方法（对两个学生的年龄进行相等判断）
    def __eq__(self, other):
        return self.age == other.age

stu1 = Student('周杰伦', 31)
stu2 = Student('林俊杰', 36)
stu3 = Student('蔡徐坤', 36)


### 示例1 __str__字符串方法
print("--------------------- 示例1 -------------------------")
# 没有__str__方法时直接打印对象或者转换成字符串打印的结果如下：
# print(stu1)       # <__main__.Student object at 0x000001EE01A7D850>
# print(str(stu1))  # <__main__.Student object at 0x000001EE01A7D850>
# 可以看到都是表示内存地址(没啥作用)，所以需要用__str__方法进行改造

# 使用__str__字符串方法后的打印结果
print(stu1)        # Student类对象，name:周杰伦，age:31
print(str(stu1))   # Student类对象，name:周杰伦，age:31
# 可以看到直接打印对象的结果是__str__字符串方法的返回结果


### 示例2 __lt__比较判断方法
print("--------------------- 示例2 -------------------------")
# 没有__lt__方法直接对两个对象比较会报错
# print(stu1 < stu2) # TypeError: '<' not supported between instances of 'Student' and 'Student'
# print(stu1 > stu2) # TypeError: '>' not supported between instances of 'Student' and 'Student'

# 有__lt__方法后便可以直接进行比较
print(stu1 < stu2) # True  (符合31 < 36 是正确的结果)
print(stu1 > stu2) # False (符合31 > 36 是错误的结果)     


### 示例3 __le__比较判断方法（与__lt__类似，只是可以多进行小于等于和大于等于的判断）
print("--------------------- 示例3 -------------------------")
print(stu1 <= stu2) # True  (符合31 <= 36 是正确的结果)
print(stu1 >= stu2) # False (符合31 >= 36 是错误的结果)   


### 示例4 __eq__相等判断方法
print("--------------------- 示例4 -------------------------")
# 没有__eq__方法直接对两个对象进行相等判断并不会报错，因为判断的是两个对象的内存地址是否一致
# print(stu1 == stu2) # False（因为两个独立的对象内存地址肯定不同，所以是False）

# 有__eq__方法后便可以直接进行比较
print(stu1 == stu2) # False  (符合31 ≠ 36 是正确的结果)
print(stu2 == stu3) # True  (符合36 = 36 是正确的结果)
 