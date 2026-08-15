"""
一、多态思想："同一种操作，不同的行为"，即相同的函数/方法调用，作用于不同的对象，会产生不同的状态。

二、作用：(多态是目的：通过统一接口调用不同的实现，提高代码的灵活性和可扩展性)
    1.接口统一；
    2.提高灵活性；
    3.易于扩展新类型。

三、应用场景：多态常作用在继承关系上，比如函数形参声明接收父类对象，但实际传入父类的子类对象进行工作
        具体而言：
            1.以父类做定义声明；
            2.以子类做实际工作；
            3.用以获得同一操作下的不同状态。

四、实现方式：通过抽象类(接口)来实现：
    抽象类(接口)：含有抽象方法的类称之为抽象类；
    抽象方法：方法体是空实现(pass)的称之为抽象方法。

    解释：抽象类(接口)就好比定义一个标准，但并不拿来直接使用(即获得抽象类的具体对象)
                而抽象类里包含的一些抽象的方法(即标准)，是要求子类必须实现。

        比如示例2中：定义的抽象空调类是用来制定标准：制冷、制热和左右摆风，这些标准都是抽象方法。
                而定义的子类美的空调类和格力空调类通过复写抽象方法，来用自己的核心技术实现空调的
                三个标准，然后创建各自子类的对象，在同一操作(比如制冷)下产生不同的状态(即各自的
                核心技术)，这就是多态的体现。

"""
### 示例1 多态的实现
print("--------------------- 示例1 -------------------------")
# 父类——动物类
class Animal:
    def speak(self):
        pass

# 子类1——狗类
class Dog(Animal):
    def speak(self):
        print("汪汪汪")

# 子类2——猫类
class Cat(Animal):
    def speak(self):
        print("喵喵喵")

# 制造噪音的操作(函数)
def make_noise(animal: Animal):
    """制造点噪音，需要传入Animal对象"""
    animal.speak()

# 演示多态，使用2个子类对象来调用函数
dog = Dog()
cat = Cat()

# 多态的展现：即同一操作（make_noise）作用不同对象有不同状态
make_noise(dog)  # 汪汪汪
make_noise(cat)  # 喵喵喵


### 示例2 抽象类(接口)的演示
print("--------------------- 示例2 -------------------------")
# 定义一个抽象类(接口)：空调AC
class AC:
    def cool_wind(self):
        """制冷"""
        pass

    def hot_wind(self):
        """制热"""
        pass

    def swing_l_r(self):
        """左右摆风"""
        pass

# 子类——美的空调
class Midea_AC(AC):
    def cool_wind(self):
        print("美的空调制冷")

    def hot_wind(self):
        print("美的空调制热")    

    def swing_l_r(self):
        print("美的空调左右摆风")

# 子类——格力空调
class GREE_AC(AC):
    def cool_wind(self):
        print("格力空调制冷")

    def hot_wind(self):
        print("格力空调制热")    

    def swing_l_r(self):
        print("格力空调左右摆风")

# 制冷操作
def make_cool(ac: AC):
    ac.cool_wind()

# 定义美的空调对象和格力空调对象
midea_ac = Midea_AC()
gree_ac = GREE_AC()

# 多态展现
make_cool(midea_ac)  # 美的空调制冷
make_cool(gree_ac)   # 格力空调制冷