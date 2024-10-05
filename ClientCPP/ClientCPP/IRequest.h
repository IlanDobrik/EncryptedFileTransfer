#pragma once

#include "Common.hpp"
#include "Hardcoded.h"


class Request {
public:
	Request(const ClientID& clientId, const Code& code);
	Buffer serialize();
	
protected:
	virtual ~Request() = default;
	virtual Buffer _serialize();

private:
	Buffer serializeHeader(const PayloadSize payloadSize);

private:
	Version m_version;

protected:
	const ClientID m_clientID;
	Code m_code;
};
