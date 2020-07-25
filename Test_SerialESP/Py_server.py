"""
Socket programming
Server
"""

import socket
import time

HEADERSIZE = 1
GET = "GET"
INQ = "INQ"
DIS = "DIS!"
NA = ""
msg_dict = {NA:0, GET:1, INQ:2, DIS:3}

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(),5050)) # bind the socket to the local machine (ip,port)
s.listen() # can handle 5 clients at a time
print("Server is Listening...")
def response_msg(data):
    try:
        msg_num = msg_dict[data]
    except:
        msg_num = 99
    if msg_num == 0:
        return ''
    elif msg_num == 1:
        return "data\0"
    elif msg_num ==2:
        return "INQUIRY request"
    elif msg_num == 3:
        return DIS
    else:
        return "Recieved";


while True:
    client, addr = s.accept()
    print(f"Client: {addr}")
    while True:
        try:
            # receiev message from client
            msg_len_buff = client.recv(HEADERSIZE)
            msg_len = int.from_bytes(msg_len_buff, "big")
            content = client.recv(msg_len)  # string
            msg = response_msg(content.decode("utf-8"))
            if msg == DIS:

                print("Disconnecting....")
                client.close()
                break
            elif  msg == '':
                continue
            # send message to clients
            print(f"content length: {msg_len_buff}")
            print(f"Client message: {content}")
            client.send(bytes([len(msg)]))
            client.send(msg.encode("utf-8"))
        except KeyboardInterrupt:
            client.close()
            exit()
