import threading
import socket
import logging

from CryptoUtils import SymetricKey
from cksum import memcrc


class ClientThread(threading.Thread):
    def __init__(self, clientAddress: socket.socket, clientsocket: socket.AddressInfo):
        threading.Thread.__init__(self, daemon=True)
        self.csocket = clientsocket
        self.caddress = clientAddress

    def key_exchange(self):
        public_rsa_key = self.csocket.recv(32).decode()
        symetric_key = SymetricKey(public_rsa_key)
        self.csocket.send(symetric_key.get_encrypted_session_key())

    def register(self):
        pass

    def run(self):
        try:
            res = self.csocket.recv(1024).decode()
            # Registration is
            self.key_exchange()
            
            # State machine
            
            
        except Exception as e:
            logging.error("Caught exception {e}")