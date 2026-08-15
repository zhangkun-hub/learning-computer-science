"""
honeycomb晶格在XC构型下的坐标，以字典形式存储
"""
import sys
import numpy as np

### 输入格点数N(要求必须是4的倍数)
N = 32

### 判断格点数是否是最小基元格点数8的倍数
if N % 8 != 0:
    print(f"格点数N = {N} 不是最小基元格点数8的倍数，程序结束")
    sys.exit()  # 终止程序

### 设置honeycomb的晶格参数与存储字典
a = 1.0                      # 最近邻边长
hx = 3.0 * a                 # 同一水平面上相邻六边形中心的水平距离
hy = np.sqrt(3) * a          # 六边形高度
honeycomb_coords = {}        # 晶格坐标存储字典

### 建立0-7格点的坐标(这是XC构型下最小平移单元，其他格点都可由该单元平移hx长度得到)
coords_basis = [
    # 第1列
    (0.0, 0.0),           # 0格点
    (-0.5, 0.5 * hy),     # 1格点
    (0.0, hy),            # 2格点
    (-0.5, 1.5 * hy),     # 3格点

    # 第2列
    (a, 0.0),             # 4格点
    (a + 0.5, 0.5 * hy),  # 5格点
    (a, hy),              # 6格点
    (a + 0.5, 1.5 * hy)   # 7格点
]

### 建立所有N个格点的坐标字典
## 循环基元个数
for l in range(N//8):
    
    ## 循环基元内8个格点数
    for i in range(8):
        point = l * 8 + i
        x0, y0 = coords_basis[i]   # 解包i格点坐标
        honeycomb_coords[point] = (x0 + l * hx, y0)

print(honeycomb_coords)






