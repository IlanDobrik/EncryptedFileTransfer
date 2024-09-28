#include "AESEncryption.hpp"

#include "aes.h"
#include "rng.h"
#include "base64.h"
#include "modes.h"


static constexpr size_t AES_KEY_SIZE = 256 / 8;
static constexpr size_t IV_SIZE = 256 / 8;


AES::AES(const Buffer& key, const Buffer& iv = Buffer(0, IV_SIZE)) :
    m_key(key), m_iv(iv)
{ }

Buffer AES::encrypt(const Buffer& input) {
    Buffer cipher;

    auto aes = CryptoPP::AES::Encryption(m_key.data(), m_key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Encryption(aes, m_iv.data());

    CryptoPP::VectorSource vs(
        input,
        true,
        new CryptoPP::StreamTransformationFilter(
            aes_cbc,
            new CryptoPP::Base64Encoder(
                new CryptoPP::VectorSink(cipher)
            )
        )
    );

    return cipher;
}

Buffer AES::decrypt(const Buffer& cipher_text) {
    Buffer plain_text;

    auto aes = CryptoPP::AES::Decryption(m_key.data(), m_key.size());
    auto aes_cbc = CryptoPP::CBC_Mode_ExternalCipher::Decryption(aes, m_iv.data());

    CryptoPP::VectorSource ss(
        cipher_text,
        true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StreamTransformationFilter(
                aes_cbc,
                new CryptoPP::VectorSink(plain_text)
            )
        )
    );

    return plain_text;
}
