#pragma once

#include "Response.h"

constexpr Code ACK_RESPONSE_CODE = 1604;

class AckResponse : public ResponsePayloadWithClientID
{
public:
	AckResponse(const Buffer& input);
	virtual ~AckResponse() = default;
};

