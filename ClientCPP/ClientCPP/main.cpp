#include <array>
#include <memory>
#include <iostream>

#include "Common.h"
#include "Hardcoded.h"

#include "TransferInfo.h"
#include "Me.h"

#include "RSAEncryption.h"
#include "AESEncryption.h"
#include "Base64.h"

#include "Connection.h"
#include "Client.h"

#include "CLILogger.h"



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
        auto logger = std::make_unique<CLILogger>();
        auto file = std::make_unique<File>(transferInfo.filePath, std::ios_base::binary | std::ios_base::in);

        auto client = Client(std::move(connection), std::move(logger), std::move(file), rsa, me, transferInfo);
        client.run();
    }
    catch (const std::exception& e) {
        std::cout << "Unkown exception: " << e.what();
    }

    return 0;
};
