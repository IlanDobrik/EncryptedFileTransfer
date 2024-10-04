#pragma once

#include "Common.hpp"
#include "Hardcoded.h"

class IResponse
{
public:
	IResponse(const Buffer& input); 

protected:
	Version m_version;
	Code m_code;
	PayloadSize m_payloadSize;
	Buffer m_payload;
};

