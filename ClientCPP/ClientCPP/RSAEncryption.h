#pragma once

#include <vector>

#include "cryptopp\rsa.h"
#include "common.h"
#include "Hardcoded.h"


class RSA {
public:
    RSA(const std::string& privateKeyPath);
    Buffer encrypt(const Buffer& to_encrypt);
    Buffer decrypt(const Buffer& to_decrypt);

    PublicKey getPublicKey();

private:
    CryptoPP::RSA::PrivateKey m_privKey;
    CryptoPP::RSA::PublicKey m_pubKey;
};

void generate_keys(const std::string& privatePath);
