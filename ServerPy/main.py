import threading
import os
import logging
import socket

import Config
from ClientThread import ClientThread, Request


def listen4clients(listenPort):
    # creating listen socket
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('', listenPort))
    logging.info(f"Sarted listening on port {listenPort}")

    # creating client sockets    
    while True:
        server.listen(1)
        clientsock, clientAddress = server.accept()
        newthread = ClientThread(clientAddress, clientsock)
        newthread.start()

def loadPort():
    if not os.path.exists(Config.PORT_INFO_PATH):
        logging.error(f"Port file in path {Config.PORT_INFO_PATH} not found")
        return 1256
    
    with open(Config.PORT_INFO_PATH, "r") as portFile:
        return portFile.readline()

def main():
    r = Request(b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x02\x00\x00\x00\x01\x00')
    config = Config.read_config()
    listen4clients(config.port)
    # t = threading.Thread(target=listen4clients, args=(loadPort()))
    # t.start()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        logging.info("Shutting Down")
