#pragma once

#include "Common.hpp"
#include "Hardcoded.h"


class Request {
public:
	Request(const ClientID& clientId, const Code& code);
	virtual Buffer serialize();
	
protected:
	virtual ~Request() = default;
	virtual Buffer _serialize();

private:
	Buffer serializeHeader(const PayloadSize payloadSize);

private:
	Version m_version;

protected:
	ClientID m_clientID;
	Code m_code;
};


class RequestWithName : public Request {
public:
	RequestWithName(const ClientID& clientId, const ClientName& clientName, const Code& code);

protected:
	virtual ~RequestWithName() = default;
	virtual Buffer _serialize();

protected:
	ClientName m_clientName;
};
