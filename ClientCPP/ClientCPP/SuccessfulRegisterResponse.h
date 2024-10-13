#pragma once

#include "Response.h"


constexpr Code SUCCESSFUL_REGISTER_RESPONSE_CODE = 1600;


class SuccessfulRegisterResponse : public ResponsePayloadWithClientID
{
public:
	SuccessfulRegisterResponse(const Buffer& input);
};

