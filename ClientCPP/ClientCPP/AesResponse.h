#pragma once

#include "Response.h"
#include "SuccessfulRegisterResponse.h"


constexpr Code AES_RESPONSE_CODE = 1602;

class AesResponse : public ResponsePayloadWithClientID
{
public:
	AesResponse(const Buffer& input);

	Buffer getAesKey() const;

private:
	Buffer m_aesKey;
};

