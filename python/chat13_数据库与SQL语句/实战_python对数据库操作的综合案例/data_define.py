"""
和数据相关的类定义
"""
class Record:

    def __init__(self, date, order_id, money, province):
        self.date = date           # 订单日期
        self.order_id = order_id   # 订单ID
        self.money = money         # 订单金额
        self.province = province   # 销售省份

    # 定义魔术方法__str__来实现对象的数据内容输出
    def __str__(self):
        return f"{self.date}, {self.order_id}, {self.money}, {self.province}"
    