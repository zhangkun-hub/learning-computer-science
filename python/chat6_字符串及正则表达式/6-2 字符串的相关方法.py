"""
字符串的相关方法(其中字符串命名为str)：
    1.str.lower()：将str全部转成小写字母，结果为一个新的字符串；
    2.str.upper()：将str全部转成大写字母，结果为一个新的字符串；
    3.str.split(sep)：把str按照指定的分隔符sep进行分隔，结果为列表类型(分隔符不属于任何一个元素)；
    4.str.splitlines()：把字符串str按行进行分割，并用列表存储；
    5.str.count(sub)：查询sub这个子串在str中出现的次数；
    6.str.find(sub)：查询sub这个子s串在str中是否存在，如果不存在结果为-1，
                    如果存在，结果为sub首次出现的索引；
    7.str.index(sub)：功能与find()相同，区别在于要查询的子串sub不存在时，程序报错；
    8.str.startswith(s)：查询字符串str是否以子串s开头；
    9.str.endswith(s)：查询字符串str是否以子串s结尾。

    10.str.replace(old,news,n)：使用news替换字符串str中的前n个old字符串(不写n则默认全部替换)，
                            结果是一个新的字符串；
    11.str.center(width,fillchar)：字符串str在指定的宽度范围内居中，可以使用fillchar进行填充；
    12.str.join(iter)：在可迭代对象iter中的每个元素的后面都添加字符串str来进行连接，
                    从而成为一个字符串(可迭代对象包含要连接的元素的列表、元组、集合、字符串等)；

    # 注意：以下方法若不填参数chars，则默认去掉空格、制表符\t和换行符\n。
    13.str.strip(chars)：从字符串中去掉左侧和右侧chars中列出的字符串(与该字符串书写顺序无关)；
    14.str.lstrip(chars)：从字符串中去掉左侧chars中列出的字符串(与该字符串书写顺序无关)；
    15.str.rstrip(chars)：从字符串中去掉右侧chars中列出的字符串(与该字符串书写顺序无关)。
"""
### 示例1 字符串的相关处理方法1
print("--------------------- 示例1 -------------------------")
# 大小写转换
s1 = 'HelloWorld'
s2 = s1.lower()
s3 = s1.upper()
print(s1)
print(s2)
print(s3)
print()

# 字符串的分隔
e_mail = 'zk@126.com'
lst = e_mail.split('@')
print(lst[0]) # zk
print(lst[1]) # 126.com
print(f'邮箱名：{lst[0]}；邮件服务器域名：{lst[1]}') # 邮箱名：zk；邮件服务器域名：126.com
print()

# 子串在str中的操作
print(s1.count('o')) # o在字符串s1中出现了两次
print(s1.find('o')) # o在字符串s1中首次出现的位置索引为4
print(s1.find('p')) # -1,即没有找到
print(s1.index('o')) # 与find一样输出4
# print(s1.index('p'))    # 报错(与find区别)：ValueError: substring not found
print()

# 判断前缀和后缀
print(s1.startswith('H')) # True
print(s1.startswith('P')) # False
print('demo.py'.endswith('.py')) # True
print('text.txt'.endswith('.txt')) # True


### 示例2 字符串的相关处理方法2
print("--------------------- 示例2 -------------------------")
s = 'HelloWorld'

# 字符串的替换
new_s = s.replace('o', '你好', 1) # 最后一个参数1是只替换一个o(不写则默认替换全部o)
print(new_s)  # Hell你好World
print()

# center与join用法
print(s.center(20))
print(s.center(20, '*'))
my_list = ['a', 'b', 'c']
result = '-'.join(my_list)  # 用'-'作为连接符
print(result)  # 输出: a-b-c
print()

# 去掉字符串左右空格
s = '    Hello    World    '
print(s)
print(s.strip()) # 去掉两侧空格
print(s.lstrip()) # 去掉左侧空格
print(s.rstrip()) # 去掉右侧空格
print()

# 去掉指定的字符
s3 = 'dl-Helloworld'
print(s3.strip('ld')) # 去除的字符ld与书写顺序无关，即ld、dl都去除
print(s3.lstrip('ld'))
print(s3.rstrip('ld'))