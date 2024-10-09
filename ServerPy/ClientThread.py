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
        self.client_id = None
        self.symetric_key = None
    
    def send_aes(self, request: Requests.PublicKeyRequest):
        self.symetric_key = SymetricKey(request.publicKey)
        response = Responses.EncryptedAESResponse(request.clientID, self.symetric_key.get_encrypted_session_key())
        self.csocket.sendall(response.pack())
        self.db.insert(request.clientID, request.name, request.publicKey)

    def register(self, request : Requests.RegisterRequest):
        if self.db.exists(request.name):
            response = Responses.FailedRegisterResponse()
        else:
            client_id = Utils.generateUUID().encode()
            response = Responses.SuccessfulRegisterResponse(client_id)
            self.client_id = client_id
            self.db.insert(client_id, request.name, b"")
        self.csocket.sendall(response.pack())

    def reconnect(self, request: Requests.ReConnectRequest):
        # TODO no clientID - search by name
        client_id = request.clientID
        if not self.db.exists(client_id):
            response = Responses.RejectedReconnectResponse(client_id)
            # TODO register the client - cause we need to generate clientId, which means we are sigining him
        else:
            public_key = self.db.get(client_id)
            self.symetric_key = SymetricKey(public_key)
            response = Responses.SuccessfulReconnectResponse(client_id, self.symetric_key.get_encrypted_session_key())
            self.client_id = client_id
        self.csocket.sendall(response.pack())

    def generalFailure(self):
        self.csocket.sendall(Responses.GeneralFailureResponse().pack())

    def get_file(self, request: Requests.SendFileRequest):
        # TODO if no symetric key = fail
        
        content = self.symetric_key.decrypt(request.content)
        file_name = request.file_name

        while request.current_chunk != request.total_chunks:
            data = self.csocket.recv(1024)
            request = Requests.Request(data)
            if request.code != Requests.SendFileRequest.CODE:
                self.generalFailure()
            request = Requests.SendFileRequest(request)
            content += self.symetric_key.decrypt(request.content)[:request.original_size]

        response = Responses.CRCResponse(self.client_id, content.__len__(), file_name, memcrc(content))
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
                elif request.code == Requests.SendFileRequest.CODE:
                    self.get_file(Requests.SendFileRequest(data))
                # TODO add file recive
        except Exception as e:
            self.generalFailure()
            logging.error(f"Caught exception {e}")