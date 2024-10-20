#include "Me.h"

#include <filesystem>
#include <boost/algorithm/hex.hpp>

#include "Common.h"
#include "Base64.h"
#include "File.h"




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
    if (!std::filesystem::exists(mePath)) {
        return Me{};
    }

    File configFile(mePath, std::ios_base::in);

    auto clientname = convertTo<ClientName>(configFile.getLineBin());
    clientname[clientname.size() - 1] = 0; // Ensure null terminator

    std::string clientIdString = configFile.getLine();
    if (!clientIdString.empty()) {
        clientIdString = boost::algorithm::unhex(clientIdString);
    }
    auto clientId = convertTo<ClientID>(clientIdString);

    return Me{
        clientname,
        clientId,
        Base64::decode(configFile.getLineBin()),
    };
}

void Me::save(const Me& me, const std::string& mePath)
{
    File configFile(mePath, std::ios_base::out);
    
    configFile.write(removeNulls(std::string(me.name.begin(), me.name.end())));
    configFile.write("\n");
    configFile.write(boost::algorithm::hex(std::string(me.UUID.begin(), me.UUID.end())));
    configFile.write("\n");
    auto aesBase64 = Base64::encode(me.WTF_IS_THIS);
    configFile.write(std::string(aesBase64.begin(), aesBase64.end()));
}
