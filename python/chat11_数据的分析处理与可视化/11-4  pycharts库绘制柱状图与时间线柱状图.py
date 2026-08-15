"""
通过pychaets库(包)来实现柱状图的创建。

一、柱状图：柱状图描述的是分类数据，回答每一个分类有多少数据的问题。
        (柱状图的绘制见示例1)

        注：但柱状图(还有折线图)很难动态描述一个趋势的数据，这就需要通过下面时间线来解决。

二、时间线Timeline()：如果一个Bar、Line对象是一张图表的话，时间线就是创建一个一维的x轴，
                轴上每一个点就是一个图表对象。
        (时间线柱状图的绘制见示例2)
"""
### 示例1 基础柱状图的绘制
print("--------------------- 示例1 -------------------------")
### 导入创建柱状图所需的功能模块：Bar
from pyecharts.charts import Bar
from pyecharts.options import LabelOpts


### 使用Bar构建基础柱状图
bar = Bar()


### 添加x轴和y轴数据
bar.add_xaxis(["中国", "美国", "英国"])
bar.add_yaxis("GDP", [30, 20, 10], label_opts=LabelOpts(position="right"))
# 添加y轴数据的参数label_opts是设置数据的数值标签，其中position="right"表示位于数据的右侧


### 反转x轴和y轴
bar.reversal_axis()


### 绘图
bar.render("./生成的数据可视化图像/11-4 示例1—基础柱状图.html") # 以chat11为相对路径



### 示例2 基础时间线柱状图的绘制
print("--------------------- 示例2 -------------------------")
### 导入创建时间线柱状图所需的功能模块：Bar、Timeline
from pyecharts.charts import Bar, Timeline
from pyecharts.globals import ThemeType
from pyecharts.options import LabelOpts
from pyecharts import options as opts




### 添加各时间线上的数据
bar1 = Bar()
bar1.add_xaxis(["中国", "美国", "英国"])
bar1.add_yaxis("GDP", [10, 30, 20], label_opts=LabelOpts(position="right"))
bar1.reversal_axis()

bar2 = Bar()
bar2.add_xaxis(["中国", "美国", "英国"])
bar2.add_yaxis("GDP", [40, 50, 30], label_opts=LabelOpts(position="right"))
bar2.reversal_axis()

bar3 = Bar()
bar3.add_xaxis(["中国", "美国", "英国"])
bar3.add_yaxis("GDP", [70, 60, 50], label_opts=LabelOpts(position="right"))
bar3.reversal_axis()


### 为每个图表设置全局选项，从而移动图例位置到顶部
for bar in [bar1, bar2, bar3]:
    bar.set_global_opts(
        legend_opts=opts.LegendOpts(
            pos_top="5%",        # 图例距离顶部的距离，可以是像素值如"10px"或百分比
            pos_left="50%",      # 图例距离左端的距离，可以是像素值如"10px"或百分比
            orient="horizontal"  # 水平排列图例
        )
    )


### 构建时间线对象并添加时间线数据
timeline = Timeline({"theme": ThemeType.LIGHT}) # 里面的参数用来设置主题(LIGHT表示蓝黄粉主题)

# 添加时间线数据
timeline.add(bar1, "点1")  # 第二个参数是时间线上各点的名称
timeline.add(bar2, "点2")
timeline.add(bar3, "点3")


### 设置自动播放
timeline.add_schema(
    play_interval=1000,     # 自动播放的时间间隔(单位ms)
    is_timeline_show=True,  # 是否显示时间线
    is_auto_play=True,      # 是否自动播放
    is_loop_play=True,      # 是否循环播放
)

### 绘图
timeline.render("./生成的数据可视化图像/11-4 示例2—基础时间线柱状图.html") # 以chat11为相对路径
