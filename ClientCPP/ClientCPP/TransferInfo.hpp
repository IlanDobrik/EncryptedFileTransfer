#pragma once

#include <fstream>
#include <string>

#include "Hardcoded.h"


struct IPAddress {
    std::string ip;
    uint32_t port;
};

struct TransferInfo {
    IPAddress ipAddress;
    ClientName clientName; // TODO limit 100
    std::string filePath;
};

TransferInfo getTransferInfo(const std::string& transferInfoPath);
