#pragma once

#include "IResponse.h"

constexpr Code ACK_RESPONSE_CODE = 1604;

class AckResponse : public HeaderWithClientID
{
public:
	AckResponse(const Buffer& input);
	virtual ~AckResponse() = default;
};

