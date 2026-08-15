# 猜数游戏，具体见P41
import random # random为产生随机数
rand=random.randint(1,100) # 产生1-100之间的随机数
count=1 # 记录猜数的次数
while count<=10:
    number=eval(input('在我心中有个数，，1-100之间，请你猜一猜(10次机会)：'))
    if number==rand:
        break
    elif number>rand:
        print('大了')
    else:
        print('小了')
    count+=1 # 每猜一次count次数要加1
if count<=3:
    print('真聪明，一共猜了',count,'次')
elif count<=6:
    print('还可以，一共猜了',count,'次')
elif count<=10:
    print('猜的次数有点多啊，一共猜了',count,'次')
else:
    print('10次机会用完，1分钟后再尝试')

