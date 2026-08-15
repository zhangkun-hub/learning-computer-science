### 自定义模块my_module2

# 通过from my_module2 import *时只能调用test功能
__all__ = ['test']

# 定义两数相减的功能
def test(a, b):
    print(a - b)

# 定义两数相乘的功能
def testB(a, b):
    print(a * b)

