#include "Me.hpp"


Me getMe(const std::string& mePath) {
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
        getLineBin(configFile),
    };
}

void saveMe(const std::string& mePath, const Me& me)
{
    std::ofstream configFile(mePath);
    if (!configFile.is_open()) {
        throw std::exception("Failed to open me file");
    }

    configFile.write(reinterpret_cast<const char*>(me.name.data()), me.name.size());
    configFile.write(reinterpret_cast<const char*>(me.UUID.data()), me.UUID.size());
    configFile.write(reinterpret_cast<const char*>(me.privateKey.data()), me.privateKey.size());

    configFile.close();
}

