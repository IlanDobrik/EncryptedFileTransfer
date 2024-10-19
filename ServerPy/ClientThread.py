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
        self.csocket: socket.socket = clientsocket
        self.caddress = clientAddress
        
        self.db : DB = db
        self.client_id : bytes = None
        self.client_name : bytes = None
        self.symetric_key = None
        logging.info(f"Recived connection from {clientAddress}")
        
    def validate(self, header: Requests.RequestHeader):
        if self.client_id != header.clientID:
            raise "Different client id"
    
    def register(self, header: Requests.RequestHeader, payload : Requests.RegisterRequest):
        if self.db.exists(payload.name):
            response = Responses.FailedRegisterResponse()
            logging.info(f"Client {payload.name.strip(b"\x00")} failed to register")
        else:
            client_id = Utils.generateUUID()
            response = Responses.SuccessfulRegisterResponse(client_id)
            self.client_id, self.client_name = client_id, payload.name
            self.db.insert_client(header.clientID, payload.name, b'', b'')
            logging.info(f"Client {payload.name.strip(b"\x00")} with id {client_id} registered successfuly")
        self.csocket.sendall(response.pack())
        
    def send_aes(self, header: Requests.RequestHeader, payload: Requests.PublicKeyRequest):
        self.validate(header)
        self.symetric_key = SymetricKey(payload.publicKey)
        response = Responses.EncryptedAESResponse(header.clientID, self.symetric_key.get_encrypted_session_key())
        self.csocket.sendall(response.pack())
        self.db.insert_client(header.clientID, payload.name, payload.publicKey, self.symetric_key.session_key)

    def reconnect(self, header: Requests.RequestHeader, payload: Requests.ReConnectRequest):
        client_id = header.clientID
        if not self.db.exists(client_id):
            response = Responses.RejectedReconnectResponse(client_id)
            logging.info(f"Client {client_id}: failed to reconnect")
        else:
            client = self.db.get_client(client_id)
            self.symetric_key = SymetricKey(client.public_key)
            response = Responses.SuccessfulReconnectResponse(client_id, self.symetric_key.get_encrypted_session_key())
            self.client_id = client_id
            logging.info(f"Client {client_id}: reconnected successfuly")
        self.csocket.sendall(response.pack())

    def generalFailure(self):
        logging.info(f"General failure")
        self.csocket.sendall(Responses.GeneralFailureResponse().pack())

    def get_file(self, header: Requests.RequestHeader, payload: Requests.SendFileRequest):
        self.validate(header)
        # TODO if no symetric key = fail
        content = self.symetric_key.decrypt(payload.content)
        file_name = payload.file_name.strip(b"\x00")
        
        logging.info(f"Client {header.clientID}: uploding {file_name} {payload.current_chunk}/{payload.total_chunks}")

        with open(file_name, "ba+") as f:
            f.write(content)
            
        if payload.current_chunk == payload.total_chunks:
            with open(file_name, "rb") as f:
                content = f.read()
            checksum = memcrc(content)
            logging.info(f"Client {header.clientID}: finished uploding {file_name}. checksum {checksum}")
            response = Responses.CRCResponse(self.client_id, content.__len__(), file_name, checksum)
            self.csocket.sendall(response.pack())

    def OkCrc(self, header: Requests.RequestHeader, payload: Requests.OkCRCRequest):
        self.validate(header)
        logging.info(f"Client {header.clientID}: Checksum verified for {payload.file_name.strip(b"\x00")}")
        self.finish()

    def BadCrc(self, header: Requests.RequestHeader, payload: Requests.BadCRCRequest):
        self.validate(header)
        logging.info(f"Client {header.clientID}: Checksum not verified for {payload.file_name.strip(b"\x00")}")
    
    def FinalBadCrc(self, header: Requests.RequestHeader, payload: Requests.FinalBadCRCRequest):
        self.validate(header)
        logging.info(f"Client {header.clientID}: Checksum not verified for {payload.file_name.strip(b"\x00")} for the final time. Closing connection")
        self.finish()
        
    def finish(self):
        self.csocket.sendall(Responses.AckResponse(self.client_id).pack())

    def run(self):
        try:
            while True:
                data = self.csocket.recv(Requests.RequestHeader.HEADER_SIZE)
                if len(data) == 0:
                    # Client disconnected
                    return
                header = Requests.RequestHeader(data)
                payload = self.csocket.recv(header.payload_size)
                
                # TODO command factory
                if header.code == Requests.RegisterRequest.CODE:
                    self.register(header, Requests.RegisterRequest(payload))
                elif header.code == Requests.PublicKeyRequest.CODE:
                    self.send_aes(header, Requests.PublicKeyRequest(payload))
                elif header.code == Requests.ReConnectRequest.CODE:
                    self.reconnect(header, Requests.ReConnectRequest(payload))
                elif header.code == Requests.SendFileRequest.CODE:
                    self.get_file(header, Requests.SendFileRequest(payload))
                
                elif header.code == Requests.OkCRCRequest.CODE:
                    self.OkCrc(header, Requests.OkCRCRequest(payload))
                elif header.code == Requests.BadCRCRequest.CODE:
                    self.BadCrc(header, Requests.BadCRCRequest(payload))
                elif header.code == Requests.FinalBadCRCRequest.CODE:
                    self.FinalBadCrc(header, Requests.FinalBadCRCRequest(payload))
        except ConnectionResetError as e:
            logging.error(f"Client disconnected {self.caddress}")
        except Exception as e:
            self.generalFailure()
            logging.error(f"Caught exception {e}")
