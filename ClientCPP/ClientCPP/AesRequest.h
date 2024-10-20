#pragma once

#include "Request.h"
#include "Hardcoded.h"
#include "Common.h"


constexpr Code AES_REQUEST_CODE = 826;

class AesRequest : public RequestWithClientName {
public:
	AesRequest(const ClientID& clientID, const ClientName& clientName, const PublicKey& publicKey);
	virtual ~AesRequest() = default;

protected:
	virtual Buffer serializePayload();

private:
	PublicKey m_publicKey;
};
