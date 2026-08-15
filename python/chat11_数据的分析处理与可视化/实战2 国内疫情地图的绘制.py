"""
全国疫情可视化地图开发
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


### 取到各省的json数据并转换为python数据
data_dict = json.loads(data)  # 转换python数据
province_data_list = data_dict["areaTree"][0]["children"]  # 从字典中取出省份的数据


### 组装每个省份和确诊人数为元组，并将各个省份的数据都封装到列表内
data_list = []  # 绘图用的数据列表

for province_data in province_data_list:
    ## 提取各省份名字并加上后缀
    province_name = province_data["name"]
    SUFFIX_MAP = {
        '香港': '特别行政区', '澳门': '特别行政区',
        '北京': '市', '上海': '市', '天津': '市', '重庆': '市',
        '西藏': '自治区', '内蒙古': '自治区',
        '新疆': '维吾尔自治区',
        '广西': '壮族自治区',
        '宁夏': '回族自治区'
    }
    province_name += SUFFIX_MAP.get(province_name, '省')

    ## 提取各省份疫情人数数据
    province_confirm = province_data["total"]["confirm"]

    ## 将省份与对应疫情人数组合成元组并添加到data_list中
    data_list.append((province_name, province_confirm))


### 创建地图对象并添加数据
map = Map()
map.add("各省份确诊人数", data_list, "china") 


### 设置全局配置，定制分段的视觉映射
map.set_global_opts(
    title_opts=TitleOpts(title="全国疫情地图"),  # 地图标题
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
map.render("./生成的数据可视化图像/实战2 全国疫情地图.html") # 以chat11为相对路径