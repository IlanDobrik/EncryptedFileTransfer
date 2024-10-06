#pragma once

#include "AesResponse.h"

constexpr Code SUCCESSFUL_RECONNECT_RESPONSE_CODE = 1605;


class SuccessfulReconnectResponse : public AesResponse
{
public:
	SuccessfulReconnectResponse(const Buffer& input);
	virtual ~SuccessfulReconnectResponse() = default;
};

