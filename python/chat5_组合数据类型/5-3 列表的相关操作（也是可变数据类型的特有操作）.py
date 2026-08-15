"""
一、可变数据类型的特有操作：增、删、改、查。

二、有序序列的特有操作：排序
    1.sorted()函数：
        (1)语法：新序列 = sorted(有序序列, key=指定排序规则的函数, reverse)

        (2)参数：
            (a)key: 是要求传入一个函数，表示将序列的每一个元素都传入函数中，从而返回新序列，
                    然后将新序列按降序/升序排序，而新序列与原序列元素一一对应，从而将原序列排序。
            (b)reverse(默认值为False): True表示对新序列降序排序，False表示对新序列升序排序。

        (3)注意：sorted可以接受任何可迭代对象，会产生新序列对象。

    2.sort()函数：
        (1)语法：有序序列.sort(key=指定排序规则的函数, reverse)

        (2)参数：
            (a)key: 是要求传入一个函数，表示将序列的每一个元素都传入函数中，从而返回新序列，
                    然后将新序列按降序/升序排序，而新序列与原序列元素一一对应，从而将原序列排序。
            (b)reverse(默认值为False): True表示对新序列降序排序，False表示对新序列升序排序。

        (3)注意：sort只能接受列表对象，不会产生新序列对象。

"""
### 示例1 列表元素的增加、删除与修改
print("--------------------- 示例1 -------------------------")
lst=['hello','world','python']
print('原列表：',lst,id(lst)) # id函数为输出lst的内存地址
# 增加元素操作
lst.append('sql')
print('增加元素之后：',lst,id(lst))

# 使用instert(index,x)表示在由index所指定的位置上插入元素x
lst.insert(1,100)
print(lst)

# 列表元素删除操作
lst.remove('world')
print('删除元素后的列表：',lst,id(lst))

# 使用pop(index)根据索引将元素取出，然后再删除
print(lst.pop(1))
print(lst)

# 列表元素的修改操作
lst[1]='mysql'
print(lst)


### 示例2 清除列表中所有的元素
print("--------------------- 示例2 -------------------------")
# 清除列表中所有的元素clear()
#lst.clear()
#print(lst,id(lst))


### 示例3 列表的反向、拷贝
print("--------------------- 示例3 -------------------------")
# 列表的反向
lst.reverse() # 不会产生新的列表，在原列表的基础上进行
print(lst)

# 列表的拷贝,将产生一个新的列表对象
new_lst=lst.copy()
print(lst,id(lst))
print(new_lst,id(new_lst))


### 示例4 列表排序sorted
print("--------------------- 示例4 -------------------------")
lst=[4,56,3,78,40,56,89]
print('原列表：',lst)
# 升序排列
asc_lst=sorted(lst)
print('升序：',asc_lst)
print('原列表：',lst)
#降序
desc_lst=sorted(lst,reverse=True)
print('降序：',desc_lst)
print('原列表：',lst)
#注意reverse()函数的一些情形
lst3=[1,3,5,7,9]
print(lst3)
lst1=lst3.reverse()
print(lst3)
print(lst1)

print('-'*20)
lst2=['banana','apple','Cat','Orange']
print('原列表：',lst2)
# 忽略大小写进行排序
new_lst2=sorted(lst2,key=str.lower)
print('原列表：',lst2)
print('排序后的列表：',new_lst2)


### 示例5 列表的排序sort
print("--------------------- 示例5 -------------------------")
lst=[4,56,3,78,40,56,89]
print('原列表：',lst)
# 排序，默认是升序
lst.sort() # 排序是在原列表基础上进行的，不会产生新的列表对象
print('升序：',lst)
# 降序
lst.sort(reverse=True)
print('降序：',lst)
print('-'*20)

### 通过ASCII码进行排序
## 升序排序，先排大写，再排小写(因为大写的ASCII码值比小写的要小32)
lst2=['banana','apple','Cat','Orange']
lst2.sort()
print('升序：',lst2)  # ['Cat', 'Orange', 'apple', 'banana']
#降序
lst2.sort(reverse=True)
print('降序：',lst2)  # ['banana', 'apple', 'Orange', 'Cat']
# 忽略大小写比较
lst2.sort(key=str.lower) # str.lower表示将字符串都转成小写的函数方法
print(lst2)          # ['apple', 'banana', 'Cat', 'Orange']


### 示例6 按照自己规则进行排序
print("--------------------- 示例6 -------------------------")
### 如下嵌套列表，要求对外层列表进行降序排序，排序的依据是内层列表的第二个元素数字
my_list = [["a", 33], ["b", 55], ["c", 11]]

### 方式1————依据带名函数排序
# # 定义排序方法
# def choose_sort_key(element):
#     return element[1]

# my_list.sort(key=choose_sort_key, reverse=True)
# print(my_list)         # [['b', 55], ['a', 33], ['c', 11]]


### 方式2————依据lambda匿名函数排序
new_list = sorted(my_list, key=lambda element: element[1]) 
print(new_list)          # [['c', 11], ['a', 33], ['b', 55]]

my_list.sort(key=lambda element: element[1], reverse=True)
print(my_list)           # [['b', 55], ['a', 33], ['c', 11]]


