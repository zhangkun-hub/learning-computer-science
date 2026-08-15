"""
一、pycharts库(包)：用于做出数据可视化效果图。
    1.使用说明：通过官方网站：https://pyecharts.org/，切换语言为中文，便直接进入到中文使用文档。

    2.画廊功能：通过网站：https://gallery.pyecharts.org/，进入到画廊网页，
                可以查看各种图表及其实现代码。

    3.pycharts库(包)的安装(具体见10-3)：在anaconda虚拟环境中输入：pip install pyecharts

二、pycharts库(包)的入门使用：
    1.基础折线图的使用：见示例1

    2.配置选项：
        (1)全局配置选项：针对整个图像去进行设置，比如图像的标题、图例等(见示例1)

        (2)系列配置选项：针对具体的轴数据进行配置，比如y轴的数据进行颜色等个性化配置(见11-4节内容)
"""

### 示例1 基础折线图的创建
print("--------------------- 示例1 -------------------------")
### 导入库(包)
from pyecharts.charts import Line           # 导入折线图功能
# 设置全局选项的功能模块(可选)
from pyecharts import options as opts
from pyecharts.options import TitleOpts     # 导入标题的控制功能
from pyecharts.options import LegendOpts    # 导入图例的控制功能
from pyecharts.options import ToolboxOpts   # 导入工具箱的控制功能
from pyecharts.options import VisualMapOpts # 导入视觉映射的控制功能
# 注：23-26行代码可以写在一起，具体见11-3的导入例子


### 创建一个折线图对象
line = Line()


### 给折线图对象添加x轴数据
line.add_xaxis(["中国", "美国", "英国"])


### 给折线图对象添加y轴数据
line.add_yaxis("GDP", [30, 20, 10])   # 其中第一个参数"GDP"表示图例中该数据的名字


### 设置图例"GDP"的位置
line.set_global_opts(
    legend_opts=opts.LegendOpts(
        pos_bottom="3%",     # 图例距离底部的距离，可以是像素值如"10px"或百分比
        pos_left="center",   # 图例距离左端的距离，可以是像素值如"10px"或百分比
        orient="horizontal"  # 水平排列图例
    )
)


### 设置全局配置项(可选)
line.set_global_opts(
    ## TitleOpts功能用来设置图像标题
    # 其中pos_left设置标题左右位置(center为中心)；pos_bottom设置上下位置(90%：距离底部90%距离)
    title_opts=TitleOpts(title="GDP展示", pos_left="center", pos_bottom="90%"),

    ## LegendOpts功能用来设置图像图例(可以控制36行代码中图例的显示、位置等)
    legend_opts=LegendOpts(is_show=True),        # is_show=True表示允许展示

    ## ToolboxOpts功能用来设置工具箱
    toolbox_opts=ToolboxOpts(is_show=True),      # is_show=True表示允许展示

    ## VisualMapOpts功能用来设置视觉映射(注：只适用于单组数据，因为多组数据的图像会变成同一颜色)
    visualmap_opts=VisualMapOpts(is_show=True),  # is_show=True表示允许展示
)   # 注：set_global_opts方法还有很多参数，根据具体情况去用


### 将代码生成为图像，其中可传入保存文件的名参数，以.html结尾(默认名字为render.html)
line.render("./生成的数据可视化图像/11-2 基础折线图.html")  # 以chat11为相对路径