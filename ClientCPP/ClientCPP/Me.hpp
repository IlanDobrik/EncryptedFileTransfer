#pragma once

#include <fstream>
#include <string>

#include "Common.hpp"
#include "Hardcoded.h"

struct Me {
    ClientName name;
    ClientID UUID; 
    Buffer privateKey; // Is this AES?
};

Me getMe(const std::string& mePath);
void saveMe(const std::string& mePath, const Me& me);
