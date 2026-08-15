"""
TCP服务端开发的编程步骤：
1.创建socket对象
socket_server = socket.socket()

2.绑定socket_server到指定IP和地址
socket_server.bind((host, port))  
    # 其中元组中host是IP，host="localhost"/127.0.0.1均表示自己的主机；port是端口号

3.服务端开始监听端口
socket_server.listen(backlog)
    # backlog为int，表示允许的客户端连接数量，超出的会等待，可以不填，不填会自动设置一个合理值

4.接收客户端连接，获得链接对象
conn, address = socket_server.accept()
print(f"接收到客户端连接，连接来自:{address}")
    # accept方法是阻塞方法，如果没有连接，会卡在当前这一行不向下执行代码
    # accept返回的是一个二元元组，可以使用上述形式，用两个变量接收二元元组的2个元素
    # 其中conn表示客户端和服务端的链接对象；address表示客户端的地址信息

5.服务端与客户端之间的信息交流传输
while True:
    # 可以通过while True无限循环来持续和客户端进行数据交互
    # 可以通过判定客户端或服务端发来的特殊标记，如exit，来退出无限循环    

    5.1 客户端连接后，通过recv方法，接收客户端发送的消息
    data = conn.recv(1024).decode("UTF-8")
        # recv方法的返回值是字节数组(Bytes)，可以通过decode使用UTF-8解码为字符串
        # recv方法的传参是buffsize，缓冲区大小，一般设置为1024即可
        # recv也是阻塞方法，如果客户端没有发送信息，则会卡在当前这一行不向下执行代码
    print("接收到客户端发送来的数据：", data)
    if data == 'exit':
        break

    5.2 通过conn(客户端当次连接对象)，调用send方法可以回复消息
    msg = input("请输入对客户端回复的消息：")
    conn.send(msg.encode("UTF-8"))
        # send接受的是字节数组，可以通过encode使用UTF-8将字符串编码为字节数组
    if msg == 'exit':
        break

6.conn(客户端当次连接对象)和socket_server对象调用close方法，关闭连接
conn.close()
socket_server.close() 
    # 注：如果要接收下一个客户端的链接，则无需关闭socket_server对象
"""
### 示例 TCP服务端开发
print("--------------------- 示例 -------------------------")
import socket

## 1.创建Socket对象
socket_server = socket.socket()

## 2.绑定ip地址和端口
socket_server.bind(("localhost", 8888))  # 注：localhost与127.0.0.1均表示自己的主机

## 3.监听端口
socket_server.listen(1)  # listen方法内接受一个整数参数，表示接受的客户端链接数量

## 4.等待客户端连接
result: tuple = socket_server.accept() # 注：如果没有链接，则会卡在这一步不向下执行了
conn = result[0]     # 客户端和服务端的链接对象
address = result[1]  # 客户端的地址信息
# conn, address = socket_server.accept()   # 更简便的写法

print(f"接收到客户端连接，客户端的信息是:{address}") 

## 5.服务端与客户端之间的信息交流传输
while True:
    # 5.1 接受客户端信息(注意：要使用客户端和服务端的本次链接对象，而非socket_server对象)
    data = conn.recv(1024).decode("UTF-8")
    print(f"客户端发来的消息是：{data}")
    if data == 'exit':
        break

    ## 5.2 发送回复消息
    msg = input("请输入你要和客户端回复的消息：")
    conn.send(msg.encode("UTF-8"))
    if msg == 'exit':
        break

## 6.关闭链接
conn.close()
socket_server.close()


#### 注：在没有开发客户端程序时(如果开发则直接运行即可)，如何运行服务端程序的具体操作：
# 1.先运行该程序和netAssist.exe可执行文件。
# 2.然后在netAssist.exe文件中的协议类选择TCP Client。
# 3.netAssist.exe文件中的远程ip = 127.0.0.1就是localhost，所以保持不变；而端口号要一致。
# 4.在netAssist.exe文件中点击开始连接。
# 5.在netAssist.exe文件中发送信息。
# 6.在程序的终端中回复信息。