#pragma once

#include "IResponse.h"


constexpr Code SUCCESSFUL_REGISTER_RESPONSE_CODE = 1600;


class SuccessfulRegisterResponse : public HeaderWithClientID
{
public:
	SuccessfulRegisterResponse(const Buffer& input);
};

