#include "CRCResponse.h"

CRCResponse::CRCResponse(const Buffer& input) :
	HeaderWithClientID(input)
{
	auto p = m_payload.begin();

	// TODO create function for this
	std::copy_n(p, sizeof(m_contentSize), reinterpret_cast<uint8_t*>(&m_contentSize));
	p += sizeof(m_contentSize);

	std::copy_n(p, sizeof(m_fileName), m_fileName.data());
	p += sizeof(m_fileName);

	std::copy_n(p, sizeof(m_checksum), reinterpret_cast<uint8_t*>(&m_checksum));
	p += sizeof(m_checksum);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

CheckSum CRCResponse::getCheckSum() const
{
	return m_checksum;
}
