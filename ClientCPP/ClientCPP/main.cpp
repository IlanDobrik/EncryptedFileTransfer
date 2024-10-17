#include <array>
#include <memory>

#include "Common.h"
#include "Hardcoded.h"

#include "TransferInfo.h"
#include "Me.h"

#include "RSAEncryption.h"
#include "AESEncryption.h"
#include "Base64.h"

#include "Connection.h"
#include "Client.h"



RSA getRSA() {
    try {
        return RSA(RSA_PRIVATE_KEY_PATH);
    }
    catch (...)
    {
        generate_keys(RSA_PRIVATE_KEY_PATH);
    }
    return RSA(RSA_PRIVATE_KEY_PATH);
}

int main(void) {
    try {
        auto transferInfo = getTransferInfo(TRANSFER_INFO_PATH);
        auto me = Me::get(ME_PATH);
        auto rsa = getRSA();
        auto connection = std::make_unique<Connection>(transferInfo.ipAddress.ip, transferInfo.ipAddress.port);
        auto logger = std::make_unique<ILogger>();

        auto client = Client(std::move(connection), std::move(logger), rsa, me, transferInfo);
        client.run(transferInfo.filePath);
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }

    return 0;
};
