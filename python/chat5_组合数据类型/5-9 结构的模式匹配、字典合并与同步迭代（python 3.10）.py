"""
一、结构的模式匹配：针对整个数据结构进行匹配
语法结构：
match data:
    case{}:       # 字典/集合
        pass
    case[]:       # 列表
        pass
    case():       # 元组
        pass
    case_:        # 其余情况
        pass

二、字典合并运算符：|
    作用：将多个字典进行合并。

三、同步迭代：
语法结构：
match data1,data2:
    case data1,data2:
        pass
"""

### 示例1 结构的模式匹配
print("--------------------- 示例1 -------------------------")
data=eval(input('请输入要匹配的数据：'))
match data:
    case {'name':'zk','age':20}:
        print('字典')
    case[10,20,30]:
        print('列表')
    case(10,20,40):
        print('元组')
    case _:
        print('相当于多重if中的else')


### 示例2 合并字典运算符
print("--------------------- 示例2 -------------------------")
d1={'a':10,'b':20}
d2={'c':30,'d':40,'e':50}
merged_dict=d1|d2
print(merged_dict)


### 示例3 同步迭代
print("--------------------- 示例3 -------------------------")
fruits={'apple','orange','pear','grape'} # 集合是无序的
counts=[10,3,4,5] # 列表是有序的
for f,c in zip(fruits,counts): # 将集合fruits和列表counts进行压缩得到f和c
    match f,c:
        case 'apple',10:
            print('10个苹果')
        case 'orange',3:
            print('3个桔子')
        case 'pear',4:
            print('4个梨')
        case 'grape',5:
            print('5串葡萄')

print('-'*20)
fruits=['apple','orange','pear','grape'] # 列表是有序的
counts=[10,3,4,5] # 列表是有序的
for f,c in zip(fruits,counts): # 将集合fruits和列表counts进行压缩得到f和c
    match f,c:
        case 'apple',10:
            print('10个苹果')
        case 'orange',3:
            print('3个桔子')
        case 'pear',4:
            print('4个梨')
        case 'grape',5:
            print('5串葡萄')
