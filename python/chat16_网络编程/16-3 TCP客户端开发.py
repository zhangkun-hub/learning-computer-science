"""
TCP客户端开发的编程步骤：
1.创建socket对象
import socket
socket_client = socket.socket()

2.连接到服务端
socket_client.connect(("localhost", 8888))

3.通过无限循环发送消息并接收消息
while True: 
    # 可以通过while True无限循环来持续和服务端进行数据交互
    # 可以通过判定客户端或服务端发来的特殊标记，如exit，来退出无限循环 

    3.1 给服务端发送消息
    send_msg = input("请输入要给服务端发送的消息")
    socket_client.send(send_msg.encode("UTF-8"))  # 消息需要编码为字节数组（UTF-8编码）
    if send_msg == 'exit':   # 通过特殊标记来确保可以退出无限循环
        break

    3.2 接收服务端返回消息
    recv_data=socket_client.recv(1024)  
        # 1024是缓冲区大小，一般1024即可
        # recv方法是阻塞式的，即不接收到返回，就卡在这里等待

    print("服务端回复消息为：",recv_data.decode("UTF-8")) # 接受的消息要通过UTF-8解码为字符串

4.关闭链接
socket_client.close()  # 最后通过close关闭链接
"""
### 示例 TCP客户端开发
print("--------------------- 示例 -------------------------")
import socket

## 1.创建socket对象
socket_client = socket.socket()

## 2.连接服务端
socket_client.connect(("localhost", 8888))

## 3.通过无限循环发送消息并接收消息
while True:
    # 3.1 向服务端发送消息
    msg = input("请输入要给服务端发送的消息")
    socket_client.send(msg.encode("UTF-8"))
    if msg == 'exit':
        break

    # 3.2 接收服务端返回消息
    recv_data = socket_client.recv(1024)  # 1024是缓冲区大小，一般1024即可，同样recv是阻塞的
    print(f"服务端回复消息为：{recv_data.decode("UTF-8")}")

## 4.关闭链接
socket_client.close()