#pragma once

#include "Response.h"


constexpr Code FAILED_REGISTER_RESPONSE_CODE = 1601;

class FailedRegisterResponse : public ResponsePayloadWithClientID
{
public:
	FailedRegisterResponse(const Buffer& input);
};

