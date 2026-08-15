"""
一、编码与解码：
    1.编码：将str(字符串类型)转换成bytes(二进制类型)的方法；
    2.解码：将bytes(二进制类型)转换成str(字符串类型)的方法。

二、作用：体现在两台计算机的数据在进行网络传输时的过程：
    计算机A的str  ---编码--->  bytes  ---网络传输--->  计算机B接收 ---解码--->  str

三、具体操作：
    1.编码：encode()方法
        语法格式：str.encode(字符串名, encoding='utf-8', errors='strict/ignore/replace')
            解释(对于解码含义也一致):
                1.encoding是编码格式，其中默认为utf-8，其它还有gbk格式；
                2.errors是编码过程中出错的解决方案，
                    其中ignore是忽略；
                        strict是严格，即遇到转不了字符则程序报错；
                        replace是替换，即遇到转不了字符会使用 ? 去替代无法转换的字符

    2.解码：decode()方法
        语法格式：bytes.decode(二进制变量名,encoding='utf-8',errors='strict/ignore/replace')

    注意：编码与解码的格式要一一对应

四、数据的验证：指程序对用户输入的数据进行“合法”性验证，比如银行密码必须是6位数字等
    常用的验证方法(以下方法在只有满足条件的才会输出True，否则输出False)：
        1.str.isdigit()：所有字符都是十进制的阿拉伯数字；
        2.str.isnumeric()：所有字符都是十进制数字；
        3.str.isalpha()：所有字符都是字母(包含中文字符)；
        4.str.isalnum()：所有字符都是数字或字母(包含中文字符)；
        5.str.islower()：所有字符都是小写（汉字即是大写又是小写）；
        6.str.isupper()：所有字符都是大写（汉字即是大写又是小写）；
        7.str.istitle()：所有字符都是首字母大写；
        8.str.isspace()：所有字符都是空白字符(\n、\t等)。
"""

### 示例1 编码与解码
print("--------------------- 示例1 -------------------------")
# 编码 str -> bytes
s = '伟大的中国梦'
scode = str.encode(s, errors='replace') # 注意，utf-8中文占3个字节，总共18个(打印中有18个\内容)
print(scode) # b'\xe4\xbc\x9f\xe5\xa4\xa7\xe7\x9a\x84\xe4\xb8\xad\xe5\x9b\xbd\xe6\xa2\xa6'

scode_gbk = s.encode('gbk', errors='replace') # gbk中文占2个字节，总共12个
print(scode_gbk) # b'\xce\xb0\xb4\xf3\xb5\xc4\xd6\xd0\xb9\xfa\xc3\xce'
print()

# 编码中的出错问题
s2 = '耶✌'
scode_error = s2.encode('gbk', errors='replace')
print(scode_error)  # b'\xd2\xae?'
print()

# 解码 bytes -> str
print(bytes.decode(scode_gbk,'gbk'))
print(scode.decode('utf-8'))


### 示例2 数据的验证
print("--------------------- 示例2 -------------------------")
# 阿拉伯数字的验证.isdigit()
print('123'.isdigit()) # True
print('一二三'.isdigit()) # False
print('0b1010'.isdigit()) # False（二进制也是验证失败）
print('ⅠⅡⅢ'.isdigit()) # False
print('壹贰叁'.isdigit()) # False
print()

# 数字的验证.isnumeric()
print('123'.isnumeric()) # True
print('一二三'.isnumeric()) # True
print('0b1010'.isnumeric()) # False（二进制仍然验证失败）
print('ⅠⅡⅢ'.isnumeric()) # True
print('壹贰叁'.isnumeric()) # True
print()

# 字母(包括中文)的验证.isalppha()
print('helo你好'.isalpha()) # True
print('helo你好123'.isalpha()) # False
print('helo你好一二三'.isalpha()) # True
print('heloⅠⅡⅢ'.isalpha()) # False
print('helo壹贰叁'.isalpha()) # Ture
print()

# 数字或字母(包括中文)的验证
print('helo你好'.isalnum()) # True
print('helo你好123'.isalnum()) # True
print('helo你好一二三'.isalnum()) # True
print('heloⅠⅡⅢ'.isalnum()) # True
print('helo壹贰叁'.isalnum()) # Ture
print()

# 小写的验证.islower()
print('HelloWorld'.islower()) # False
print('helloworld'.islower()) # True
print('hello你好'.islower()) # True（这说明汉字即是大写又是小写）
print()

# 大写的验证.isupper()
print('HelloWorld'.isupper()) # False
print('HELLOWORLD'.isupper()) # True
print('HELLO你好'.isupper()) # True（这说明汉字即是大写又是小写）
print()

# 首字母大写的验证.istitle()
print('Hello'.istitle()) # True
print('HelloWorld'.istitle()) # False
print('Helloworld'.istitle()) # True
print('Hello World'.istitle()) # True
print('Hello world'.istitle()) # False
print()

# 空白字符的验证.isspace()
print('\t'.isspace()) # True
print(' '.isspace()) # True
print('\n'.isspace()) # True