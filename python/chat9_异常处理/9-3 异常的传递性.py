"""
异常具有传递性：
        比如当函数func1中发生异常，并且没有捕获处理这个异常。当第二个函数func2调用函数func1时，
    异常会传递到第二个函数func2。当func2函数也没有捕获处理这个异常，并且第三个函数main调用第二个
    函数func2时，该异常就会传递到第三个函数main。假设他通过try捕获了这个异常，则第一个函数的异常
    就传递到第三个函数捕获。如果最终都没有捕获，则在终端抛出异常，这就是异常的传递性。
    (见下面示例所示)
"""
# 定义一个出现异常的方法
def func1():
    print("func1 开始执行")
    num = 1 / 0   # 除0异常
    print("func1 结束执行")

# 定义一个无异常的方法，调用上面的方法
def func2():
    print("func2 开始执行")
    func1()
    print("func2 结束执行")

# 定义一个方法，调用上面的方法
def main():
    try:
        func2()
    except Exception as e:
        print(f"出现异常了，异常的信息是: {e}")

# 执行main函数
main()
"""
上面程序的终端执行结果如下：
    func2 开始执行
    func1 开始执行
    出现异常了，异常的信息是: division by zero

可以看到没有执行“func1 结束执行”和“func2 结束执行”，这是因为异常导致函数func1和func2停止执行了。
"""
