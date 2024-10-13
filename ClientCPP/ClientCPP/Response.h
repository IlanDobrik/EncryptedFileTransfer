#pragma once

#include "Common.h"
#include "Hardcoded.h"

#include <algorithm>

template<typename T, typename S>
S write(S begin, T* data) {
	uint8_t dataSize = sizeof(*data);
	std::copy_n(begin, dataSize, reinterpret_cast<uint8_t*>(data));
	return begin + dataSize;
}

class ResponseHeader
{
public:
	ResponseHeader(const Buffer& input); 
	virtual ~ResponseHeader() = default;

	Code getCode() const;
	PayloadSize getPayloadSize() const;

protected:
	Version m_version;
	Code m_code;
	PayloadSize m_payloadSize;
};


class ResponsePayload {
protected:
	ResponsePayload(const Buffer& payload);
	virtual ~ResponsePayload() = default;

protected:
	Buffer m_payload;
};

class ResponsePayloadWithClientID : public ResponsePayload {
public:
	ResponsePayloadWithClientID(const Buffer& input);
	virtual ~ResponsePayloadWithClientID() = default;
	ClientID getClientID() const;

protected:
	ClientID m_clientID;
};

struct Response {
	ResponseHeader responseHeader;
	Buffer responsePayload;
};
