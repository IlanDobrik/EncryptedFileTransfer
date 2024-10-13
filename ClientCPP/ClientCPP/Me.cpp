#include "Me.h"
#include "Base64.h"

#include <boost/algorithm/hex.hpp>


void Me::reset()
{
    *this = Me{};
}

bool Me::isEmpty()
{
    // checks if UUID is empty
    for (const auto& b : UUID) {
        if (b != 0)
        {
            return false;
        }
    }

    return true;
}

Me Me::get(const std::string& mePath) {
    std::ifstream configFile(mePath);

    if (!configFile.is_open()) {
        return Me{};
    }

    Buffer clientNameBin = getLineBin(configFile);
    ClientName clientname{0};
    std::copy(clientNameBin.begin(), clientNameBin.end(), clientname.begin());

    std::string clientIdString = getLine(configFile);
    if (!clientIdString.empty()) {
        clientIdString = boost::algorithm::unhex(clientIdString);
    }
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

    configFile << removeNulls(std::string(me.name.begin(), me.name.end()));
    configFile << "\n";
    configFile <<  boost::algorithm::hex(std::string(me.UUID.begin(), me.UUID.end()));
    configFile << "\n";
    auto aesBase64 = Base64::encode(me.WTF_IS_THIS);
    configFile << std::string(aesBase64.begin(), aesBase64.end());

    configFile.close();
}
