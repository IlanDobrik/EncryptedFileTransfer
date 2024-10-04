#pragma once

#include <fstream>
#include <string>

#include "Common.hpp"
#include "Hardcoded.h"

struct Me {
    ClientName name;
    std::string UUID; 
    Buffer privateKey; // Is this AES?
};

Me getMe(const std::string& mePath);
