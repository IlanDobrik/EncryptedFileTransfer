#pragma once

#include "IResponse.h"


constexpr Code AES_RESPONSE_CODE = 1602;

class AesResponse : public Response
{
public:
	AesResponse(const Buffer& input);

	Buffer getAesKey() const;

private:
	Buffer m_aesKey;
};

