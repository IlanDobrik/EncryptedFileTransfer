#pragma once

#include "Response.h"

constexpr Code FAILED_RECONNECT_RESPONSE_CODE = 1606;

class FailedReconnectResponse : public ResponsePayloadWithClientID
{
public:
	FailedReconnectResponse(const Buffer& input);
	virtual ~FailedReconnectResponse() = default;
};

