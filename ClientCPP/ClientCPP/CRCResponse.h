#pragma once

#include "IResponse.h"


class CRCResponse : public ResponseWithClientID
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

