#include "Me.hpp"


Me getMe(const std::string& mePath) {
    std::ifstream configFile(mePath);

    if (!configFile.is_open()) {
        return Me{};
    }

    Buffer clientNameBin = getLineBin(configFile);
    ClientName clientname{0};
    std::copy(clientNameBin.begin(), clientNameBin.end(), clientname.begin());

    return Me{
        clientname,
        getLine(configFile),
        getLineBin(configFile),
    };
}

