#include <array>
#include <memory>

#include "Common.hpp"
#include "Hardcoded.h"

#include "TransferInfo.hpp"
#include "Me.hpp"

#include "RSAEncryption.hpp"
#include "AESEncryption.hpp"
#include "Base64.hpp"

#include "Connection.h"
#include "Client.h"

#include <iostream>


int main(void) {
    try {
        auto transferInfo = getTransferInfo(TRANSFER_INFO_PATH);
        auto me = Me::get(ME_PATH);
        auto rsa = RSA(RSA_PRIVATE_KEY_PATH);
        auto aes = AES(Buffer());
        auto connection = std::make_unique<Connection>(transferInfo.ipAddress.ip, transferInfo.ipAddress.port);

        auto client = Client(std::move(connection), rsa, aes, me, transferInfo);
        client.run(transferInfo.filePath);
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }

    return 0;
};
