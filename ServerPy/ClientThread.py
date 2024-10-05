import threading
import socket
import logging

from CryptoUtils import SymetricKey
import Utils
from cksum import memcrc

import Requests
import Responses


class ClientThread(threading.Thread):
    def __init__(self, db, clientAddress: socket.socket, clientsocket: socket.AddressInfo):
        threading.Thread.__init__(self, daemon=True)
        self.db = db
        self.csocket: socket.socket = clientsocket
        self.caddress = clientAddress
    
    def send_aes(self, request: Requests.PublicKeyRequest):
        symetric_key = SymetricKey(request.publicKey).get_encrypted_session_key()
        response = Responses.EncryptedAESResponse(request.clientID, symetric_key)
        self.csocket.sendall(response.pack())
        self.db.insert(request.clientID, symetric_key)

    def register(self):
        client_id = Utils.generateUUID().encode()
        response = Responses.SuccessfulRegisterResponse(client_id)
        self.csocket.sendall(response.pack())
        self.db.insert(client_id, "")

    def run(self):
        try:
            while True:
                # TODO read header, then payload
                data = self.csocket.recv(1024) # TODO on connection close, this returns b''
                request = Requests.Request(data)
                if request.code == Requests.RegisterRequest.CODE:
                    self.register()
                if request.code == Requests.PublicKeyRequest.CODE:
                    self.send_aes(Requests.PublicKeyRequest(data))
                    
        except Exception as e:
            logging.error(f"Caught exception {e}")