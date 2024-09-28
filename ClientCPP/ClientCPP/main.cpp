#include "TransferInfo.hpp"
#include "Me.hpp"


#define TRANSFER_INFO_PATH "./transfer.info"
#define ME_PATH "./me.info"
#define RSA_PRIVATE_KEY_PATH "./priv.key"


#include "RSAEncryption.hpp"
#include "Base64.hpp"
#include "AESEncryption.hpp"


int main(void) {
    auto config = getTransferInfo(TRANSFER_INFO_PATH);
    auto me = getMe(ME_PATH);

    // generate_keys();
    std::string message = "Hello yuval";
    
    {
        RSA rsa(RSA_PRIVATE_KEY_PATH);
        Buffer encrypted = rsa.encrypt(Buffer(message.begin(), message.end()));
        Buffer decrypted = rsa.decrypt(encrypted);

        std::string x = std::string(decrypted.begin(), decrypted.end());
    }

    {
        AES aes(Buffer(IV_SIZE, 1), Buffer(IV_SIZE, 0));
        Buffer encrypted = aes.encrypt(Buffer(message.begin(), message.end()));
        Buffer decrypted = aes.decrypt(encrypted);

        std::string x = std::string(decrypted.begin(), decrypted.end());
    }


    return 0;
};
