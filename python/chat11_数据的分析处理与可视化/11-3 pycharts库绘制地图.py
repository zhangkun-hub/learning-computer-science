"""
通过pychaets模块来实现地图的创建
"""
### 导入创建地图所需的功能模块：Map和VisualMapOpts
from pyecharts.charts import Map
from pyecharts.options import VisualMapOpts

### 准备地图对象
map = Map()

### 准备数据
data = [   # 每个元素是个元组(A, B)，其中A为城市/省份等地图信息, B为对应的人口、经济等具体数据
    ("北京市", 9),
    ("上海市", 99),
    ("湖南省", 199),
    ("台湾省", 299),
    ("广东省", 399)
]

### 添加数据
map.add("测试地图", data, "china") # 参数1为数据名称、参数2为数据、参数3为地图类型(默认中国地图)

### 设置全局选项
map.set_global_opts(
    visualmap_opts=VisualMapOpts( # 配置地图各数据的视觉映射（颜色映射）选项
        is_show=True,             # 控制视觉映射组件要求显示
        is_piecewise=True, # 用分段式视觉映射，具体由下面pieces确定(若为False，则用连续渐变颜色)
        pieces=[     # 定义具体的数据分段规则，其元素的内容与含义见下面5行代码(可以直接看懂含义)
            {"min": 1, "max": 9, "label": "1-9", "color": "#CCFFFF"},
            {"min": 10, "max": 99, "label": "10-99", "color": "#FF6666"},
            {"min": 100, "max": 199, "label": "100-199", "color": "#990033"},
            {"min": 200, "max": 299, "label": "200-299", "color": "#24f03d"},
            {"min": 300, "max": 399, "label": "300-399", "color": "#020203"}
        ]
    )
)

### 绘图，其中可传入保存文件的名参数，以.html结尾(默认名字为render.html)
map.render("./生成的数据可视化图像/11-3 基础地图开发.html") # 以chat11为相对路径