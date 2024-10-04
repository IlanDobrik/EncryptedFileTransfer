import threading
import socket
import logging

from CryptoUtils import SymetricKey
import Utils
from cksum import memcrc

import Requests
import Responses


class ClientThread(threading.Thread):
    def __init__(self, clientAddress: socket.socket, clientsocket: socket.AddressInfo):
        threading.Thread.__init__(self, daemon=True)
        self.csocket: socket.socket = clientsocket
        self.caddress = clientAddress

    def key_exchange(self):
        public_rsa_key = self.csocket.recv(32).decode()
        symetric_key = SymetricKey(public_rsa_key)
        self.csocket.send(symetric_key.get_encrypted_session_key())
        
    def send_aes(self, request: Requests.PublicKeyRequest):
        symetric_key = SymetricKey(request.publicKey)
        response = Responses.EncryptedAESResponse(request.clientID, symetric_key.get_encrypted_session_key())
        self.csocket.send(response.pack())

    def register(self):
        response = Responses.SuccessfulRegisterResponse(Utils.generateUUID().encode())
        self.csocket.sendall(response.pack())

    def run(self):
        try:
            while True:
                request = Requests.Request(self.csocket.recv(1024))
                if request.code == Requests.RegisterRequest.CODE:
                    self.register()
                if request.code == Requests.PublicKeyRequest.CODE:
                    self.send_aes(request)
                    
        except Exception as e:
            logging.error("Caught exception {e}")