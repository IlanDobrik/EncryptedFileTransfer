#pragma once

#include "IRequest.h"
#include "RegisterRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"


constexpr Code RECONNECT_REQUEST_CODE = 827;

class ReconnectRequest : public RequestWithClientName {
public:
	ReconnectRequest(const ClientID& clientID, const ClientName& clientName);
	virtual ~ReconnectRequest() = default;
};
