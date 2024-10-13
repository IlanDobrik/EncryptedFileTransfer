#pragma once

#include "Response.h"

constexpr Code CRC_RESPONSE_CODE = 1603;

class CRCResponse : public ResponsePayloadWithClientID
{
public:
	CRCResponse(const Buffer& input);
	virtual ~CRCResponse() = default;

	CheckSum getCheckSum() const;

protected:
	ContentSize m_contentSize;
	FileName m_fileName;
	CheckSum m_checksum;
};
