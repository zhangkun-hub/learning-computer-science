"""
使用第12章《面向对象》章节实战1中的数据集，在读取文件基础上，将数据写入MySQL。
其中本次开发需要新建一个数据库来使用，数据库名称：py_sql
"""
from file_define import TextFileReader, JsonFileReader
from data_define import Record
from pymysql import Connection


### 一、提取数据并存储到列表中
## 1.1 获取各月份数据的对象
text_file_reader = TextFileReader("2011年1月的销售数据.txt")
json_file_reader = JsonFileReader("2011年2月的销售数据JSON.txt")

## 1.2 通过方法read_data得到各月份数据的Record对象列表
jan_data: list[Record] = text_file_reader.read_data()
feb_data: list[Record] = json_file_reader.read_data()

## 1.3 将2个月份的数据合并为1个list来存储
all_data: list[Record] = jan_data + feb_data


### 二、将数据存储到MySQL数据库里
## 2.1 构建MySQL对象
conn = Connection(
    host = "localhost",
    port = 3306,
    user = "root",
    password = "123456",
    autocommit=True
)

## 2.2 获取游标对象
cursor = conn.cursor()

## 2.3 选择数据库
conn.select_db("py_sql")

## 2.4 组织并执行SQL语句
for record in all_data:
    sql = (f"insert into orders(order_date, order_id, money, province) "
          f"values('{record.date}', '{record.order_id}', '{record.money}', '{record.province}')")

    ## 2.4.1 执行SQL语句
    cursor.execute(sql)

## 2.6 关闭MySQL链接对象
conn.close()


