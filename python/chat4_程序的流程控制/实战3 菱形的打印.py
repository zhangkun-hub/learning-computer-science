print('-'*30) # 菱形
print('菱形')
# 先判断输入的行数，因为菱形的行数必须为奇数
row=eval(input('请输入菱形的行数(必须奇数)：'))
while row%2==0: # 判断行数的奇偶性，行数是偶数，则重新输入行数
    print('重新输入菱形的行数')
    row=eval(input('请输入菱形的行数：'))
# 输出菱形的上半部分
top_row=(row+1)//2 # 上半部分行数
for i in range(1,top_row+1): # 行循环
    for j in range(1,top_row+1-i): # 空格的倒三角形的列循环
        print(' ',end='')
    for k in range(1,i*2): # *的等腰三角形的列循环
        print('*',end='')
    print() # 当两个并列的for循环执行完毕后，再换行
# 下半部分
bottom_row=row//2 # 下半部分行数
for i in range(1,bottom_row+1): # 行循环
    for j in range(1,i+1): # 空格的直角三角形的列循环
        print(' ',end='')
    for k in range(1,bottom_row*2-2*i+2): # *的倒等腰三角形的列循环
        print('*',end='')
    print() # 当两个并列的for循环执行完毕后，再换行


print('-'*30) # 空心菱形
print('空心菱形')
# 先判断输入的行数，因为菱形的行数必须为奇数
row=eval(input('请输入菱形的行数(必须奇数)：'))
while row%2==0: # 判断行数的奇偶性，行数是偶数，则重新输入行数
    print('重新输入菱形的行数')
    row=eval(input('请输入菱形的行数：'))
# 输出菱形的上半部分
top_row=(row+1)//2 # 上半部分行数
for i in range(1,top_row+1): # 行循环
    for j in range(1,top_row+1-i): # 空格的倒三角形的列循环
        print(' ',end='')
    for k in range(1,i*2): # *的等腰三角形的列循环
        if k==1 or k==i*2-1:
            print('*',end='')
        else:
            print(' ',end='')
    print() # 当两个并列的for循环执行完毕后，再换行
# 下半部分
bottom_row=row//2 # 下半部分行数
for i in range(1,bottom_row+1): # 行循环
    for j in range(1,i+1): # 空格的直角三角形的列循环
        print(' ',end='')
    for k in range(1,bottom_row*2-2*i+2): # *的倒等腰三角形的列循环
        if k==1 or k==bottom_row*2-2*i+1:
            print('*',end='')
        else:
            print(' ',end='')
    print() # 当两个并列的for循环执行完毕后，再换行

