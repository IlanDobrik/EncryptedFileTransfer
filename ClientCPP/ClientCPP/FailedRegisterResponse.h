#pragma once

#include "IResponse.h"


constexpr Code FAILED_REGISTER_RESPONSE_CODE = 1601;

class FailedRegisterResponse : public Response
{
	FailedRegisterResponse(const Buffer& input);

private:
	ClientID m_clientID;
};

