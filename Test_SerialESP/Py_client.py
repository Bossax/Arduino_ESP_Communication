"""
Testing communication with arduino via ESP01
using client
"""

import socket

HEADERSIZE = 1 #  byte
FORMAT = "utf-8"
PORT = 5050
SERVER = "192.168.1.131"
ADDR = (SERVER,PORT)
DISCONNECT_MESSAGE = "!DISCONNECT"
GET_MSG = "TCP_GET"


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
print(f"Connected to server {SERVER}\n")


def getResponse():
    full_msg = ''
    new_msg = True
    while True:
        # first packet of a new string
        # extract header
        if new_msg:
            msg_len_buffer = client.recv(HEADERSIZE)
            msg_len = int.from_bytes(msg_len_buffer, byteorder='big')
            print(f"new massege length:{msg_len}\n")
            new_msg = False
            continue
        msg = client.recv(msg_len)   # 8-byte  size of chunk
        full_msg += msg.decode(FORMAT)
        print(f"Server mesage: \n{full_msg}\n")
        break;

def sendMSG(msg):

    message = msg.encode(FORMAT)
    msg_length = len(message)

    # print(f"sending a message: {message} with length:{bytes([msg_length])}")
    # send message
    print(bytes([5]))
    client.send(bytes([5]))
    # client.send(bytes([msg_length]))
    # client.send(message)
    getResponse()


sendMSG("Hello")
input()
sendMSG(GET_MSG)
input()
sendMSG(DISCONNECT_MESSAGE)
