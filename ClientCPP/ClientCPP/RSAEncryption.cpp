#include "files.h"
#include "osrng.h"
#include "base64.h"
#include "cryptlib.h"

#include "RSAEncryption.hpp"

CryptoPP::AutoSeededRandomPool rng;

void generate_keys() {
    CryptoPP::RSA::PrivateKey privKey;
    CryptoPP::RSA::PublicKey pubKey;
    privKey.GenerateRandomWithKeySize(rng, 8192);
    pubKey = CryptoPP::RSA::PublicKey(privKey);
    std::cout << "Generation ended." << std::endl;

    std::ofstream privFile("priv.key", std::ios::binary);
    CryptoPP::FileSink privSink(privFile);
    privKey.DEREncode(privSink);
    privFile.close();

    std::ofstream pubFile("public.key", std::ios::binary);
    CryptoPP::FileSink pubSink(pubFile);
    pubKey.DEREncode(pubSink);
    pubFile.close();
}


RSA::RSA(const std::string& privateKeyPath) {
    CryptoPP::RSA::PrivateKey privKey;
    std::ifstream privFile(privateKeyPath, std::ios::binary);
    CryptoPP::FileSource privSource(privFile, true);
    privKey.BERDecode(privSource);
    privFile.close();
    
    m_privKey = privKey;
    m_pubKey = CryptoPP::RSA::PublicKey(m_privKey);
}

Buffer RSA::encrypt(const Buffer& to_encrypt) {
    CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(m_pubKey);
    Buffer ciphered;
    CryptoPP::VectorSource(to_encrypt, true, new CryptoPP::PK_EncryptorFilter(rng, encryptor, new CryptoPP::VectorSink(ciphered)));

    Buffer encoded_ciphered;
    CryptoPP::VectorSource(ciphered, true, new CryptoPP::Base64Encoder(new CryptoPP::VectorSink(encoded_ciphered)));
    return encoded_ciphered;
}

Buffer RSA::decrypt(const Buffer& to_decrypt) {
    Buffer decoded_ciphered;
    CryptoPP::VectorSource(to_decrypt, true, new CryptoPP::Base64Decoder(new CryptoPP::VectorSink(decoded_ciphered)));

    Buffer recovered;
    CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(m_privKey);
    CryptoPP::VectorSource(decoded_ciphered, true, new CryptoPP::PK_DecryptorFilter(rng, decryptor, new CryptoPP::VectorSink(recovered)));

    return recovered;
}

PublicKey RSA::getPublicKey()
{
    PublicKey rsaBuffer;
    // TODO m_pubKey to buffer 

    return rsaBuffer;
}
