"""
一、类型注解：在代码中涉及数据交互的地方，提供数据类型的注解（显式的说明）

    1.主要功能：
        (1)帮助第三方IDE工具（如PyCharm）对代码进行类型推断，协助做代码提示；
        (2)帮助开发者自身对变量进行类型注释。

    2.支持的情形：
        (1)变量的类型注解；
        (2)函数（方法）形参列表和返回值的类型注解。

二、变量的类型注解：(注意：注解的类型与实际赋值不一致并不导致代码的错误和影响程序的运行)
    1.基础语法：变量: 类型
        例如：var: int = 10  
    
    2.类对象的类型注解格式：按照基础语法去写(以下举例说明)
        class Student:
            pass
        stu: Student = Student()   # 其中对象stu的类型为：Student类

    3.序列的类型注解格式：按照基础语法去写(以下举例说明)
        (1)简易格式：
            my_list: list = [1,2,3]
            my_tuple: tuple = (1,2,3)
            my_set: set = {1,2,3}
            my_dict: dict = {"itheima": 666}
            my_str: str = "itheima"
        
        (2)更详细的格式：
            my_list: list[int] = [1,2,3]
            my_tuple: tuple[str, int, bool] = ("itheima", 666, True)
            my_set: set[int] = {1,2,3}
            my_dict: dict[str, int] = {"itheima": 666}

            注意:(a)元组类型设置类型详细注解，需要将每一个元素都标记出来；
                (b)字典类型设置类型详细注解，需要2个类型，第一个是key，第二个是value。

三、函数/方法的类型注解：
        def 函数/方法名(形参1: 类型, 形参2: 类型,...) -> 返回值类型:
            函数体
            return 返回值

四、Union联合类型注解(即混合的类型的注解方式)：
    通过模块typing中的包Union，使用Union[类型1,类型2,...]，便可实现混合类型的注解。具体实例如下：
        # 导入模块typing中的包Union
        from typing import Union

        # 建立要么有str类型，要么有int类型的列表
        my_list: list[Union[str, int]] = [1, 2, "itheima", "itcast"]

        # 建立key是str类型，value是要么有str类型，要么有int类型的字典
        my_dict: dict[str, Union[str, int]] = {"name": "周杰伦", "age": 31}

        # 建立具有混合类型的形参和返回值的函数
        def func(data: Union[int, str]) -> Union[int, str]:
            pass        
"""
### 示例1 变量的类型注解
print("--------------------- 示例1 -------------------------")
# 基础数据类型注解
var_1: int = 10
var_2: str = "itheima"
var_3: bool = True

# 类对象类型注解
class Student:
    pass
stu: Student = Student()

# 序列的注解
my_list: list = [1,2,3]
my_tuple: tuple = (1,2,3)
my_set: set = {1,2,3}
my_dict: dict = {"itheima": 666}
my_str: str = "itheima"

# 序列的详细注解
my_list2: list[int] = [1,2,3]
my_tuple2: tuple[str, int, bool] = ("itheima", 666, True)
my_set2: set[int] = {1,2,3}
my_dict2: dict[str, int] = {"itheima": 666} 


### 示例2 函数/方法的类型注解
print("--------------------- 示例2 -------------------------")
def add(x: int, y: int) -> int:
    return x + y
c = add(1, 2)
print(c)


### 示例3 Union联合类型注解
print("--------------------- 示例3 -------------------------")
from typing import Union

# 建立要么有str类型，要么有int类型的列表
my_list: list[Union[str, int]] = [1, 2, "itheima", "itcast"]

# 建立key是str类型，value是要么有str类型，要么有int类型的字典
my_dict: dict[str, Union[str, int]] = {"name": "周杰伦", "age": 31}

# 函数的形参和返回值的混合类型注解
def func(data: Union[int, str]) -> Union[int, str]:
    pass


