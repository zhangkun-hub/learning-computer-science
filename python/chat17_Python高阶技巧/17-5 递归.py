"""
递归：
一、定义：函数(方法)自己调用自己的一种特殊编程写法。
    例如：
        def func():
            if ...:
                func()
            return ...

        
二、使用场景：最典型的递归场景就是找出一个文件夹中的全部文件。


三、注意事项：
    1.注意递归退出的条件，否则容易变成无限递归。
    2.注意返回值的传递，确保从最内层，层层传递到最外层。

    
四、os模块的3个方法(在找文件列出所有文件中非常有用)
    1. os.listdir(path)：列出path路径下的文件夹里的所有目录，以列表形式呈现。

    2. os.path.isdir(path)：判断path路径是否是一个文件夹，是则返回True。

    3. os.path.exists(path)：判断path路径是否存在，存在则返回True。
"""
### 示例1 os模块的使用
print("--------------------- 示例1 -------------------------")
import os

# listdir方法：列出参数路径下的文件夹里的所有目录，以列表形式呈现
print(os.listdir("./test"))  # ['1.txt', '2.txt', '3.txt', 'a', 'b']

# path.isdir方法：判断给的路径是否是一个文件夹
print(os.path.isdir("./test/a"))  # True

# path.exists方法：判断给的路径是否存在
print(os.path.exists("./test"))  # True



### 示例2 对test文件夹找出所有文件
print("--------------------- 示例2 -------------------------")
### 定义找出所有文件的函数
def get_files_recursion_from_dir(path):
    """
    从指定的文件夹中使用递归的方式，获取全部的文件列表
    
    :param path: 被判断的文件夹
    :return file_list: list，包含的全部文件，如果目录不存在或者无文件则返回一个空list
    """
    file_list = []

    ## 判断给的路径path是否存在
    print(f"当前判断的文件夹是：{path}")
    if os.path.exists(path):

        ## 通过for循环，遍历路径path下的文件夹里的所有目录
        for f in os.listdir(path):
            new_path = path + "/" + f  # 目录new_path的完整路径

            ## 判断new_path路径下的目录是否是一个文件夹
            if os.path.isdir(new_path):
                # new_path是文件夹，则用递归找寻该文件夹下的内容
                file_list += get_files_recursion_from_dir(new_path)
            else:
                file_list.append(new_path)

    else:
        print(f"指定的目录{path}不存在")
        return []
    
    return file_list


if __name__ == '__main__':
    print(get_files_recursion_from_dir("./test")) # 相对chat17文件夹下的相对路径
# 输出结果：
# 当前判断的文件夹是：./test
# 当前判断的文件夹是：./test/a
# 当前判断的文件夹是：./test/a/d
# 当前判断的文件夹是：./test/a/d/e
# 当前判断的文件夹是：./test/b
# 当前判断的文件夹是：./test/b/c
# ['./test/1.txt', './test/2.txt', './test/3.txt', './test/a/a1.txt', './test/a/a2.txt',
#  './test/a/a3.txt', './test/a/d/e/e1.txt', './test/a/d/e/e2.txt', './test/a/d/e/e3.txt', 
# './test/b/b1.txt', './test/b/b2.txt', './test/b/b3.txt', './test/b/c/c1.txt', 
# './test/b/c/c2.txt', './test/b/c/c3.txt']

