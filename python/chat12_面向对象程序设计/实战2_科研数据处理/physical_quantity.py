import re
import sys
import ast
from data_record import EnergyRecord
from data_record import CorrelationRecord


#### 定义一个抽象数据处理器用来做顶层设计,里面是囊括honeycomb晶格坐标与处理物理量数据的方法
class Processor:
    ### 传入数据的初始化方法
    def __init__(self, data):
        self.data = data   # 定义成员属性data用来存储传入数据
 
    ### 提取并处理数据的方法
    def Process_data(self):
        pass
    



#-----------------------------------------------------------------------------------
#--------------------------------能量的数据处理器-----------------------------------

class EnergyProcessor(Processor):
    """
    Input:
    :data: 计算的能量的数据
    :N: 格点数
    :N: t-J模型的系数J
    """ 
    def __init__(self, data, N, J):
        super().__init__(data)  # 调用父类的初始化方法
        self.N = N    # 格点数N
        self.J = J    # t-J模型的系数J
    

    ### 复写父类的提取与处理数据的方法
    def Process_data(self) -> EnergyRecord:
        """
        将输入的字符串数据data的所有E0值提取出来，进行数据处理，然后封装为EnergyRecord对象，
        最后返回该EnergyRecord对象。
        """
        ## 使用正则表达式匹配数据中所有E0值
        pattern = r'E0\s*=\s*(-?\d+\.\d+)'
        matches = re.findall(pattern, self.data)
        
        ## 将匹配的字符串转换为浮点数
        E0_list = [float(match) for match in matches]
        
        ## 进行数据处理
        E0 = sum(E0_list) / len(E0_list)  # 提取出所有E0值的求平均作为能量E0值
        Es = E0 / self.N                  # 单格点能量Es
        Es_J = Es / self.J                # Es与J的比值

        ## 将能量数据存储在Record_Energy对象中
        E_data = EnergyRecord(self.N, E0, Es, Es_J)

        return E_data




#--------------------------------------------------------------------------------------
#---------------------------关联函数<i·j>的数据处理器---------------------------------

class CorrelationProcessor(Processor): 
    """
    Input:
    :data: 计算的关联函数的数据
    :sequence: honeycomb晶格下有意义的关联格点序列
                由源点位置而分为两种情形：源点处于A子格的序列/源点处于B子格的序列
                例如：A子格序列：range(1, 300, 4)      
                     B子格序列：range(2, 300, 4)
    """ 
    def __init__(self, data, sequence):
        super().__init__(data)     # 调用父类的初始化方法
        self.sequence = sequence   # honeycomb晶格下有意义的关联格点序列


    #### 复写父类的提取与处理数据的方法
    def Process_data(self) -> list[CorrelationRecord]:
        """
        将输入的字符串数据data(内容是列表序列)每一元素都封装为CorrelationRecord对象，
        然后存储到list列表中，最后返回元素为CorrelationRecord对象的列表。
        """
        data_list = ast.literal_eval(self.data)   # 取出数据列表
        record_list: list[CorrelationRecord]= []  # 创建存储每个CorrelationRecord对象的列表

        ### 判断列表的每个源点的值是否都相同
        point_i = data_list[0][0][0]        # 关联函数的源点i
        for k in range(len(data_list)):
            i = data_list[k][0][0]
            if i != point_i:
                print(f"第{k}个元素的关联函数的源点有问题，程序结束")
                sys.exit()  # 终止程序

        ### 判断源点i是否在输入的序列sequence中
        if point_i not in self.sequence:
            print(f"关联函数的源点{point_i}不在输入的序列中，不符合逻辑，程序结束")
            sys.exit()  # 终止程序

        ### 通过for循环提取出列表每个元素的数据并处理
        for element in data_list:
            j = element[0][1]  # 场点

            ## 判断场点j是否在输入的序列sequence中，符合才提取
            if j in self.sequence:    
                r = abs(j - point_i) / 4     # 计算场点与源点的距离
                value = element[1][0]        # 获取关联函数的值

                # 转成CorrelationRecord对象并存储
                record = CorrelationRecord(point_i, j, r, value)
                record_list.append(record)

        return record_list
    




#------------------------------------------------------------------------------------
#-----------------------自旋关联函数的合并方法(与类无关)-----------------------------
def Combined_spin_correlation(
        SzSz: list[CorrelationRecord], 
        SuSd: list[CorrelationRecord], 
        SdSu: list[CorrelationRecord]
) -> list[CorrelationRecord]:
    """
    <S_i·S_j> = <S^z_i·S^z_j> + <S^+_i·S^-_j> + <S^-_i·S^+_j>
    通过上述公式，将输入的三个独立自旋关联函数的CorrelationRecord对象列表进行合并

    Input:
    :SzSz: 存储自旋关联函数<S^z_i·S^z_j>的CorrelationRecord对象列表
    :SuSd: 存储自旋关联函数<S^+_i·S^-_j>的CorrelationRecord对象列表
    :SdSu: 存储自旋关联函数<S^-_i·S^+_j>的CorrelationRecord对象列表

    Return:
    :SiSj: 存储自旋关联函数<S_i·S_j>的CorrelationRecord对象列表
    """
    ### 1.检查三个关联函数长度是否一致
    if len(SzSz) != len(SuSd) or len(SzSz) != len(SdSu):
        print("输入的三个自旋关联函数的列表长度不一致，程序结束")
        sys.exit()  # 终止程序

    ### 2.检查源点是否完全相同
    SzSz_i = SzSz[0].source_point
    SuSd_i = SuSd[0].source_point
    SdSu_i = SdSu[0].source_point
    if SzSz_i != SuSd_i:
        print("关联函数<S^z_i·S^z_j>与<S^+_i·S^-_j>的源点不相同，程序结束")
        sys.exit()  # 终止程序
    if SzSz_i != SdSu_i:
        print("关联函数<S^z_i·S^z_j>与<S^-_i·S^+_j>的源点不相同，程序结束")
        sys.exit()  # 终止程序

    ### 3.遍历列表所有元素进行判断与合并
    SiSj = []
    for k in range(len(SzSz)):
        ## 3.1 获取每个列表当前元素(是个CorrelationRecord对象)
        SzSz_Record = SzSz[k]
        SuSd_Record = SuSd[k]
        SdSu_Record = SdSu[k]

        ## 3.2 获取元素对象的各个属性
        j = SzSz_Record.field_point           # 场点
        r = SzSz_Record.distance              # 距离
        SzSz_value = SzSz_Record.Correlation  # <S^z_i·S^z_j>
        SuSd_value = SuSd_Record.Correlation  # <S^+_i·S^-_j>
        SdSu_value = SdSu_Record.Correlation  # <S^-_i·S^+_j>
                
        ## 3.3 求出<S_i·S_j>的值，并生成CorrelationRecord对象
        SiSj_value = SzSz_value + SuSd_value + SdSu_value
        record = CorrelationRecord(SzSz_i, j, r, SiSj_value)

        ## 3.4 将record添加到SiSj列表中
        SiSj.append(record)

    return SiSj




#------------------------------------------------------------------------------------------------
#---------------------------超导关联函数<i·j·k·l>的数据处理器---------------------------------
    



