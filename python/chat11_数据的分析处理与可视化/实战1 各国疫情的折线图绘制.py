"""
在可视化案例数据中的折线图数据进行可视化开发

数据共3个文件，分别记录了美国、日本和印度的疫情情况
"""
import json
from pyecharts.charts import Line           
from pyecharts.options import TitleOpts,LegendOpts,ToolboxOpts,VisualMapOpts,LabelOpts 

### 读取数据
f_us = open(
    "./可视化案例数据/折线图数据/美国.txt", # 相对chat11文件夹的路径
    "r", encoding="UTF-8"
)
us_data = f_us.read() # 美国的全部数据

f_jp = open(
    "./可视化案例数据/折线图数据/日本.txt", # 相对chat11文件夹的路径
    "r", encoding="UTF-8"
)
jp_data = f_jp.read() # 日本的全部数据

f_in = open(
    "./可视化案例数据/折线图数据/印度.txt", # 相对chat11文件夹的路径
    "r", encoding="UTF-8"
)
in_data = f_in.read() # 印度的全部数据

### 构建符合JSON格式的数据
## 去掉不合JSON规范的开头
us_data = us_data.replace("jsonp_1629344292311_69436(", "")
jp_data = jp_data.replace("jsonp_1629350871167_29498(", "")
in_data = in_data.replace("jsonp_1629350745930_63180(", "")

## 去掉不合JSON规范的结尾
us_data = us_data[:-2]  # 也可以用rstrip方法
jp_data = jp_data[:-2]
in_data = in_data[:-2]

### JSON数据转python数据
us_dict = json.loads(us_data)
jp_dict = json.loads(jp_data)
in_dict = json.loads(in_data)

### 获取trend key
us_trend_data = us_dict['data'][0]['trend']
jp_trend_data = jp_dict['data'][0]['trend']
in_trend_data = in_dict['data'][0]['trend']

### 获取日期数据，用于x轴（取2020年这一年即可）
us_x_data = us_trend_data['updateDate'][:314]
jp_x_data = jp_trend_data['updateDate'][:314]
in_x_data = in_trend_data['updateDate'][:314]

### 获取确诊的数据，用于y轴（取2020年这一年即可）
us_y_data = us_trend_data['list'][0]['data'][:314]
jp_y_data = jp_trend_data['list'][0]['data'][:314]
in_y_data = in_trend_data['list'][0]['data'][:314]

### 生成可视化图表
line = Line()

## 添加x轴数据（注：x轴数据是共用的）
line.add_xaxis(us_x_data)

## 添加y轴数据（第三参数结果是图像中各数据的y轴数字不显示）
line.add_yaxis("美国确诊人数", us_y_data, label_opts=LabelOpts(is_show=False)) # 美国y轴数据
line.add_yaxis("日本确诊人数", jp_y_data, label_opts=LabelOpts(is_show=False)) # 日本y轴数据
line.add_yaxis("印度确诊人数", in_y_data, label_opts=LabelOpts(is_show=False)) # 印度y轴数据

## 设置全局选项
line.set_global_opts(
    # 标题设置
    title_opts=TitleOpts(title="2020年美日印三国确诊人数对比折线图", 
                        pos_left="center", pos_bottom="90%"),

    # 设置图像图例
    legend_opts=LegendOpts(is_show=True),        # is_show=True表示允许展示

    # 设置工具箱
    toolbox_opts=ToolboxOpts(is_show=True),      # is_show=True表示允许展示
)

## 将代码生成为图像
line.render("./生成的数据可视化图像/实战1 各国疫情情况.html")  # 以chat11为相对路径
