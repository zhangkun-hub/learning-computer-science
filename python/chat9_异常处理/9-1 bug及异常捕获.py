"""
一、Bug(异常)：指程序运行的过程中出现了错误。

二、思路不清导致的Bug的解决方案：
    1.使用print()函数来打印不清楚的地方来进行判断；
    2.使用“#”暂时注释掉部分代码。

三、异常捕获：真实工作中不可能因为小bug就让整个程序停止运行，那么就需要下面的异常捕获操作
1.try...except语法结构：
    try:
        可能会抛出异常的代码
    except 异常类型A:    # 异常类型会在解释器的终端显示(常见异常类型见9-2)
        异常处理代码（报错后执行的代码）
    except 异常类型B:
        异常处理代码（报错后执行的代码）
    ...
    except Exception:        # 是包含所有通常的异常类型，但不包含系统级异常
        异常处理代码（报错后执行的代码）
    except BaseException:    # 最大的一个异常类型(包含所有异常)，放在最后(可写可不写)
        异常处理代码（报错后执行的代码）
    else:               
        没有抛出任何异常则执行的代码
    finally:            # 这个可写可不写(根据是否需要判断)
        无论是否产生异常都要执行的代码

    注意：
        (1)捕获异常的顺序：先子类后父类(所以建议越子类的异常放在越前面)，可见9-2的异常类型继承树。
        (2)捕获多个异常还可以用元组形式去写，即
                except (异常类型A, 异常类型B,...):

2. 捕获异常类型并赋值获取异常：
    try:
        可能会抛出异常的代码
    except 异常类型A as e:    # as e：将异常对象赋值给变量e(也可以是其他)，方便获取异常信息
        print(f"捕获到异常类型A: {e}")
    except 异常类型B as e:
        print(f"捕获到异常类型B: {e}")
    ...
    之后与1都一样

    注：捕获多个异常并赋值获取异常还可以用元组形式去写，即
                except (异常类型A, 异常类型B,...) as e:

"""
### 示例1 try...except结构的使用
print("--------------------- 示例1 -------------------------")
try:
    num1 = int(input('请输入一个整数：'))
    num2 = int(input('请输入另一个整数：'))
    result = num1 / num2

except ZeroDivisionError: 
    print('除数为0')

except ValueError:
    print('不能将字符串转成整数')

except BaseException:   # 最大的一个异常类型
    print('未知异常')

else:
    print('结果：',result)

finally:
    print('程序执行结束！')


### 示例2 捕获异常类型并赋值获取异常
print("--------------------- 示例2 -------------------------")
try:
    num1 = int(input('请输入一个整数：'))
    num2 = int(input('请输入另一个整数：'))
    result = num1 / num2

except ZeroDivisionError as e:   
    print(f"捕获到除零错误: {e}")  # 捕获到除零错误: division by zero

except ValueError as e: 
    print(f"捕获到将字符串转成整数错误: {e}") 
    # 捕获到将字符串转成整数错误: invalid literal for int() with base 10: 'a'

except BaseException: 
    print('未知异常')

else:
    print('结果：',result)

finally:
    print('程序执行结束！')