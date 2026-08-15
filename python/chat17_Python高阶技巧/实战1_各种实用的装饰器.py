### 示例1 计时装饰器（最常用）
print("--------------------- 示例2 -------------------------")
import time
from functools import wraps  
# wraps装饰器：在使用装饰器包装一个函数时，保留被包装函数(原函数)的元信息(如函数名、文档字符串等)

def timer(func):
    """计算函数执行时间的装饰器"""
    @wraps(func)  # 保留原函数元信息
    def wrapper(*args, **kwargs):
        start_time = time.time()  # time.time()表示获取当前时间
        result = func(*args, **kwargs) # 将所有参数(*args, **kwargs)原样传递给func函数
        end_time = time.time()
        print(f"{func.__name__} 执行时间: {end_time - start_time:.4f}秒")
        # func.__name__获取原始函数的名字（得益于@wraps(func)）

        return result
    return wrapper

@timer
def calculate_sum(n):
    """计算1到n的和"""
    return sum(range(1, n+1))

print(calculate_sum(1000000))  # 自动输出执行时间



### 示例2 日志装饰器
print("--------------------- 示例3 -------------------------")
from functools import wraps  

def logger(func):
    """记录函数调用的装饰器"""
    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"[日志] 开始调用: {func.__name__}")
        print(f"[日志] 参数: args={args}, kwargs={kwargs}")
        result = func(*args, **kwargs)
        print(f"[日志] 结束调用: {func.__name__}, 返回值: {result}")
        return result
    return wrapper

@logger
def add(a, b):
    return a + b

add(3, 5)  # 自动记录日志



### 示例3 权限验证装饰器
print("--------------------- 示例3 -------------------------")
def require_login(login_required=True):
    """检查用户是否登录的装饰器"""
    def decorator(func):
        def wrapper(user, *args, **kwargs):
            if login_required and not user.get('is_authenticated', False):
                print("错误：请先登录！")
                return None
            return func(user, *args, **kwargs)
        return wrapper
    return decorator

# 使用
@require_login(login_required=True)
def view_profile(user):
    print(f"欢迎，{user['name']}！查看个人资料...")

user1 = {'name': '张三', 'is_authenticated': True}
user2 = {'name': '李四', 'is_authenticated': False}

view_profile(user1)  # 正常访问
view_profile(user2)  # 提示需要登录



### 示例4 重试装饰器
print("--------------------- 示例4 -------------------------")
import time

def retry(max_attempts=3, delay=1):
    """失败重试的装饰器"""
    def decorator(func):
        def wrapper(*args, **kwargs):
            for attempt in range(1, max_attempts + 1):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    if attempt == max_attempts:
                        print(f"第{attempt}次尝试失败，不再重试: {e}")
                        raise
                    print(f"第{attempt}次尝试失败，{delay}秒后重试: {e}")
                    time.sleep(delay)
        return wrapper
    return decorator

@retry(max_attempts=3, delay=2)
def call_api(url):
    """模拟API调用，可能失败"""
    import random
    if random.random() < 0.7:  # 70%概率失败
        raise ConnectionError("API调用失败")
    return "API调用成功"



### 示例5 参数验证装饰器
print("--------------------- 示例5 -------------------------")
def validate_params(func):
    """验证函数参数的装饰器"""
    def wrapper(a, b):
        if not isinstance(a, (int, float)):
            raise TypeError(f"参数a必须是数字，实际是{type(a)}")
        if not isinstance(b, (int, float)):
            raise TypeError(f"参数b必须是数字，实际是{type(b)}")
        if b == 0:
            raise ValueError("除数b不能为0")
        return func(a, b)
    return wrapper

@validate_params
def divide(a, b):
    """除法运算"""
    return a / b



### 示例6 类装饰器
print("--------------------- 示例6 -------------------------")
class CountCalls:
    """记录函数调用次数的类装饰器"""
    def __init__(self, func):
        self.func = func
        self.count = 0
    
    def __call__(self, *args, **kwargs):
        self.count += 1
        print(f"{self.func.__name__} 已被调用 {self.count} 次")
        return self.func(*args, **kwargs)

@CountCalls
def say_hello():
    print("你好！")

say_hello()  # 输出：say_hello 已被调用 1 次
say_hello()  # 输出：say_hello 已被调用 2 次



### 示例8 装饰器链（叠加多个装饰器）
print("--------------------- 示例8 -------------------------")
@timer
@logger
@validate_params
def complex_operation(a, b):
    """复杂的计算操作"""
    return a * b / (a + b)

# 执行顺序：validate_params → logger → timer
# 等价于：complex_operation = timer(logger(validate_params(complex_operation)))



### 示例9 内置装饰器
print("--------------------- 示例9 -------------------------")
# 1. @staticmethod - 静态方法
class MyClass:
    @staticmethod
    def static_method():
        pass

# 2. @classmethod - 类方法
class MyClass:
    @classmethod
    def class_method(cls):
        pass

# 3. @property - 属性装饰器
class Person:
    def __init__(self, name):
        self._name = name
    
    @property
    def name(self):
        return self._name
    
    @name.setter
    def name(self, value):
        self._name = value

# 4. @functools.lru_cache - 缓存装饰器
from functools import lru_cache
@lru_cache(maxsize=32)
def expensive_function(x):
    pass