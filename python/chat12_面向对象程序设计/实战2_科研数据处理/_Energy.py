from physical_quantity import EnergyProcessor
from data_record import EnergyRecord
import getpass

### 一、输入数据
J = 0.05   # t-J模型的系数J
N = 400    # 粒子数
Energy_data = getpass.getpass("请输入能量数据: ")   # getpass.getpass()默认不会在终端显示任何输入字符，适用于敏感或长数据输入


### 二、通过面向对象程序进行数据处理得到EnergyRecord对象
Energy_Processor = EnergyProcessor(Energy_data, N, J)
Energy: EnergyRecord = Energy_Processor.Process_data()

### 三、打印数据
print(Energy)
