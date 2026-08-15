""" 
一、match语句(与c语言的switch类似):进行表示式值的匹配,若其值与对应case值匹配,则执行该case的代码,
    都不匹配则执行default代码。

二、match语句基本格式：
match 变量/表达式:
    case 模式1:
        语句体1
    case 模式2:
        语句体2
    case 模式3 if 条件:    # 带守卫的条件
        语句体3
    ...
    case _:         # 其余情况（类似c语言的default）
        语句体n
        
三、注意:1.case _中下划线 _是通配符,匹配所有情况；
        2.若不写case _，但变量没有一个模式可以匹配，则跳出match语句到下一行代码；
        3.特别注意：match只在 python 3.10 即以上可以用！
"""

score=input('请输入成绩等级：')
match score:
    case 'A':
        print('优秀')
    case 'B':
        print('良好')
    case 'C':
        print('及格')
    case 'D':
        print('不及格')
    case _:
        print('不存在该成绩等级')


        