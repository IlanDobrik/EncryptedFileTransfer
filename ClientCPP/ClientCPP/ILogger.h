#pragma once

#include "Common.h"


class ILogger
{
public:
	virtual void write(const std::string& data) = 0;
};
