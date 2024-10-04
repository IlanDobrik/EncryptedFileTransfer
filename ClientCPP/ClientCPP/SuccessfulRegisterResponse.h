#pragma once

#include "IResponse.h"


constexpr Code SUCCESSFUL_REGISTER_RESPONSE_CODE = 1600;

class SuccessfulRegisterResponse : public Response
{
public:
	SuccessfulRegisterResponse(const Buffer& input);

	ClientID getClientID() const;

private:
	ClientID m_clientID;
};

