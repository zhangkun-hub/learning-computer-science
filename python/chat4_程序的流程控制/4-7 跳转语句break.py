"""
break：break用于跳出(退出)循环结构，通常与if一起搭配使用
"""
### 示例1 break在while循环中的使用
print("--------------------- 示例1 -------------------------")
s=0 # 存储累加和
i=1 # (1)初始化变量
while i<11: # (2)条件判断
    # (3)语句块
    s+=i
    if s>20:
        print('累加和大于20的当前数是：',i)
        break
    i+=1 # (4)改变变量

print('-'*20)
i=0 # 统计登录的次数
while i<3:
    user_name=input('请输入用户名：')
    pwd=input('请输入密码：')
    if user_name=='zk' and pwd=='888888':
        print('系统正在登录，请稍后...')
        break
    else:
        if i<2:
            print('用户名或密码不正确，您还有',2-i,'次机会')
    i+=1
else: # 如果执行break，便是提前退出循环，属于不正常循环操作，故不执行此处else后语句块
    print('三次均输入错误！')


### 示例2 break在for循环中的使用
print("--------------------- 示例2 -------------------------")
for i in 'hello':
    if i=='o':
        break
    print(i,end='')
print('')
print('-'*20)
for i in range(3): # range()函数，Python中的内置函数，产生一个[n,m)的整数序列，包含n,但不包含m,而range(n)表示从0到n-1循环n次
    user_name = input('请输入用户名：')
    pwd = input('请输入密码：')
    if user_name == 'zk' and pwd == '888888':
        print('系统正在登录，请稍后...')
        break
    else:
        if i < 2:
            print('用户名或密码不正确，您还有',2-i,'次机会')
else:  # 如果执行break，便是提前退出循环，属于不正常循环操作，故不执行此处else后语句块
    print('三次均输入错误！')