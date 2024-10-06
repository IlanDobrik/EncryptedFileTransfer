import threading
import socket
import logging

from CryptoUtils import SymetricKey
import Utils
from cksum import memcrc

import Requests
import Responses
from DB import DB


class ClientThread(threading.Thread):
    def __init__(self, db, clientAddress: socket.socket, clientsocket: socket.AddressInfo):
        threading.Thread.__init__(self, daemon=True)
        self.db : DB = db
        self.csocket: socket.socket = clientsocket
        self.caddress = clientAddress
    
    def send_aes(self, request: Requests.PublicKeyRequest):
        symetric_key = SymetricKey(request.publicKey).get_encrypted_session_key()
        response = Responses.EncryptedAESResponse(request.clientID, symetric_key)
        self.csocket.sendall(response.pack())
        self.db.insert(request.clientID, request.name, symetric_key)

    def register(self, request : Requests.RegisterRequest):
        if self.db.exists(request.name):
            response = Responses.FailedRegisterResponse()
        else:
            client_id = Utils.generateUUID().encode()
            response = Responses.SuccessfulRegisterResponse(client_id)
            self.db.insert(client_id, request.name, "")
        self.csocket.sendall(response.pack())

    def reconnect(self, request: Requests.ReConnectRequest):
        client_id = request.clientID
        if not self.db.exists(client_id):
            response = Responses.RejectedReconnectResponse(client_id)
        else:
            public_key, aes_key = self.db.get(client_id)
            symetric_key = SymetricKey(public_key, aes_key).get_encrypted_session_key()
            response = Responses.SuccessfulReconnectResponse(client_id, symetric_key)
        
        self.csocket.sendall(response.pack())

    def run(self):
        try:
            while True:
                # TODO read header, then payload
                data = self.csocket.recv(1024) # TODO on connection close, this returns b''
                request = Requests.Request(data)
                # TODO command factory
                if request.code == Requests.RegisterRequest.CODE:
                    self.register(Requests.RegisterRequest(data))
                elif request.code == Requests.PublicKeyRequest.CODE:
                    self.send_aes(Requests.PublicKeyRequest(data))
                elif request.code == Requests.ReConnectRequest.CODE:
                    self.reconnect(Requests.ReConnectRequest(data))
                # TODO add reconnect
                # TODO add file recive
        except Exception as e:
            logging.error(f"Caught exception {e}")