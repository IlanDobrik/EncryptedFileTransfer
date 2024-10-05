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





int main(void) {
    auto transferInfo = getTransferInfo(TRANSFER_INFO_PATH);
    auto me = Me::get(ME_PATH);
    auto rsa = RSA(RSA_PRIVATE_KEY_PATH);
    auto aes = AES(Buffer());
    auto connection = std::make_unique<Connection>("127.0.0.1", "1256");

    auto client = Client(std::move(connection), rsa, aes, me, transferInfo);
    client.uploadFile("C:/Temp/a.txt");


   //{
   //     ClientID clientId {0};
   //     ClientName clientName{0};
   //     RegisterRequest rr(clientId, clientName);

   //     auto out = rr.serialize();
   //     std::cout << out.size();
   //}

   // // generate_keys();
   // std::string message = "Hello yuval";
   // 
   // {
   //     RSA rsa(RSA_PRIVATE_KEY_PATH);
   //     Buffer encrypted = rsa.encrypt(Buffer(message.begin(), message.end()));
   //     Buffer decrypted = rsa.decrypt(encrypted);

   //     std::string x = std::string(decrypted.begin(), decrypted.end());
   // }

   // {
   //     AES aes(Buffer(IV_SIZE, 1), Buffer(IV_SIZE, 0));
   //     Buffer encrypted = aes.encrypt(Buffer(message.begin(), message.end()));
   //     Buffer decrypted = aes.decrypt(encrypted);

   //     std::string x = std::string(decrypted.begin(), decrypted.end());
   // }


    return 0;
};
