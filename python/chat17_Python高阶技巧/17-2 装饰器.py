"""
装饰器：
一、特性：装饰器是一个可调用对象，它接受一个函数作为参数，并返回一个新的函数，用于增强或修改原函数
        的行为而不改变其源代码。装饰器本质上是闭包 + 语法糖。

二、基本语法：(具体应用见实战1)
    # 1.定义装饰器函数decorator
    def decorator(func):   # 接收一个函数

        # 包装函数，并接受任意数量的位置参数(*args)和任意数量的关键字参数(**kwargs)，自由性更强
        def wrapper(*args, **kwargs):  
            前置处理代码内容
            result = func(*args, **kwargs)  # 调用原函数，并将参数(*args, **kwargs)原样传给它
            后置处理代码内容
            return result
        return wrapper

    # 2.使用装饰器装饰函数my_function
    @decorator
    def my_function():
        pass
        
    # 3.调用被装饰器装饰的函数my_function
    result = my_function()
    
    注意：
        (1)装饰器@decorator等价于定义my_function函数后，执行wrapper = decorator(my_function)。
            也就是说，用decorator返回的wrapper函数来包装(或替换)紧随其后的my_function函数。
            
        (2)当调用my_function()函数时，实际执行的是wrapper函数。

        (3)由于实际执行的是wrapper函数，所以如果要保留原函数my_function的元信息(如函数名、文档字
            符串等)，可以导入：from functools import wraps，并在第9行加上@wraps(func)，这表示：
            将内部函数wrapper的元信息（如__name__、__doc__）设置为与原始函数func相同。

            
三、作用：
    1.功能增强：在不改变原函数代码的情况下添加功能。
    2.代码复用：将通用功能封装为装饰器，让多个函数使用相同的附加功能（如日志、计时、权限检查）。
    3.遵循开放封闭原则(闭包功能)：对扩展开放，对修改封闭
    4.AOP（面向切面编程）：将横切关注点与业务逻辑分离。
    5.函数注册：将函数注册到某些系统（如路由、信号处理）。
    6.输入验证：检查函数参数的合法性。
    7.性能监控：测量函数执行时间、调用次数。
    8.权限控制：检查用户是否有权执行函数。
    9.日志记录：记录函数调用信息
"""
### 示例1 装饰器简单例子
print("--------------------- 示例1 -------------------------")
### 装饰器函数outer，它接受一个参数func(func就是将来被@outer装饰的那个函数)
def outer(func):
    def inner():
        print("我要睡觉了")
        func()
        print("我起床了")

    return inner

### 使用装饰器装饰函数sleep
@outer
def sleep():
    import random
    import time
    print("睡眠中......")
    time.sleep(random.randint(1, 5))

### 调用被装饰的函数sleep
sleep()
# 注：如果没有@outer，则按照闭包需要调用代码如下所示：
# fn = outer(sleep)
# fn()


