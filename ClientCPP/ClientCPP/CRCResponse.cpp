#include "CRCResponse.h"

CRCResponse::CRCResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{
	auto p = m_payload.begin();

	p = read_primitive(p, m_contentSize);
	p = read_primitive(p, m_fileName);
	p = read_primitive(p, m_checksum);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

CheckSum CRCResponse::getCheckSum() const
{
	return m_checksum;
}
