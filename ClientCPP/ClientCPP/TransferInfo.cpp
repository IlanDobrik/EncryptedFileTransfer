#include "TransferInfo.hpp"


IPAddress getIP(std::ifstream& transferInfoFile) {
    std::string line;
    std::getline(transferInfoFile, line);

    uint32_t port = std::atoi(line.substr(line.find(':') + 1).c_str());
    std::string ip = line.substr(0, line.find(':'));

    return IPAddress{ ip, port };
}

std::string getClientName(std::ifstream& transferInfoFile) {
    std::string line;
    std::getline(transferInfoFile, line);

    return line;
}

std::string getFilePath(std::ifstream& transferInfoFile) {
    std::string line;
    std::getline(transferInfoFile, line);

    return line;
}

TransferInfo getTransferInfo(const std::string& transferInfoPath) {
    std::ifstream configFile(transferInfoPath);

    if (!configFile.is_open()) {
        throw std::exception("Failed to open file. Check path");
    }

    return TransferInfo{
        getIP(configFile),
        getClientName(configFile),
        getFilePath(configFile),
    };
}
