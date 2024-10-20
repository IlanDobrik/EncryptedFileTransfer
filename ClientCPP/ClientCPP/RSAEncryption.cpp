#include "cryptopp\files.h"
#include "cryptopp\osrng.h"
#include "cryptopp\cryptlib.h"

#include "RSAEncryption.h"
#include "ClientException.h"


CryptoPP::AutoSeededRandomPool rng;

void generate_keys(const std::string& privatePath) {
    CryptoPP::RSA::PrivateKey privKey;
    CryptoPP::RSA::PublicKey pubKey;
    privKey.Initialize(rng, 1024);
    pubKey = CryptoPP::RSA::PublicKey(privKey);

    std::ofstream privFile(privatePath, std::ios::binary);
    CryptoPP::FileSink privSink(privFile);
    privKey.DEREncode(privSink);
    privFile.close();
}


RSA::RSA(const std::string& privateKeyPath) {
    CryptoPP::RSA::PrivateKey privKey;
    std::ifstream privFile(privateKeyPath, std::ios::binary);
    if (!privFile.is_open()) {
        throw ClientException("Failed to open private key file");
    }

    CryptoPP::FileSource privSource(privFile, true);
    privKey.BERDecode(privSource);
    privFile.close();
    
    m_privKey = privKey;
    m_pubKey = CryptoPP::RSA::PublicKey(m_privKey);
}

Buffer RSA::encrypt(const Buffer& to_encrypt) {
    Buffer ciphered;
    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(m_pubKey);
    CryptoPP::VectorSource(to_encrypt, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::VectorSink(ciphered)));
    return ciphered;
}

Buffer RSA::decrypt(const Buffer& to_decrypt) {
    Buffer recovered;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(m_privKey);
    CryptoPP::VectorSource(to_decrypt, true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::VectorSink(recovered)));

    return recovered;
}

PublicKey RSA::getPublicKey()
{
    PublicKey rsaBuffer;

    CryptoPP::ArraySink as(rsaBuffer.data(), rsaBuffer.size());
    m_pubKey.Save(as);
    return rsaBuffer;
}
