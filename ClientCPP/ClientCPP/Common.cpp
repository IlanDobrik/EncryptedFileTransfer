#include "Common.hpp"


std::string removeNulls(std::string s)
{
    s.erase(std::find(s.begin(), s.end(), '\0'), s.end());
    return s;
}

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
