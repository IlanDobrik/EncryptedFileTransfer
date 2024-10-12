import uuid

def generateUUID() -> bytes:
    return bytes.fromhex(uuid.uuid4().hex)
