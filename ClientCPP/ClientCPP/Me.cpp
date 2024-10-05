#include "Me.hpp"
#include "Base64.hpp"


Me Me::get(const std::string& mePath) {
    std::ifstream configFile(mePath);

    if (!configFile.is_open()) {
        return Me{};
    }

    Buffer clientNameBin = getLineBin(configFile);
    ClientName clientname{0};
    std::copy(clientNameBin.begin(), clientNameBin.end(), clientname.begin());

    std::string clientIdString = getLine(configFile);
    ClientID clientId{ 0 };
    std::copy(clientIdString.begin(), clientIdString.end(), clientId.begin());

    return Me{
        clientname,
        clientId,
        Base64::decode(getLineBin(configFile)),
    };
}

void Me::save(const Me& me, const std::string& mePath)
{
    std::ofstream configFile(mePath);
    if (!configFile.is_open()) {
        throw std::exception("Failed to open me file");
    }

    configFile << std::string(me.name.begin(), me.name.end());
    configFile << "\n";
    configFile << std::string(me.UUID.begin(), me.UUID.end());
    configFile << "\n";
    auto aesBase64 = Base64::encode(me.aesKey);
    configFile << std::string(aesBase64.begin(), aesBase64.end());

    configFile.close();
}

