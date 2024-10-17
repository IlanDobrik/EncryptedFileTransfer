#pragma once

#include "Common.h"
#include "Hardcoded.h"


template<typename T, typename S>
S write_primitive(S dst, const T& src) {
	uint32_t dataSize = static_cast<uint32_t>(sizeof(src));
	std::copy_n(reinterpret_cast<const uint8_t*>(&src), dataSize, dst);
	return dst + dataSize;
}

template<typename T = Buffer, typename S>
S write_buffer(S dst, const T& src) {
	uint32_t dataSize = static_cast<uint32_t>(src.size());
	std::copy_n(reinterpret_cast<const uint8_t*>(src.data()), dataSize, dst);
	return dst + dataSize;
}


class Request {
public:
	Request(const ClientID& clientId, const Code& code);
	virtual Buffer serialize();
	
protected:
	virtual ~Request() = default;
	virtual Buffer serializePayload();
	virtual Buffer serializeHeader(const PayloadSize payloadSize);

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
	virtual Buffer serializeHeader(const PayloadSize payloadSize);

protected:
	ClientName m_clientName;
};

class RequestWithFileName : public Request {
public:
	RequestWithFileName(const ClientID& clientId, const FileName& fileName, const Code& code);

protected:
	virtual ~RequestWithFileName() = default;
	virtual Buffer serializeHeader(const PayloadSize payloadSize);

protected:
	FileName m_fileName;
};
