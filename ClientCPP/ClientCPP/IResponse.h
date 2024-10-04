#pragma once

#include "Common.hpp"
#include "Hardcoded.h"

class Response
{
public:
	Response(const Buffer& input); 

	Code getCode() const;
	Code getPayloadSize() const;

protected:
	Version m_version;
	Code m_code;
	PayloadSize m_payloadSize;
	Buffer m_payload;
};

