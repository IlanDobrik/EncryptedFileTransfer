#pragma once

#include "IRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"


constexpr Code RECONNECT_REQUEST_CODE = 826;

class ReconnectRequest : public Request {
public:
	ReconnectRequest(const ClientID& clientID, const PublicKey& publicKey);
	virtual ~ReconnectRequest() = default;

	virtual Buffer _serialize();

private:
	PublicKey m_publicKey;
};
