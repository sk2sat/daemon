#!/usr/bin/env python3
import socket
host = "127.0.0.1"
port = 12345

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((host,port))
client.send("hello!")
re = client.recv(4096)
print(re)
