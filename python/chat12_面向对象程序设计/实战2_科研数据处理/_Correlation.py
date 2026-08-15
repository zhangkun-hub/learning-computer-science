#--------------------------------------------------------------------------------------------------------------------------
#---------------------########### A子格下的自旋-自旋关联函数<S_i·S_j>数据提取与作图 ################--------------------------
import getpass
import numpy as np
import matplotlib.pyplot as plt
from physical_quantity import CorrelationProcessor
from data_record import CorrelationRecord
from physical_quantity import Combined_spin_correlation



### 一、输入数据
N = 400  # 格点数
data_SuSd = getpass.getpass("请输入<S^+_i·S^-_j>: ")   # getpass.getpass()默认不会在终端显示任何输入字符，适用于敏感或长数据输入
data_SdSu = getpass.getpass("请输入<S^-_i·S^+_j>: ")
data_SzSz = getpass.getpass("请输入<S^z_i·S^z_j>: ")


### 二、生成A子格序列       
Field_point = int(N / 4 / 4 * 3) * 4 - 3   # 对小数来说，int直接去掉小数部分，比如int(3.8) = 3
A_sequence = range(1, Field_point + 1, 4) 


### 三、通过面向对象程序进行数据处理
## 3.1 获取各关联函数的处理器对象
SzSz_Processor = CorrelationProcessor(data_SzSz, A_sequence)
SuSd_Processor = CorrelationProcessor(data_SdSu, A_sequence)
SdSu_Processor = CorrelationProcessor(data_SuSd, A_sequence)

## 3.2 通过方法Process_data得到各关联函数数据的CorrelationRecord对象列表
SzSz: list[CorrelationRecord] = SzSz_Processor.Process_data()
SuSd: list[CorrelationRecord] = SuSd_Processor.Process_data()
SdSu: list[CorrelationRecord] = SdSu_Processor.Process_data()

## 3.3 通过函数Combined_spin_correlation得到<S_i·S_j>的CorrelationRecord对象列表
SiSj: list[CorrelationRecord] = Combined_spin_correlation(SzSz, SuSd, SdSu)

## 3.4 关联函数的源点
point_i = SiSj[0].source_point  

## 3.5 打印SiSj的前5个数据
for record in SiSj[:5]:
    print(record)
print(f"... 还有{len(SiSj)-5}个点")


### 四、数据可视化
## 4.1 将数据存储到x轴和y轴列表中
x_data = [] # 创建存储两格点之间的距离数据
y_data = [] # 创建存储在x_data的距离下对应的自旋关联函数数据
for element in SiSj:
    x_data.append(element.distance)
    y_data.append(element.Correlation)

## 4.2 创建1行3列的子图布局
fig, axs = plt.subplots(1, 3, figsize=(20, 6))

## 4.3 线性坐标图（原始）
axs[0].scatter(x_data, y_data, color='blue', s=60, zorder=3)
axs[0].plot(x_data, y_data, color='red', alpha=0.5, linewidth=2)
axs[0].set_title(f'Linear Scale\nspin correlation function $\\langle S_i \\cdot S_j \\rangle$ (reference site: {point_i})', fontsize=16)
axs[0].set_xlabel('distance r', fontsize=14)
axs[0].set_ylabel(f'$\\langle S_i \\cdot S_j \\rangle$', fontsize=14)
axs[0].axhline(y=0, color='black', linewidth=3.5, linestyle='-', alpha=0.8, zorder=1)
axs[0].grid(True, alpha=0.3, linestyle='--')

## 4.4 半对数坐标图（y轴对数）- 用于判断指数衰减
# 注意：如果y_data有负值，对数坐标会有问题，这里取绝对值
y_abs = np.abs(y_data)
axs[1].scatter(x_data, y_abs, color='green', s=60, zorder=3)
axs[1].plot(x_data, y_abs, color='orange', alpha=0.5, linewidth=2)
axs[1].set_yscale('log')
axs[1].set_title(f'Log-Linear Scale (y-log)\nExponential decay check', fontsize=16)
axs[1].set_xlabel('distance r', fontsize=14)
axs[1].set_ylabel(f'$|\\langle S_i \\cdot S_j \\rangle|$ (log scale)', fontsize=14)
axs[1].grid(True, alpha=0.3, linestyle='--', which='both')

## 4.5 双对数坐标图 - 用于判断幂律衰减
axs[2].scatter(x_data, y_abs, color='purple', s=60, zorder=3)
axs[2].plot(x_data, y_abs, color='brown', alpha=0.5, linewidth=2)
axs[2].set_xscale('log')
axs[2].set_yscale('log')
axs[2].set_title(f'Log-Log Scale\nPower-law decay check', fontsize=16)
axs[2].set_xlabel('distance r (log scale)', fontsize=14)
axs[2].set_ylabel(f'$|\\langle S_i \\cdot S_j \\rangle|$ (log scale)', fontsize=14)
axs[2].grid(True, alpha=0.3, linestyle='--', which='both')

## 4.6 调整布局
plt.tight_layout()

## 4.7 显示图表
plt.show()
