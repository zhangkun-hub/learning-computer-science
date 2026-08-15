"""
一、线程：
    1.定义：线程是归属于进程的，一个进程可以开启多个线程执行不同的工作，是进程实际工作的最小单位。
            线程就好比公司的员工，进程可以有多个线程（员工），是进程实际的工作者。

    2.多线程运行：一个进程内可以运行多个线程，即多线程运行。

    3.内存特点：线程之间是内存共享的，线程是属于进程的，一个进程内的多个线程之间是共享这个进程所
                拥有的内存空间的。这就好比，公司员工之间是共享公司的办公场所的。

    4.并行执行：一个进程内的多个线程同时在运行，称之为：多线程并行执行。

二、多线程编程：通过threading模块来实现，语法如下：
    # 导入theading模块
    import threading

    # 构建某一个线程thread_obj(构建多个线程就是多线程运行)
    thread_obj = threading.Thread(group, target, name, args, kwargs)
        # group: 暂时无用，未来功能的预留参数。
        # target: 执行的目标任务名(执行任务一般是包装成函数，然后传入函数名)。
        # args: 对位置参数以元组的形式给执行任务传参，其中元组中元素的位置与位置参数保持一致。
        # kwargs: 对关键字参数以字典方式给执行任务传参。
        # name: 线程名，一般不用设置。

    # 启动线程thread_obj，让线程开始工作
    thread_obj.start()  

"""
### 示例 多线程编程
print("--------------------- 示例 -------------------------")
import time
import threading

def sing(msg):
    for i in range(10):
        print(msg)
        time.sleep(1)

def dance(msg):
    for i in range(10):
        print(msg)
        time.sleep(1)


if __name__ == '__main__':
    # 创建一个唱歌的线程
    sing_thread = threading.Thread(target=sing, args=("我要唱歌",))

    # 创建一个跳舞的线程
    dance_thread = threading.Thread(target=dance, kwargs={"msg": "我在跳舞"})

    # 让线程去干活
    sing_thread.start()
    dance_thread.start()