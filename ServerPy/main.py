import logging
import socket

from config import read_config
from ClientThread import ClientThread
import DB
import Utils


def listen4clients(listenPort):
    # creating listen socket
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('', listenPort))
    logging.info(f"Sarted listening on port {listenPort}")

    db = DB.DB()

    # creating client sockets    
    while True:
        server.listen(1)
        clientsock, clientAddress = server.accept()
        newthread = ClientThread(db, clientAddress, clientsock)
        newthread.start()

def main():
    logging.getLogger().setLevel(logging.INFO)
    
    config = read_config()
    listen4clients(config.port)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        logging.info("Shutting Down")
