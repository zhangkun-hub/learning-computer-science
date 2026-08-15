"""
演示河南省疫情地图开发
"""
import json
from pyecharts.charts import Map
from pyecharts.options import *


### 读取数据文件并关闭
f = open(
    "./可视化案例数据/地图数据/疫情.txt",  # 相对chat11的路径
    "r", encoding = "UTF-8" 
)
data = f.read()
f.close()


### 取到河南省的json数据并转换为python数据
data_dict = json.loads(data)  # 转换python数据
# 从字典中取出河南省各城市数据
cities_data_list = data_dict["areaTree"][0]["children"][3]["children"]


### 组装河南省每个城市和确诊人数为元组，并将各个城市的数据都封装到列表内
data_list = []  # 绘图用的数据列表

for city_data in cities_data_list:
    ## 提取各城市名字并加上后缀
    city_name = city_data["name"] + "市"

    ## 提取各城市疫情人数数据
    city_confirm = city_data["total"]["confirm"]

    ## 将城市与对应疫情人数组合成元组并添加到data_list中
    data_list.append((city_name, city_confirm))

## 手动添加济源市的数据(因为文件里没有)
data_list.append(("济源市", 5))

### 创建地图对象并添加数据
map = Map()
map.add("河南省疫情分布", data_list, "河南")   # 注：第3个参数地图类型写"河南"


### 设置全局配置，定制分段的视觉映射
map.set_global_opts(
    title_opts=TitleOpts(title="河南省疫情地图"),  # 地图标题
    visualmap_opts=VisualMapOpts(
        is_show=True,
        is_piecewise=True,
        pieces=[
            {"min": 1, "max": 99, "label": "1~99人", "color": "#CCFFFF"},
            {"min": 100, "max": 999, "label": "100~999人", "color": "#FFFF99"},
            {"min": 1000, "max": 4999, "label": "1000~4999人", "color": "#FF9966"},
            {"min": 5000, "max": 9999, "label": "5000~9999人", "color": "#FF6666"},
            {"min": 10000, "max": 99999, "label": "10000~99999人", "color": "#CC3333"},
            {"min": 100000, "label": "100000+", "color": "#990033"},
        ]
    )
)


### 绘图
map.render("./生成的数据可视化图像/实战3 河南省疫情地图.html") # 以chat11为相对路径