#pragma once

#include "Common.h"


class ILogger
{
public:
	virtual void write(const std::string& data) {
		std::cout << data << std::endl;
	};
};
