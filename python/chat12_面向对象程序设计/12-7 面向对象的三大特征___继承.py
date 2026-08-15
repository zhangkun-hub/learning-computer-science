"""
一、继承的引出：比如苹果手机每年都出新品，但每一代新款手机都从零开始设计图纸会很麻烦并浪费时间精力，
            所以可以基于老的设计图进行修修改改，由此引出了继承的思想。

二、继承思想："子承父业，代代相传"，即子类自动获得父类的属性和方法，实现代码复用和扩展。
        注：1.在python中一个子类可以继承N多个父类，同样一个父类也可以拥有N多个子类；
            2.如果一个类没有继承任何类(比如父类)，那么这个类默认继承的是object类。

三、作用：(继承是手段：通过继承建立类之间的关系，实现代码复用)
    1.代码复用；
    2.层次化设计；
    3.易于扩展。

四、单继承格式：
    class 父类名()         # 父类就是被继承的类(类似于老的图纸)
        父类内容体

    class 子类名(父类名)    # 子类就是继承父类的类(也就是在继承老的图纸上，新加的内容所构成的类)
        子类内容体          # 子类的内容是新加的内容(没有老的内容)

五、多继承：Python的类之间也支持多继承，即一个类可以继承多个父类。
    1.格式：
        class 父类1()         
            父类1内容体

        class 父类2()         
            父类2内容体
        ...

        class 子类名(父类1, 父类2,...)
            子类内容体

    2.多继承中，如果父类有同名方法或属性，则调用的优先级判定为：先继承的优先级高于后继承的。
        例如：设子类创建名称为：class w(A, B, C,...)，那么优先级标准为：A > B > C >...

六、复写：子类继承父类的成员属性和成员方法后，如果对其“不满意”，可以进行复写。
    1.操作方式：在子类中重新定义同名的属性或方法即可(具体见示例3)。
        (注：初始化方法也可以复写，而调用父类的初始化方法可以通过super()，即下面方式2)

    2.在子类中，如何调用父类的属性和方法(包括被复写的属性和方法)？
        (1)方式1：通过父类名打点调用，即：
            父类名.父类属性名
            父类名.父类方法名(self) # 需要在括号里传入self参数，其他在父类的参数也要传入

        (2)方式2：使用super()调用父类成员
            super().父类属性名
            super().父类方法名()   # 无需在括号里传入self参数，但其他在父类的参数要传入
                
"""
### 示例1 单继承
print("--------------------- 示例1 -------------------------")
# 父类
class Phone:
    IMEI = None         # 序列号
    producer = "ITCAST" # 厂商

    def call_by_4g(self):
        print("4g通话")

# 子类
class Phone2022(Phone):
    face_id = "10001"  # 面部识别ID

    def call_by_5g(self):
        print("2022年新功能：5g通话")

# 构建子类Phone2022的对象
phone = Phone2022()
# 因为继承特性，所以子类和父类的所有属性方法都可以调用
print(phone.producer) # HM
phone.call_by_4g()    # 4g通话
phone.call_by_5g()    # 2022年新功能：5g通话


### 示例2 多继承
print("--------------------- 示例2 -------------------------")
# 父类1见上面的class Phone
# 父类2——NFC读卡器
class NFCReader:
    nfc_type = "第五代"
    producer = "HM"

    def read_card(self):
        print("NFC读卡")

    def write_card(self):
        print("NFC写卡")

# 父类3——红外遥控器
class RemoteControl:
    rc_type = "红外遥控"

    def control(self):
        print("红外遥控开启了")

# 多继承的子类——我的手机
class MyPhone(Phone, NFCReader, RemoteControl):
    pass

# 创建对象
phone = MyPhone()

# 调用方法
phone.call_by_4g()   # 4g通话
phone.read_card()    # NFC读卡
phone.write_card()   # NFC写卡
phone.control()      # 红外遥控开启了
print()

# 调用同名属性producer
print(phone.producer) # ITCAST
# 输出的结果表明：先继承的优先级高于后继承的。
# 比如class w(A, B,...)，则各个父类同名属性在子类调用的优先级为：A > B > ...


### 示例3 复写
print("--------------------- 示例3 -------------------------")
# 父类
class Phone:
    IMEI = None         # 序列号
    producer = "ITCAST" # 厂商

    def call_by_5g(self):
        print("使用5g网络进行通话")

# 子类，复写父类成员
class MyPhone(Phone):
    producer = "HM" # 复写(修改)厂商

    # 复写(修改)父类方法call_by_5g(self)
    def call_by_5g(self):
        print("开启CPU单核模式，确保通话的时候省电")

        # # 调用被复写的方式1
        # print(f"父类的厂商是：{Phone.producer}")
        # Phone.call_by_5g(self)

        # 调用被复写的方式2
        print(f"父类的厂商是：{super().producer}")
        super().call_by_5g()

        print("关闭CPU单核模式，确保性能")

# 创建子类对象
phone = MyPhone()

# 调用复写的属性和方法
phone.call_by_5g()
print(phone.producer)