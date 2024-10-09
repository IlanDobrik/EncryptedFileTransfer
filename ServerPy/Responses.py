import struct

import config

class Response:
    RESPONSE_FORMAT = f"<BHL"
    CODE = 0
    
    def __init__(self) -> None:
        pass
        
    def pack(self, payload: bytes = b""):
        return struct.pack(self.RESPONSE_FORMAT, config.SERVER_VERSION, self.CODE, payload.__len__()) + payload


class WithClientID(Response):    
    def __init__(self, client_id) -> None:
        payload_format = f"{config.CLIENT_ID_SIZE}s"
        self.payload_size = struct.calcsize(payload_format)
        self.payload = struct.pack(payload_format, client_id)
        
    def pack(self, payload: bytes =b""):
        return super().pack(self.payload + payload)


class SuccessfulRegisterResponse(WithClientID):
    CODE = 1600
        
class FailedRegisterResponse(Response):
    CODE = 1601

class EncryptedAESResponse(WithClientID):
    CODE = 1602
    
    def __init__(self, client_id, aes_key) -> None:
        super().__init__(client_id)
        self.aes_key = aes_key
    
    def pack(self):
        return super().pack(self.aes_key)

class CRCResponse(WithClientID):
    CODE = 1603
    PAYLOAD_FORMAT = f"<L{config.FILE_NAME_SIZE}sL"
    def __init__(self, client_id, content_size, file_name, checksum) -> None:
        super().__init__(client_id)
        self.content_size = content_size
        self.file_name = file_name
        self.checksum = checksum
    
    def pack(self):
        return super().pack(struct.pack(self.PAYLOAD_FORMAT, self.content_size, self.file_name, self.checksum))

class AckResponse(WithClientID):
    CODE = 1604

class SuccessfulReconnectResponse(EncryptedAESResponse):
    CODE = 1605
    
class RejectedReconnectResponse(WithClientID):
    CODE = 1606
    
class GeneralFailureResponse(Response):
    CODE = 1607
