"""
一、字符串的拼接：
    1.使用 + 或 str.join() 进行拼接，join方法的介绍具体见6-2
    2.直接拼接
    3.使用格式化字符串进行拼接

二、字符串的去重操作：
    1.通过for遍历字符串循环与if判断来去重；
    2.使用集合来去重 + 列表排序 + join方法拼接
"""
### 示例1 字符串的拼接
print("--------------------- 示例1 -------------------------")
s1 = 'hello'
s2 = 'world'
# 使用 + 拼接
print(s1 + s2) 
# 使用join方法进行拼接
print(''.join([s1,s2])) 
print('*'.join(['hello','world','python','java','php']))
print('你好'.join(['hello','world','python','java','php']))
print()

# 直接拼接
print('hello''world')
print()

# 使用格式化字符串进行拼接
print('%s%s' %(s1,s2))
print(f'{s1}{s2}')
print('{0}{1}'.format(s1, s2))


### 示例2 字符串的去重
print("--------------------- 示例2 -------------------------")
s = 'helloworldhelloworldadfdfdeoodllffe'
new_s = ''
for item in s:
    if item not in new_s:
        new_s += item # 拼接操作
print(new_s)

# 使用索引
new_s2 = ''
for i in range(len(s)):
    if s[i] not in new_s2:
        new_s2 += s[i]
print(new_s2)
print()

# 使用集合来去重 + 列表排序 + join方法拼接
new_s3 = set(s)
lst = list(new_s3)
print(lst) # 因为集合的无序性使得去重的字符串其顺序也被打乱
lst.sort(key=s.index) # 指定列表的排序key按照s.index去排序
# s.index：这是字符串/列表/元组的index()方法，返回列表lst的元素在s中第一次出现的索引位置
print(''.join(lst))