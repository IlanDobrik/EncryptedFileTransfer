from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Util.Padding import pad, unpad


class SymetricKey:
    def __init__(self, public_rsa_key, aes_key : bytes =b"") -> None:
        self.public_rsa_key = public_rsa_key
        self.session_key = aes_key if aes_key != b"" else get_random_bytes(32)
    
    def decrypt(self, ciphertext):
        cipher_aes = AES.new(self.session_key, AES.MODE_CBC, iv=b'\x00'*16)
        return unpad(cipher_aes.decrypt(ciphertext), 16)

    def get_encrypted_session_key(self):
        cipher_rsa = PKCS1_OAEP.new(RSA.import_key(self.public_rsa_key))
        return cipher_rsa.encrypt(self.session_key)
