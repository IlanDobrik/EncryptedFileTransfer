#pragma once

#include "Common.h"
#include "Hardcoded.h"

#include <algorithm>

template<typename T, typename S>
S read_primitive(S src, T& dst) {
	uint32_t dataSize = static_cast<uint32_t>(sizeof(dst));
	std::copy_n(src, dataSize, reinterpret_cast<uint8_t*>(&dst));
	return src + dataSize;
}

template<typename T=Buffer, typename S>
S read_buffer(S src, T& dst) {
	uint32_t dataSize = static_cast<uint32_t>(dst.size());
	std::copy_n(src, dataSize, reinterpret_cast<uint8_t*>(dst.data()));
	return src + dataSize;
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
