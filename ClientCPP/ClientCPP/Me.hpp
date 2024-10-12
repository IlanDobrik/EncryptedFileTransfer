#pragma once

#include <fstream>
#include <string>

#include "Common.hpp"
#include "Hardcoded.h"

struct Me {
    ClientName name;
    ClientID UUID; 
    Buffer WTF_IS_THIS;

    void reset();
    bool isEmpty();

    static Me get(const std::string& mePath);
    static void save(const Me& me, const std::string& mePath);
};
