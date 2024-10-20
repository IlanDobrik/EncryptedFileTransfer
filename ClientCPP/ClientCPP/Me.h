#pragma once

#include <fstream>
#include <string>

#include "Common.h"
#include "Hardcoded.h"

struct Me {
    ClientName name;
    ClientID UUID; 
    Buffer aesKey; 

    void reset();
    bool isEmpty();

    static Me get(const std::string& mePath);
    static void save(const Me& me, const std::string& mePath);
};
