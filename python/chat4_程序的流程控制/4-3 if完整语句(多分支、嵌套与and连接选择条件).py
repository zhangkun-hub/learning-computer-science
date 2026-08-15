"""
一、if完整语句：
if 关系表达式1:
    语句体1
elif 关系表达式2:
    语句体2
elif 关系表达式3:
    语句体3
...
else:
    语句体n

二、执行流程:如果表达式1值为True则执行语句体1,否则判断表达式2是否为True,若也不为True,则判断下一个,
            即从上到下依次判断哪个关系表达式是否为True，为True的执行对应语句体，
            如果都为Fales，则执行else内容(若无else，则跳出if语句)。
"""

### 示例1 if...else结构(双分支结构)
print("--------------------- 示例1 -------------------------")
number=eval(input('请输入您的6位中奖号码：'))
if number==987654:
    print('恭喜您中奖了！')
else:
    print('您未中本期大奖！')

print('-----以上代码可以使用条件表达式进行简化------')
result='恭喜您中奖了！' if number==987654 else'您未中本期大奖！'
print(result)

print('恭喜您中奖了！' if number==987654 else'您未中本期大奖！')


### 示例2 多分支结构
print("--------------------- 示例2 -------------------------")
score=eval(input('请输入您的成绩：'))
if score<0 or score>100:
    print('成绩有误！')
elif 0<=score<60:
    print('E')
elif 60<=score<70:
    print('D')
elif 70<=score<80:
    print('C')
elif 80<=score<90:
    print('B')
else:
    print('A')


### 示例3 嵌套if的使用
print("--------------------- 示例3 -------------------------")
answer=input('请问您喝酒了吗？')
if answer=='yes':
    proof=eval(input('请输入酒精含量：'))
    if proof<20:
        print('构不成酒驾，祝您一路平安')
    elif proof<80:
        print('已构成酒驾，请不要开车')
    else:
        print('已达到醉驾标准，请千万不要开车')
else:
    print('你走吧，没您啥事了')


### 示例4 使用and连接多个选择条件
print("--------------------- 示例4 -------------------------")
user_name=input('请输入您的用户名：')
pwd=input('请输入您的密码：')
if user_name=='zk' and pwd=='888888':
    print('登录成功')
else:
    print('用户名或密码不正确')


### 示例5 使用or连接多个选择条件
print("--------------------- 示例5 -------------------------")
score=eval(input('请输入您的成绩：'))
if score<0 or score>100:
    print('成绩无效')
else:
    print('您的成绩为：',score)
