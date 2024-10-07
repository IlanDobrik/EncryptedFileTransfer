#pragma once

#include "Common.hpp"
#include "Hardcoded.h"

#include <algorithm>

template<typename T, typename S>
S write(S begin, T data) {
	std::copy_n(begin, sizeof(data), reinterpret_cast<uint8_t*>(&data));
	return begin + sizeof(data);
}


class Response
{
public:
	Response(const Buffer& input); 
	virtual ~Response() = default;

	Code getCode() const;
	PayloadSize getPayloadSize() const;

protected:
	Version m_version;
	Code m_code;
	PayloadSize m_payloadSize;
	Buffer m_payload;
};


class ResponseWithClientID : public Response {
public:
	ResponseWithClientID(const Buffer& input);
	virtual ~ResponseWithClientID() = default;
	ClientID getClientID() const;

private:
	ClientID m_clientID;
};