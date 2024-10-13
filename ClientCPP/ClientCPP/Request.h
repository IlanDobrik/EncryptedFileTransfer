#pragma once

#include "Common.h"
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


class RequestWithClientName : public Request {
public:
	RequestWithClientName(const ClientID& clientId, const ClientName& clientName, const Code& code);

protected:
	virtual ~RequestWithClientName() = default;
	virtual Buffer _serialize();

protected:
	ClientName m_clientName;
};

class RequestWithFileName : public Request {
public:
	RequestWithFileName(const ClientID& clientId, const FileName& fileName, const Code& code);

protected:
	virtual ~RequestWithFileName() = default;
	virtual Buffer _serialize();

protected:
	FileName m_fileName;
};
