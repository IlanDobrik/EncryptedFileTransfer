#pragma once

#include <fstream>
#include <string>

#include "Common.hpp"

struct Me {
    std::string name;
    std::string UUID; 
    Buffer privateKey; // Is this AES?
};

Me getMe(const std::string& mePath);
