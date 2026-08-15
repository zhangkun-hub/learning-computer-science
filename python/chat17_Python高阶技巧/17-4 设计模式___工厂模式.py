"""
工厂模式：
    1.使用场景：当需要大量创建一个类的实例对象的时候，可以使用工厂模式。

    2.方式：从原生的使用类的构造去创建对象的形式，比如str_tool = StrTools()，迁移到基于工厂类提供
            的方法去创建对象的形式。(具体见下面示例)

    3.优点：
        (1)大批量创建对象的时候有统一的入口，易于代码维护。
        (2)当发生修改，仅修改工厂类的创建方法即可。
        (3)符合现实世界的模式，即由工厂来制作产品(产品对应类的对象)
"""
### 示例 工厂模式
print("--------------------- 示例 -------------------------")
## 创建Person类及其各种子类
class Person:
    pass

class Worker(Person):
    pass

class Student(Person):
    pass

class Teacher(Person):
    pass

## 创建工厂类
class PersonFactory:
    def get_person(self, p_type):
        if p_type == 'w':
            return Worker()
        elif p_type == 's':
            return Student()
        else:
            return Teacher()
        
## 创建工厂类的实例对象
pf = PersonFactory()

## 通过工厂模式获取各种类对象（特点：都是通过方法get_person获取类对象，非常统一，修改维护简便）
worker = pf.get_person('w')
stu = pf.get_person('s')
teacher = pf.get_person('t')