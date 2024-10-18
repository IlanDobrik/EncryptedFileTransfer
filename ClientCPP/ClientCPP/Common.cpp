#include "Common.h"


std::string removeNulls(std::string s)
{
    s.erase(std::find(s.begin(), s.end(), '\0'), s.end());
    return s;
}
