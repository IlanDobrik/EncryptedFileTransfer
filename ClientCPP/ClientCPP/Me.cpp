#include "Me.hpp"


Me getMe(const std::string& mePath) {
    std::ifstream configFile(mePath);

    if (!configFile.is_open()) {
        throw std::exception("Failed to open file. Check path");
    }

    return Me{
        getLine(configFile),
        getLine(configFile),
        getLineBin(configFile),
    };
}

