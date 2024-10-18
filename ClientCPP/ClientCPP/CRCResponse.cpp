#include "CRCResponse.h"

#include "ClientException.h"


CRCResponse::CRCResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{
	constexpr uint32_t CRC_PAYLOAD_SIZE = sizeof(m_contentSize) + sizeof(m_fileName) + sizeof(m_checksum);
	if (m_payload.size() < CRC_PAYLOAD_SIZE)
	{
		throw ClientException("Payload too short to include CRC");
	}

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
