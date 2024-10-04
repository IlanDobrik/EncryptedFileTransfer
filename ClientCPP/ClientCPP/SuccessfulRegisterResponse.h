#pragma once

#include "IResponse.h"

class SuccessfulRegisterResponse : public IResponse
{
	SuccessfulRegisterResponse(const Buffer& input);

private:
	ClientID m_clientID;
};

