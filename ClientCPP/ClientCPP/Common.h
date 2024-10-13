#pragma once

#include <vector>
#include <string>
#include <fstream>


typedef std::vector<uint8_t> Buffer;


std::string removeNulls(std::string s);

std::string getLine(std::ifstream& file);
Buffer getLineBin(std::ifstream& file);