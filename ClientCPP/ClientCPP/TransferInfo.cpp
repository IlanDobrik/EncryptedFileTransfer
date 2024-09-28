#include "TransferInfo.hpp"
#include "Common.hpp"


IPAddress getIP(std::ifstream& transferInfoFile) {
    std::string line = getLine(transferInfoFile);
    
    uint32_t port = std::atoi(line.substr(line.find(':') + 1).c_str());
    std::string ip = line.substr(0, line.find(':'));

    return IPAddress{ ip, port };
}


TransferInfo getTransferInfo(const std::string& transferInfoPath) {
    std::ifstream configFile(transferInfoPath);

    if (!configFile.is_open()) {
        throw std::exception("Failed to open file. Check path");
    }

    return TransferInfo{
        getIP(configFile),
        getLine(configFile),
        getLine(configFile),
    };
}
