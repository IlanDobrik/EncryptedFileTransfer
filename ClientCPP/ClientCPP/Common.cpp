#include "Common.hpp"


std::string getLine(std::ifstream& file)
{
    std::string line;
    std::getline(file, line);

    return line;
}

Buffer getLineBin(std::ifstream& file)
{
    std::string line;
    std::getline(file, line);

    return Buffer(line.begin(), line.end());;
}
