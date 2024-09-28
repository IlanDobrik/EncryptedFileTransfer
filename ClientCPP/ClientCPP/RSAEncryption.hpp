#include <vector>

#include "rsa.h"
#include "common.hpp"


class RSA {
public:
    RSA(const std::string& privateKeyPath);
    Buffer encrypt(const Buffer& to_encrypt);
    Buffer decrypt(const Buffer& to_decrypt);

private:
    CryptoPP::RSA::PrivateKey m_privKey;
    CryptoPP::RSA::PublicKey m_pubKey;
};

void generate_keys();
