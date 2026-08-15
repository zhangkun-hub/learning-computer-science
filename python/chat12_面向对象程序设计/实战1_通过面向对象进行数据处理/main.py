"""
通过面向对象思想进行数据分析

实现步骤：
1.设计一个类Record，可以完成数据的封装（文件data_define中实现）
2.设计一个抽象类FileReader，定义文件读取的相关功能，并使用子类实现具体功能（文件file_define中实现）
3.读取文件，生产数据对象（文件file_define中实现）
4.进行数据需求的逻辑计算，即计算每一天的销售额（主文件main中实现）
5.通过PyEcharts进行图形绘制（主文件main中实现）
"""
from file_define import TextFileReader, JsonFileReader
from data_define import Record
from pyecharts.charts import Bar
from pyecharts.options import *
from pyecharts.globals import ThemeType

### 一、获取各月份数据的对象
text_file_reader = TextFileReader("2011年1月的销售数据.txt")
json_file_reader = JsonFileReader("2011年2月的销售数据JSON.txt")

### 二、通过方法read_data得到各月份数据的Record对象列表
jan_data: list[Record] = text_file_reader.read_data()
feb_data: list[Record] = json_file_reader.read_data()

### 三、将2个月份的数据合并为1个list来存储
all_data: list[Record] = jan_data + feb_data

### 四、开始进行数据计算
data_dict = {} # 存储每日的销售总额，例如{"2011-01-01": 1534, "2011-01-02": 300, ...}
## 获取每个数据对象record
for record in all_data:
    # 判断当前数据日期是否记录在当前字典的key内
    if record.date in data_dict.keys():
        # 当前日期已经有记录了，所以对该日期的销售额进行累加
        data_dict[record.date] += record.money
    # 如果没在key中记录，则在字典中添加该日期(key)与相应的销售额(value)    
    else:
        data_dict[record.date] = record.money

### 五、可视化图表开发
bar = Bar(init_opts=InitOpts(theme=ThemeType.LIGHT)) 

bar.add_xaxis(list(data_dict.keys()))               # 添加x轴的数据
bar.add_yaxis("销售额", list(data_dict.values()), 
              label_opts=LabelOpts(is_show=False))  # 添加y轴的数据

# 添加图表标题
bar.set_global_opts(
    title_opts = TitleOpts(title="每日销售额")
)

bar.render("每日销售额柱状图.html")
