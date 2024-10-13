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
    

'''
import base64
import hashlib
from Crypto import Random
from Crypto.Cipher import AES

class AESCipher(object):

    def __init__(self, key):
        self.bs = AES.block_size
        self.key = hashlib.sha256(key.encode()).digest()

    def encrypt(self, raw):
        raw = self._pad(raw)
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return base64.b64encode(iv + cipher.encrypt(raw.encode()))

    def decrypt(self, enc):
        enc = base64.b64decode(enc)
        iv = enc[:AES.block_size]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return AESCipher._unpad(cipher.decrypt(enc[AES.block_size:])).decode('utf-8')

    def _pad(self, s):
        return s + (self.bs - len(s) % self.bs) * chr(self.bs - len(s) % self.bs)

    @staticmethod
    def _unpad(s):
        return s[:-ord(s[len(s)-1:])]
'''