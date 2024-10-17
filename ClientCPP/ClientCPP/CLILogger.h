#pragma once

#include "ILogger.h"

class CLILogger : public ILogger {
public:
	CLILogger() = default;
	virtual ~CLILogger() = default;

	virtual void write(const std::string& data);
};