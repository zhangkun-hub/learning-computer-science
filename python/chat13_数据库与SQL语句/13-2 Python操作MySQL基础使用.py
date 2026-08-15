"""
一、使用方式：通过第三方库(包)：pymysql来完成对MySQL数据库的操作。
        安装方式：pip install pymysql

二、通过python操作数据库执行SQL语句的语法：具体见示例1

    注意事项：
        1.跟文件一样，在操作完数据库后，一定要断掉链接；
        2.在python的操作中，SQL语句末尾的分号可以不用写，但在SQL上操作则必须写。

三、python执行数据插入到数据库语法：
        pymysql在执行数据插入或其他产生数据更改的SQL语句时，默认是需要提交更改的，即需要通过
    代码“确认”这种更改行为。这需要通过链接对象.commit()即可确认此行为。具体见示例2。

    注意：也可以设置自动提交，即在开头获取MySQL数据库的连接对象的方法Connection里传入参数：
        autocommit = True，这就是设置为自动提交，见64行代码
"""
### 示例1 通过python操作MySQL
print("--------------------- 示例1 -------------------------")
### 导入pymysql包
from pymysql import Connection

### 获取MySQL数据库的连接对象
conn = Connection(
    host = 'localhost',    # 主机名（或IP地址），其中localhost表示是在自己电脑上
    port = 3306,           # 端口，默认3306
    user = 'root',         # 账户名
    password = '123456'    # 密码
)

### 打印MySQL数据库软件信息
# print(conn.get_server_info())  # 8.0.45（这是MySQL数据库的版本号）


### 获取游标对象并选择数据库(执行SQL语句的前提准备)
cursor = conn.cursor() # 获取游标对象
conn.select_db("world") # 选择数据库


### 执行SQL语句，注意以下内容：
# (1)""里面内容可以写任何SQL语句并执行。
# (2)在python的操作中，SQL语句末尾的分号可以不用写，但在SQL上操作则必须写
# cursor.execute("create table test_pymysql(id int)")  # 创建test_pymysql的一列为id的表格

## 提取MySQL数据库里表格的数据内容并展示
cursor.execute("select * from student")  # 执行SQL语句(注意：结果还驻留在数据库服务器端)
results = cursor.fetchall()  # 从数据库服务器端取出上一行execute查询准备好的整个结果集。

# 注：cursor.fetchall()返回的results是列表，而列表中的每个元素代表表中一行数据(是元组形式)
for r in results:  
    print(r)  # 将表格中的行数据以元组形式显示，比如：(10001, '周杰轮', 31, '男')


### 关闭到数据库的链接
conn.close()



### 示例2 数据插入
print("--------------------- 示例2 -------------------------")
### 导入pymysql包
from pymysql import Connection

### 获取MySQL数据库的连接对象
conn = Connection(
    host = 'localhost',    # 主机名（或IP地址），其中localhost表示是在自己电脑上
    port = 3306,           # 端口，默认3306
    user = 'root',         # 账户名
    password = '123456'    # 密码
    # autocommit = True      # 设置自动提交
)

### 获取游标对象并选择数据库(执行SQL语句的前提准备)
cursor = conn.cursor() # 获取游标对象
conn.select_db("world") # 选择数据库

### 执行SQL语句
cursor.execute("insert into student values(10021, '蔡徐坤', 31, '男')")  

### 通过commit确认
conn.commit()

### 关闭到数据库的链接
conn.close()
