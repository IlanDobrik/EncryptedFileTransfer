#pragma once

#include <fstream>
#include <string>


struct Me {
    std::string name;
    std::string UUID; 
    std::string privateKey;
};

Me getMe(std::string mePath);