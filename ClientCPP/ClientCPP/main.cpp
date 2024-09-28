#include "TransferInfo.hpp"
#include "Me.hpp"

#include "RSAEncryption.hpp"

#define TRANSFER_INFO_PATH "./transfer.info"
#define ME_PATH "./me.info"
#define RSA_PRIVATE_KEY_PATH "./priv.key"


#include "Base64.hpp"


int main(void) {
    auto config = getTransferInfo(TRANSFER_INFO_PATH);
    auto me = getMe(ME_PATH);

    // generate_keys();
    
    RSA rsa(RSA_PRIVATE_KEY_PATH);

    std::string message = "Hello yuval";

    Buffer encrypted = rsa.encrypt(Buffer(message.begin(), message.end()));
    Buffer decrypted = rsa.decrypt(encrypted);

    std::string x = std::string(decrypted.begin(), decrypted.end());



    return 0;
};
