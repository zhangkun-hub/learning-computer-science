"""
一、封装：将现实世界事物的属性行为封装到类中,描述为成员属性和成员方法,从而完成程序对现实世界的描述,
        但是，并不是所有属性行为都是公开的，需要对用户隐藏某些属性和行为，而公开部分属性和行为。
        即：对内隐藏细节，对外暴露接口，比如print()函数就是如此。
        
二、核心思想：隐藏对象的内部实现细节，只对外提供安全的访问接口。

三、作用：(封装是基础：没有封装，数据和实现都暴露在外，继承和多态无从谈起)
    1.保护数据安全;
    2.降低耦合度;
    3.易于维护和修改。
    
四、封装的三种级别：
    1.双下划线开头：表示私有的成员(具体见4和5)。

    2.单下划线开头：以单下划线开头的属性或方法表示受保护的成员，这类成员被视为仅供内部使用，
        允许类本身和子类进行访问，但实际上它可以被外部代码访问(只防君子不防小人);

    3.无下划线：公开的属性或方法，类的内部、外部及子类都可以访问。

    注意：首尾双下划线：一般表示特殊的方法，即魔术方法。

五、封装的最高级别———私有成员：分为私有成员属性和私有成员方法。
    1.形式：双下划线开头，比如：__a = 1。

    2.特点：类对象无法调用，只能被所属的该类内部的属性和方法调用(无论这些属性方法是否私有)。

    3.作用：强有效的保证数据的安全性。
    
六、对私有成员(即具有双下划线的私有属性/方法)的外部访问方式：
    1.对象名._类名__属性名/方法名    # 此方式非常不推荐

    2.使用修饰器@property，将方法转成属性使用(具体见示例2——属性的设置)
"""
### 示例1 私有成员的属性和方法(双下划线开头)
print("--------------------- 示例1 -------------------------")
# 定义一个类，内含私有成员变量和私有成员方法
class Phone:
    __current_voltage = 1  # 当前手机的运行电压

    def __keep_single_core(self):
        print("让CPU以单核模式运行")

    # 定义公开的成员方法来调用私有的成员属性__current_voltage和私有方法__keep_single_core()
    def call_by_5g(self):
        if self.__current_voltage >= 1:
            print("5g通话已开启")
        else:
            self.__keep_single_core()
            print("电量不足，无法使用5g通话，并已设置为单核运行进行省电。")

phone = Phone()

# 直接调用私有成员会出错
# phone.__keep_single_core()     # 出错，因为无法调用私有成员方法
# print(phone.__current_voltage) # 出错，因为无法调用私有成员属性

# 调用公开的成员方法call_by_5g，但里面含有调用私有成员属性和方法的内容
phone.call_by_5g()  # 调用成功





### 示例2 封装的权限控制
print("--------------------- 示例2 -------------------------")
class Student():
    # 首尾双下划线
    def __init__(self, name, age, gender):
        self._name = name    # 单下划线开头，受保护，只能本类和子类访问(但也可被外部访问)
        self.__age = age     # 双下划线开头，只能类本身去访问
        self.gender = gender # 普通的实例属性，类的内部、外部及子类都可以访问

    # 单下划线的方法
    def _fun1(self):
        print('子类及本身可以访问')

    # 双下划线的方法
    def __fun2(self):
        print('只有定义的类可以访问')

    # 无下划线，即普通的实例方法
    def show(self):
        self._fun1()  # 调用单下划线的方法
        self.__fun2() # 调用双下划线的方法
        print(self._name) # 调用单下划线的属性
        print(self.__age) # 调用双下划线的属性

# 创建一个学生类的对象
stu = Student('陈梅梅', 20, '女')

# 类的外部访问受保护的属性
print(stu._name)  # 子类及本身可以访问
# print(stu.__age)  # 错误AttributeError(因为双下划线受保护)

# 类的外部访问受保护的方法
stu._fun1() # 子类及本身可以访问
# stu.__fun2() # 错误AttributeError(因为双下划线受保护)

# 受保护的双下划线的访问
print(stu._Student__age)
stu._Student__fun2()


### 示例3 属性的设置
print("--------------------- 示例3 -------------------------")
class Student2():
    def __init__(self, name, gender):
        self.name = name    
        self.__gender = gender # 双下划线开头的私有实例属性

    # 使用@property修改方法，将方法转成属性使用
    @property
    def gender(self):
        return self.__gender
    
    # 将私有属性gender设置为可写属性(即可以进行修改)
    @gender.setter
    def gender(self, value):  # 因为该属性的值可以修改，则需要一个参数value传递该修改的值
        # 判断修改的值value是否非男非女
        if value != '男' and value != '女':
            print('性别有误，已将性别默认设置为男')
            self.__gender = '男'
        else:
            self.__gender = value
    
# 通过访问@property方法，从而可以访问私有属性self.__gender
stu = Student2('李明', '男')
print(f'{stu.name}的性别是：{stu.gender}') # 李明的性别是：男

# 对私有属性gender的值进行修改
stu.gender = '女'  
print(f'{stu.name}的性别是：{stu.gender}') # 李明的性别是：女
stu.gender = '其他'  # 性别有误，已将性别默认设置为男
print(f'{stu.name}的性别是：{stu.gender}') # 李明的性别是：男
