#pragma once

#include "IResponse.h"

constexpr Code FAILED_RECONNECT_RESPONSE_CODE = 1606;

class FailedReconnectResponse : public ResponseWithClientID
{
public:
	FailedReconnectResponse(const Buffer& input);
	virtual ~FailedReconnectResponse() = default;
};

