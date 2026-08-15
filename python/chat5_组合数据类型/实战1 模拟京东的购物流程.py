"""
模拟京东的购物流程，内容见网课P60
"""
lst=[]
for i in range(5):
    goods=input('请输入商品的编号和商品的名称进行商品入库，每次只能输入一件商品：')
    lst.append(goods)
    
# 输出所有商品信息
for item in lst:
    print(item)

# 创建空列表，用于储存购物车中的商品
cart=[]
while True: # 无限循环命令，通常需要在循环体内通过break、return或异常来终止循环。
    flag=False # 代表没有商品的情况
    num=input('请输入要购买的商品编号')
    # 遍历商品列表，查询一下要购买的商品是否存在
    for item in lst:
        if num==item[0:4]: # 切片操作，从商品中切出序号
            flag=True # 代表商品已找到
            cart.append(item) # 添加到购物车中
            print('商品已成功添加到购物车')
            break # 退出for循环
    if not flag and num!='q': # 这里q指输入商品编号为q则退出添加商品操作即while循环,而not flag指==True时才满足条件
        print('商品不存在')

    if num=='q':
        break # 退出while循环
print('-'*50)
print('您购物车里已选择的商品为：')
cart.reverse()
for item in cart:
    print(item)
