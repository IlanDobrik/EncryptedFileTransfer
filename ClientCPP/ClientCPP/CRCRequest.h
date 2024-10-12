#pragma once

#include "IRequest.h"
#include "RegisterRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"

constexpr Code OK_CRC_REQUEST_CODE = 900;

class OKCRCRequest : public RequestWithFileName {
public:
	OKCRCRequest(const ClientID& clientID, const FileName& filename);
	virtual ~OKCRCRequest() = default;
};


constexpr Code BAD_CRC_REQUEST_CODE = 901;

class BadCRCRequest : public RequestWithFileName {
public:
	BadCRCRequest(const ClientID& clientID, const FileName& filename);
	virtual ~BadCRCRequest() = default;
};

constexpr Code FINAL_BAD_CRC_REQUEST_CODE = 902;

class FinalBadCRCRequest : public RequestWithFileName {
public:
	FinalBadCRCRequest(const ClientID& clientID, const FileName& filename);
	virtual ~FinalBadCRCRequest() = default;
};