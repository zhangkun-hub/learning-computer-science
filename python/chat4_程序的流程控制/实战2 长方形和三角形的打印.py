# 三行四列长方形
print('三行四列长方形')
for i in range(1,4): # 外层循环行数
    for j in range(1,5): # 内层循环列数
        print('*',end='')
    print() # 空的print语句，作用是换行

print('-'*20) # 正直角三角形
print('正直角三角形')

for i in range(1,6): # 5行
    #  *的个数与行数相等，故内层循环中第一行为range(1,2),第二行为range(1,3)，第i行为range(1,i+1)
    for j in range(1,i+1):
        print('*',end='')
    print() # 空的print语句，换行作用


print('-'*20) # 倒三角形
print('倒三角形')
for i in range(1,6): # 外层循环共5行
    for j in range(1,7-i): # 内层循环列数，第i行为从1到6-i列
        print('*',end='')
    print() # 空的print语句，换行作用


print('-'*20) # 等腰三角形
print('等腰三角形')
for i in range(1,6): # 外层循环5行
    for j in range(1,6-i): # 空格的倒三角形列循环
        print(' ',end='')
    for k in range(1,i*2): # *的等腰三角形列循环
        print('*',end='')
    print() # 空的print语句，换行作用
