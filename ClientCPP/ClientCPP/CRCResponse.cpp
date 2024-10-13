#include "CRCResponse.h"

CRCResponse::CRCResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{
	auto p = m_payload.begin();

	p = write(p, &m_contentSize);
	p = write(p, &m_fileName);
	p = write(p, &m_checksum);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

CheckSum CRCResponse::getCheckSum() const
{
	return m_checksum;
}
