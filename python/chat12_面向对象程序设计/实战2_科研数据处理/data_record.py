"""
记录提取的物理量数据信息的类的定义
"""

### 定义一个抽象数据记录器用来做顶层设计
class Record:
    # 定义魔术方法__str__来实现对象的数据内容输出
    def __str__(self):
        pass


### 能量的数据记录器
class EnergyRecord(Record):
    def __init__(self, N, E0, Es, Es_J):
        self.N = N              # 系统格点数N
        self.E0 = E0            # 整个系统能量的数值E0
        self.Es = Es            # 单格点能量Es
        self.Es_J = Es_J        # Es与J的比值

    def __str__(self):
        return (
            f"系统格点数: N = {self.N}\n"
            f"整个系统能量的数值: E0 = {self.E0}\n"
            f"单格点能量: Es = {self.Es}\n"
            f"Es与J的比值: Es_J = {self.Es_J}"
        )
        


### 关联函数<i·j>的数据记录器
class CorrelationRecord(Record):
    def __init__(self, source_point, field_point, distance, Correlation):
        self.source_point = source_point    # 关联函数的源点i
        self.field_point = field_point      # 关联函数的场点j
        self.distance = distance            # 源点i与场点j之间的距离
        self.Correlation = Correlation      # 关联函数<i·j>的值

    def __str__(self):
        return f"关联函数的源点i = {self.source_point}, 场点j = {self.field_point}, 距离r = {self.distance}, 对应关联函数 = {self.Correlation:.6f}"
    