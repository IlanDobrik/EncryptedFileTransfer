#include "Me.hpp"


std::string getName(std::ifstream& meFile) {
    std::string line;
    std::getline(meFile, line);

    return line;
}

std::string getUUID(std::ifstream& meFile) {
    std::string line;
    std::getline(meFile, line);

    return line;
}

std::string getPrivateKey(std::ifstream& meFile) {
    std::string line;
    std::getline(meFile, line);

    return line;
}


Me getMe(const std::string& mePath) {
    std::ifstream configFile(mePath);

    if (!configFile.is_open()) {
        throw std::exception("Failed to open file. Check path");
    }

    return Me{
        getName(configFile),
        getUUID(configFile),
        getPrivateKey(configFile),
    };
}
