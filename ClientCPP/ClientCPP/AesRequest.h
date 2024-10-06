#pragma once

#include "IRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"


constexpr Code AES_REQUEST_CODE = 826;

class AesRequest : public RequestWithName {
public:
	AesRequest(const ClientID& clientID, const ClientName& clientName, const PublicKey& publicKey);
	virtual ~AesRequest() = default;

	virtual Buffer _serialize();

private:
	PublicKey m_publicKey;
};
