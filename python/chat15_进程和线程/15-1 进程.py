"""
一、程序：是指一系列有序指令(代码)的集合，使用编程语言所编写，用于实现一定的功能。

二、进程：
    1.定义：一个程序运行在系统之上，那么便称之这个程序为一个运行进程，并分配进程ID方便系统管理。
            进程就好比一家公司，是操作系统对程序进行运行管理的单位。

    2.多任务执行：操作系统中可以运行多个进程，即多任务运行。

    3.内存特点：进程之间是内存隔离的，即不同的进程拥有各自的内存空间。这就类似于不同的公司拥有不同
                的办公场所。

    4.并行执行：多个进程同时在运行，即不同的程序同时运行，称之为：多任务并行执行。

三、创建子进程方式：
    1.方式一：
        # 导入Process模块
        from multiprocessing import Process

        # 构建某一个子进程process_obj
        process_obj = Process(group, target, name, args, kwargs)
            # group: 暂时无用，未来功能的预留参数。
            # target: 子进程要执行的任务名(执行任务一般是包装成函数，然后传入函数名)。
            # name: 子进程名，一般不用设置。
            # args: 对位置参数以元组的形式给执行任务传参，其中元组中元素的位置与位置参数保持一致。
            # kwargs: 对关键字参数以字典方式给执行任务传参。

        # 启动子进程process_obj，让子进程开始工作
        process_obj.start()  
"""
### 示例 创建子进程
print("--------------------- 示例 -------------------------")
import os, time
from multiprocessing import Process

def test():
    print(f"我是子进程，我的PIP是：{os.getpid()}，我的父进程是：{os.getppid()}") 
    time.sleep(5)

if __name__ == '__main__':
    print('主进程开始执行')
    lst = []

    # 创建五个子进程
    for i in range(5):
        # 创建子进程
        p = Process(target=test)
        # 启动子进程
        p.start()
        # 启动中的进程添加到列表中
        lst.append(p)

    print('主进程执行结束')


