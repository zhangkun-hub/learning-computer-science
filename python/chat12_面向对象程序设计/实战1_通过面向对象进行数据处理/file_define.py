"""
和文件相关的类定义
"""
from data_define import Record
import json

#### 先定义一个抽象类用来做顶层设计，确定有哪些功能需要实现
class FileReader:

    def __init__(self, path):
        self.path = path   # 定义成员属性path用来记录文件的路径

    def read_data(self) -> list[Record]:
        """
        读取文件数据，然后将读到的每一行数据都转换为Record对象(Record类在data_define文件中)，
        并封装到list列表(因为数据行数可能很多，所以Record对象太多，需要列表存储)，最后返回即可。
        """
        pass


#### 构建读取文本数据的文件读取器
class TextFileReader(FileReader):

    ### 复写父类的方法
    def read_data(self) -> list[Record]:
        f = open(self.path, "r", encoding = "UTF-8")

        record_list: list[Record]= [] # 存储每个Record对象

        ## 通过for循环按每行提取出文件数据
        for line in f.readlines():
            # strip()与split()方法见字符串6-2内容
            line = line.strip()  # 将提取的每行数据line前后空格和换行符\n都消除掉
            data_list = line.split(",") # 将数据line按照逗号进行分隔,并将分隔元素以列表形式存储

            # 将每行数据列表data_list转换成Record对象并存储到列表record_list中
            record = Record(data_list[0], data_list[1], int(data_list[2]), data_list[3])
            record_list.append(record)

        f.close()

        return record_list


#### 构建读取JSON格式数据的文件读取器
class JsonFileReader(FileReader):

    ### 复写父类的方法
    def read_data(self) -> list[Record]:
        f = open(self.path, "r", encoding = "UTF-8")

        record_list: list[Record]= [] # 存储每个Record对象

        ## 通过for循环提取出每行数据
        for line in f.readlines():
            data_dict = json.loads(line)

            # 将每行数据字典data_dict转换成Record对象并存储到列表record_list中
            record = Record(data_dict["date"], data_dict["order_id"], 
                            int(data_dict["money"]), data_dict["province"])
            record_list.append(record)

        f.close()

        return record_list
    


# 测试内容（测试文件是否成功读取并将数据保存为Record对象）
if __name__ == '__main__': # if表示运行该文件时会执行下面代码，但作为导包导进去时则不会执行
    text_file_reader = TextFileReader("2011年1月的销售数据.txt")
    json_file_reader = JsonFileReader("2011年2月的销售数据JSON.txt")

    list1 = text_file_reader.read_data()
    list2 = json_file_reader.read_data()

    for l in list1:
        print(l)
    print()

    for l in list2:
        print(l)

    