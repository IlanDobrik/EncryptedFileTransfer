#pragma once

#include "IResponse.h"


constexpr Code SUCCESSFUL_REGISTER_RESPONSE_CODE = 1600;


class SuccessfulRegisterResponse : public ResponseWithClientID
{
public:
	SuccessfulRegisterResponse(const Buffer& input);
};

