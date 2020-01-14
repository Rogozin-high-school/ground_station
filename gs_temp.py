import socket
import sys
import array

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('0.0.0.0', 8888))
sock.listen(1)
while True:
    con, addr = sock.accept()
    print("Connected!")
    while True:
        msg = input("Enter byte to send: ")
        if msg == 'x':
            con.close()
            break
        con.send((int(msg)).to_bytes(1, 'big'))
    print("Lost connection")