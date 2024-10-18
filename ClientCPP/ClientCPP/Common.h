#pragma once

#include <vector>
#include <array>
#include <string>
#include <fstream>


typedef std::vector<uint8_t> Buffer;

template<typename T, typename S>
T convertTo(const S& s) {
	T t{ 0 };
	uint32_t amount = static_cast<uint32_t>(s.size() < t.size() ? s.size() : t.size()); // Take smaller
	std::copy(s.cbegin(), s.cbegin() + amount, t.begin());
	return t;
}


std::string removeNulls(std::string s);
