#pragma once

#include <fstream>
#include <string>


struct IPAddress {
    std::string ip;
    uint32_t port;
};

struct TransferInfo {
    IPAddress ipAddress;
    std::string clientName; // TODO limit 100
    std::string filePath;
};

TransferInfo getTransferInfo(const std::string& transferInfoPath);