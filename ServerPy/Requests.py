import struct


class Request:
    GENERIC_REQUEST_FORMAT = "2QBHL"
    
    def __init__(self, data) -> None:
        self.clientID, self.version, self.code, self.payload_size = struct.unpack(self.GENERIC_REQUEST_FORMAT, data) # 16bytes
        
        offset = struct.calcsize(self.GENERIC_REQUEST_FORMAT)
        self.payload = struct.unpack(f"{self.payload_size}s", data[offset:])

class RegisterRequest(Request):
    NAME_SIZE = 255
    def __init__(self, data) -> None:
        super().__init__(data)

        self.name = struct.unpack(f"{self.NAME_SIZE}s", self.payload)


class CommandRemoveFile:
    execute(params)

class CommandFactory:
    getCommand("Help")
    getCommand("remove file")

    commands = {"rm", CommandRemoveFile}

class Terminal:
    __init__(CommandsFactory)