#pragma once

#include "IResponse.h"
#include "SuccessfulRegisterResponse.h"


constexpr Code AES_RESPONSE_CODE = 1602;

class AesResponse : public HeaderWithClientID
{
public:
	AesResponse(const Buffer& input);

	Buffer getAesKey() const;

private:
	Buffer m_aesKey;
};

