"""
一、python包：
    1.来源：如果python的模块太多了，就可能造成混乱，此时需要通过python包的功能来管理。

    2.定义：包就是一个文件夹，里面有多个模块文件（于是包本质还是模块），但文件夹下必须包含一个
            __init__.py文件，称为初始化文件(可以是空文件，但必须要有该文件)。

    3.__init__.py文件：称为初始化文件，其作用见下面第三部分的内容。
            
二、导入包中的模块并使用的方式：
    1.通过import语句导入：
        import 包名.模块名     # 注：可以只导入包这个层级，但意义不大，而包里的模块才是有用的文件
        包名.模块名.功能名

    2.通过from语句导入到模块层级：
        from 包名 import 模块名
        模块名.功能名

    3.通过from语句导入到功能层级：
        from 包名.模块名 import 功能名
        功能名

三、__all__列表在包中的使用(与模块中的使用内核是一致的)：
    1.使用方式：在__init__.py初始化文件中添加__all__列表，里面变量为模块名。
    
    2.作用：可以控制通过“from 包名 import *”所允许导入的模块列表。

四、第三方包（具体见下一节）
    1.python程序的生态中，有非常多的第三方包(非python官方)，不同包有不同功能，比如：
        (1)科学计算常用的：numpy包
        (2)数据分析常用的：pandas包
        (3)大数据计算常用的：pyspark、apache-flink包
        (4)图形可视化常用的：matplotlib、pyecharts包
        (5)人工智能常用的：tensorflow包

    2.第三方包的下载、删除与查询：(在python的命令提示符环境或anaconda的虚拟环境中通过以下命令操作)
        (1)国外网站下载(网速较慢，但最全面)：pip install 包名称

        (2)国内清华镜像网站下载(网速较快，但部分包没有)：
            pip install -i https://pypi.tuna.tsinghua.edu.cn/simple 包名称

        (3)删除：pip uninstall 包名称

        (4)查看已安装的所有包名：pip list

        (5)查看特定包的信息：pip show 包名

        扩展：进入虚拟环境的命令：conda activate 环境名称，
              退出虚拟环境的命令：conda deactivate

五、库：
    1.定义：通常指一个功能完备的、可以直接拿来解决特定问题的代码集合。
            即一个库可以是一个单独的模块，一个包，或者一个由多个包和模块组成的大型项目。
                注：在日常交流中，“包”和“库”经常被混用，比如numpy即可叫库也可叫包(但叫库更多)

    2.作用：提供一套标准化的解决方案，让你无需重复造轮子，直接在库的统一接口（API）运行。
        注：轮子比喻在软件开发中那些通用、基础、必须的功能。就像造汽车必须要有“轮子”这个组件一样。

            举例：发送一个HTTP请求，需要从传输层的socket开始写起，手动拼接HTTP协议头，处理编码、
        连接超时、重定向、SSL加密（HTTPS）等一系列极其复杂的底层细节。可能需要几百行代码，还漏洞
        百出。而“使用库”（不用造轮子）的做法：即安装一个成熟的库，比如requests库，这样行代码，你
        就完成了一个健壮的HTTP GET请求，所有底层复杂性都被库封装好了。
"""
### 自定义包my_package
# 里面含有初始化文件__init__.py，并且还有两个模块文件my_module1.py和my_module2.py

### 示例1 通过语法1方式导入模块并使用
print("--------------------- 示例1 -------------------------")
### 导入包中的模块
# import my_package.my_module1
# import my_package.my_module2

# ### 使用包中模块的功能
# my_package.my_module1.info_print1()     # 我是模块1的功能函数代码
# my_package.my_module2.info_print2()     # 我是模块2的功能函数代码


### 示例2 通过语法2方式导入模块并使用
print("--------------------- 示例2 -------------------------")
### 导入包中的模块
# from my_package import my_module1
# from my_package import my_module2

# ### 使用包中模块的功能
# my_module1.info_print1()     # 我是模块1的功能函数代码
# my_module2.info_print2()     # 我是模块2的功能函数代码


### 示例3 通过语法3方式导入模块并使用
print("--------------------- 示例3 -------------------------")
### 导入包中的模块
# from my_package.my_module1 import info_print1
# from my_package.my_module2 import info_print2

# ### 使用包中模块的功能
# info_print1()     # 我是模块1的功能函数代码
# info_print2()     # 我是模块2的功能函数代码


### 示例4 __all__列表在包中的使用
print("--------------------- 示例4 -------------------------")
from my_package import *
my_module1.info_print1()
# my_module2.info_print2()  # 因为__all__ = ['my_module1']，所以*中只能导入my_module1模块
