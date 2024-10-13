#include "TransferInfo.h"
#include "Common.h"


IPAddress getIP(std::ifstream& transferInfoFile) {
    std::string line = getLine(transferInfoFile);
    
    std::string port = line.substr(line.find(':') + 1).c_str();
    std::string ip = line.substr(0, line.find(':'));

    return IPAddress{ ip, port };
}

ClientName getClientName(std::ifstream& transferInfoFile) {
    Buffer clientNameBin = getLineBin(transferInfoFile);
    ClientName clientname{0};
    std::copy(clientNameBin.begin(), clientNameBin.end(), clientname.begin());

    return clientname;
}


TransferInfo getTransferInfo(const std::string& transferInfoPath) {
    std::ifstream transferInfoFile(transferInfoPath);

    if (!transferInfoFile.is_open()) {
        throw std::exception("Failed to open file. Check path");
    }

    return TransferInfo{
        getIP(transferInfoFile),
        getClientName(transferInfoFile),
        getLine(transferInfoFile),
    };
}
