import struct
import config


# TOOD check client version - send 1607 if not

def unpack_and_move(format, buffer):
    result_size = struct.calcsize(format)
    result_data = buffer[:result_size]
    leftover_data = buffer[result_size:]
    
    result = struct.unpack(format, result_data)
    return leftover_data, *result


class RequestHeader:
    GENERIC_REQUEST_FORMAT = f"<{config.CLIENT_ID_SIZE}sBHL"
    HEADER_SIZE = struct.calcsize(GENERIC_REQUEST_FORMAT)
    
    def __init__(self, data) -> None:
        _, self.clientID, self.version, self.code, self.payload_size = unpack_and_move(self.GENERIC_REQUEST_FORMAT, data)

class RequestPayload:
    def __init__(self, payload) -> None:
        self.payload = payload

class Request:
    def __init__(self, header: RequestHeader, payload: RequestPayload):
        self.header = header
        self.payload = payload

class RegisterRequest(RequestPayload):
    CODE = 825
    NAME_SIZE = 255
    def __init__(self, data) -> None:
        super().__init__(data)
        self.payload, self.name = unpack_and_move(f"{self.NAME_SIZE}s", self.payload) # TODO override self.clientID?

class PublicKeyRequest(RegisterRequest):
    CODE = 826
    RSA_PUBLIC_KEY_SIZE = 160
    def __init__(self, data) -> None:
        super().__init__(data)
        self.payload , self.publicKey = unpack_and_move(f"{self.RSA_PUBLIC_KEY_SIZE}s", self.payload)


class ReConnectRequest(RegisterRequest):
    CODE = 827

class SendFileRequest(RequestPayload):
    CODE = 828
    def __init__(self, data) -> None:
        super().__init__(data)
        self.payload, self.content_size, self.original_size, self.current_chunk, self.total_chunks, self.file_name = unpack_and_move(f"LLHH{config.FILE_NAME_SIZE}s", self.payload) # 16bytes
        self.payload, self.content = unpack_and_move(f"{self.content_size}s", self.payload)

class OkCRCRequest(RequestPayload):
    CODE = 900
    FILE_NAME_SIZE = 255
    def __init__(self, data) -> None:
        super().__init__(data)
        self.payload , self.file_name = unpack_and_move(f"{self.FILE_NAME_SIZE}s", self.payload)
        
        
class BadCRCRequest(OkCRCRequest):
    CODE = 901

class FinalBadCRCRequest(OkCRCRequest):
    CODE = 902