"""
实战要求：
    1.读取文件bill.txt。
    2.将文件写出到bill.txt.bak文件作为备份。
    3.同时，将文件内标记为测试的数据行丢弃。

实现思路：
    1.open和r模式打开一个文件对象，并读取文件
    2.open和w模式打开另一个文件对象，用于文件写出
    3.for循环内容，判断是否是测试不是测试就write写出，是测试就continue跳过
    4.将2个文件对象均close()

扩展：.bak文件含义：表示任何类型的文件的备份文件，其文件类型跟原文件完全相同(即功能完全相同)，
            只是通过后缀bak来表明这是原文件的备份文件，而后缀bak是一种广泛使用的、简单明了的约定。
    比如：
        (1)上面的bill.txt.bak文件就是txt文件的备份，仍是txt文件，功能完全相同；
        (2)一个 report.docx.bak文件，其内部仍然是Word文档格式，需要用Word或兼容软件打开；
        (3)一个 database.db.bak仍然是数据库文件(.db)；
        (4)...
"""
# 打开文件得到文件对象，准备读取
fr = open("bill.txt", "r", encoding="UTF-8")

# 打开文件得到文件对象，准备写入
fw = open("bill.txt.bak", "w", encoding="UTF-8")

### for循环读取文件
for line in fr:
    # 将每行结尾的换行符\n去掉(strip方法见6-2)
    line = line.strip() 

    ## 判断内容，将满足的内容写出
    if line.split(",")[4] == "测试":
        continue

    # 将内容写出去
    fw.write(line)

    # 由于前面对内容进行了strip()的操作，所以要手动的写出换行符
    fw.write("\n")

# close2个文件对象
fr.close()
fw.close()  # 写出文件调用close()会自动flush()