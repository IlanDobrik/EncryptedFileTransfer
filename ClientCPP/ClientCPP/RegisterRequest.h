#pragma once

#include "IRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"


constexpr Code REGISTER_REQUEST_CODE = 825;

class RegisterRequest : public RequestWithName {
public:
	RegisterRequest(const ClientID& clientID, const ClientName& clientName);
	virtual ~RegisterRequest() = default;
};
