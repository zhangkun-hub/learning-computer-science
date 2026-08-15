"""
对各国的GDP数据通过动态柱状图可视化

需求：
    1.GDP数据处理为亿级
    2.有时间轴，按照年份为时间轴的点
    3.x轴和y轴反转，同时每一年的数据只要前8个国家
    4.有标题，标题的年份会动态更改
    5.设置主题为LIGHT
"""
from pyecharts.charts import Bar, Timeline
from pyecharts.options import *
from pyecharts.globals import ThemeType
from pyecharts import options as opts


### 读取CSV数据
f = open(
    "./可视化案例数据/动态柱状图数据/1960-2019全球GDP数据.csv", # 相对chat11文件夹的路径
    "r", encoding="GB2312"
)
data_lines = f.readlines() 
f.close()


### 删除第一条数据然后转换成python字典
data_lines.pop(0)
data_dict = {}
for line in data_lines:
    year = int(line.split(",")[0])     # 年份
    country = line.split(",")[1]       # 国家
    gdp = float(line.split(",")[2])    # gdp数据(注意：float可以将科学计数法转换成float类型)

    # 通过异常捕获处理字典data_dict没有指定key的情况
    try:
        data_dict[year].append([country, gdp])
    except KeyError:
        data_dict[year] = []
        data_dict[year].append([country, gdp])


### 排序年份
sorted_year_list = sorted(data_dict.keys())


### 创建时间线对象
timeline = Timeline({"theme": ThemeType.LIGHT})


### 按年份顺序提取出GDP前8的国家数据，并绘制时间线柱状图
for year in sorted_year_list:
    data_dict[year].sort(key=lambda element: element[1], reverse=True)

    ## 取出本年份前8名的国家
    year_data = data_dict[year][0:8]

    ## 给柱状图的x轴、y轴添加数据
    x_data = []
    y_data = []
    for country_gdp in year_data:
        x_data.append(country_gdp[0])            # x轴添加国家
        y_data.append(country_gdp[1]/100000000)  # y轴添加对应GDP(以亿为单位)
    x_data.reverse()  # 反转x轴数据顺序
    y_data.reverse()  # 反转y轴数据顺序

    ## 绘制柱状图
    bar = Bar()
    bar.add_xaxis(x_data)
    bar.add_yaxis("GDP(亿)", y_data, label_opts=LabelOpts(position="right"))
    bar.reversal_axis()

    ## 为每个图表设置全局选项，从而移动图例位置到顶部
    bar.set_global_opts(
        legend_opts=opts.LegendOpts(
            pos_top="8%",        # 图例距离顶部的距离，可以是像素值如"10px"或百分比
            pos_left="50%",      # 图例距离左端的距离，可以是像素值如"10px"或百分比
            orient="horizontal"  # 水平排列图例
        )
    )

    ## 设置每一年的标题并添加时间线数据
    bar.set_global_opts(
        title_opts=TitleOpts(
            title=f"{year}年全球前8的GDP数据",  
            pos_top="2%",
            pos_left="40%"
        )
    )
    timeline.add(bar, str(year))


### 设置时间线自动播放
timeline.add_schema(
    play_interval=1000,
    is_timeline_show=True,
    is_auto_play=True,
    is_loop_play=False
)


### 绘制动态柱状图
timeline.render("./生成的数据可视化图像/实战4 1960-2019全球GDP前8国家.html") 
# 以chat11为相对路径





