#include "TransferInfo.h"
#include "Common.h"

#include "File.h"

IPAddress getIP(File& transferInfoFile) {
    std::string line = transferInfoFile.getLine();
    
    std::string port = line.substr(line.find(':') + 1).c_str();
    std::string ip = line.substr(0, line.find(':'));

    return IPAddress{ ip, port };
}

ClientName getClientName(File& transferInfoFile) {
    return convertTo<ClientName>(transferInfoFile.getLineBin());
}

TransferInfo getTransferInfo(const std::string& transferInfoPath) {
    File transferInfoFile(transferInfoPath, std::ios_base::in);

    return TransferInfo{
        getIP(transferInfoFile),
        getClientName(transferInfoFile),
        transferInfoFile.getLine(),
    };
}
