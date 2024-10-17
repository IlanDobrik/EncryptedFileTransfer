#include "CLILogger.h"

#include <iostream>


void CLILogger::write(const std::string& data)
{
	std::cout << data << std::endl;
}
