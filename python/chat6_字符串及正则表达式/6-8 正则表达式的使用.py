"""
正则表达式在python中的使用：re模块
    1.re.match(pattern,string,flags=0)：(其中pattern是匹配模式，string是要进行匹配的字符串)
        用于从字符串的开始位置进行匹配，如果起始位置匹配成功，结果为Match对象，否则为None；
    2.re.search(pattern,string,flags=0)：
        用于在整个字符串中搜索第一个匹配的值，如果匹配成功，结果为Match对象，否则为None；
    3.re.findall(pattern,string,flags=0)：
        用于在整个字符串中搜索所有符合正则表达式的值，结果是一个列表类型；
    4.re.sub(pattern,repl,string,count,flags=0)：(其中repl是指子串要替换成为的东西)
        用于实现对字符串中指定子串的替换；
    5.re.split(pattern,string,maxsplit,flags=0)：
        字符串中的split()方法功能相同，都是分隔字符串，输出为列表形式。
"""
import re # 导入re模块

# 示例1 match方法使用(其他方法见6-8节)
print("--------------------- 示例1 -------------------------")
pattern = r'\d\.\d+' # 要求匹配.左边的0-9数字出现1次，.右边的0-9数字出现1次或多次
s = 'I study Python 3.11 every day'

match = re.match(pattern, s, re.I) # re.I是忽略大小写
print(match) # None

s2 = '3.11Python I study every day'
match2 = re.match(pattern, s2)
print(match2) # <re.Match object; span=(0, 4), match='3.11'>
print()

print('匹配值的起始位置：', match2.start())
print('匹配值的结束位置：', match2.end())
print('匹配的区间位置：', match2.span())
print('待匹配的字符串：', match2.string)
print('匹配的数据：', match2.group())


# 示例2 search方法使用
print("--------------------- 示例2 -------------------------")
pattern1 = r'\d\.\d+' # 要求匹配.左边的0-9数字出现1次，.右边的0-9数字出现1次或多次
s3 = 'I study Python 3.11 every day Python2.7 I love you'
match3 = re.search(pattern1, s3) 
print(match3) # <re.Match object; span=(15, 19), match='3.11'>

s4 = '4.10 Python I study every day'
match4 = re.search(pattern1, s4) 
print(match4) # <re.Match object; span=(0, 4), match='4.10'>

s5 = 'I study Python every day'
match5 = re.match(pattern1, s5)
print(match5) # None

print()
print('匹配的数据：', match3.group())
print('匹配的数据：', match4.group())


# 示例3 findall方法使用
print("--------------------- 示例3 -------------------------")
pattern2 = r'\d\.\d+' # 要求匹配.左边的0-9数字出现1次，.右边的0-9数字出现1次或多次
s3 = 'I study Python 3.11 every day Python2.7 I love you'
s4 = '4.10 Python I study every day'
s5 = 'I study Python every day'

match3 = re.findall(pattern2, s3) 
match4 = re.findall(pattern2, s4) 
match5 = re.findall(pattern2, s5) 
print(match3) # ['3.11', '2.7']
print(match4) # ['4.10']
print(match5) # []


# 示例4 sub方法使用
print("--------------------- 示例4 -------------------------")
pattern3 = r'黑客|破解|反爬' # 用于匹配“黑客、破解、反爬”字眼的字符串
s = '我想学习Python，想破解一些VIP视频，Python可以实现无底线反爬吗？'
new_s = re.sub(pattern3, 'XXX', s)
print(new_s)  # 我想学习Python，想XXX一些VIP视频，Python可以实现无底线XXX吗？
print()


# 示例5 split方法使用
print("--------------------- 示例5 -------------------------")
s2 = 'https://www.baidu.com/s?wd=ysj&rsv_spt=1'
pattern4 = r'[?|&]' # 用于匹配?或&符号
lst = re.split(pattern4, s2) # split方法按照匹配模式pattern4对字符串s2进行分隔，输出列表形式
print(lst) # ['https://www.baidu.com/s', 'wd=ysj', 'rsv_spt=1']
