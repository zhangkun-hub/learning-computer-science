"""
将"1_将文本数据存储到MySQL数据库中.py"文件中执行程序存入到MySQL数据重新读取并写入到txt文件中。
其中txt文件的格式为JSON格式
"""
from pymysql import Connection
import json


### 一、提取出MySQL数据库的数据
## 1.1 获取MySQL数据库的连接对象
conn = Connection(
    host = 'localhost',    # 主机名（或IP地址），其中localhost表示是在自己电脑上
    port = 3306,           # 端口，默认3306
    user = 'root',         # 账户名
    password = '123456'    # 密码
)

## 1.2 获取游标对象
cursor = conn.cursor() 

## 1.3 选择数据库
conn.select_db("py_sql") 

## 1.4 执行SQL语句
cursor.execute("select * from orders")  # 该语句是提取所有数据(注：结果还驻留在数据库服务器端)

## 1.5 数据库服务器端取出上一行execute代码在数据库中执行的结果，并赋值给results
results = cursor.fetchall() # 注：results是列表，而列表中的每个元素代表表中一行数据(是元组形式)

## 1.6 关闭到数据库的链接
conn.close()


### 二、将提取的MySQL数据封装JSON格式并存储在txt文件中
## 2.1 创建存储字典的列表，从而构建JSON格式
data = []   

## 2.2 通过for循环将列表中的每行数据的元组形式封装成字典形式
for row in results:
    # 2.2.1 因为row[0] = datetime.date(2011, 2, 28)，所以需要转换成2011-2-28的字符串日期形式
    date = f"{row[0].year}-{row[0].month}-{row[0].day}"  
    # 2.2.2 封装字典
    row_dict = {"date": date, "order_id": row[1], "money": row[2], "province": row[3]}
    # 2.2.3 存入列表
    data.append(row_dict)

## 2.3 将JSON格式的数据写入txt文件中并保存
f = open("MySQL_data.txt", "w", encoding="UTF-8")
for row in data:
    f.write(f"{row}")
    f.write("\n")
f.close()



