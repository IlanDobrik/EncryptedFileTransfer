from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Hash import HMAC, SHA256

class SymetricKey:
    def __init__(self, public_rsa_key) -> None:
        self.public_rsa_key = public_rsa_key
        self.session_key = get_random_bytes(16)
        self.cipher_aes = AES.new(self.session_key, AES.MODE_EAX)

    def encrypt(self, data):
        return self.cipher_aes.encrypt_and_digest(data) 
    
    def decrypt(self, ciphertext, tag, nonce):
        cipher_aes = AES.new(self.session_key, AES.MODE_EAX, nonce)
        return cipher_aes.decrypt_and_verify(ciphertext, tag)

    def get_encrypted_session_key(self):
        cipher_rsa = PKCS1_OAEP.new(self.public_rsa_key)
        return cipher_rsa.encrypt(self.session_key)
