#include "IResponse.h"

ResponseHeader::ResponseHeader(const Buffer& input)
{
	if (input.size() < RESPONSE_HEADER_SIZE)
	{
		throw std::exception("Input too short!");
	}
	
	auto p = input.begin();

	std::copy_n(p, sizeof(m_version), reinterpret_cast<uint8_t*>(&m_version));
	p += sizeof(m_version);

	std::copy_n(p, sizeof(m_code), reinterpret_cast<uint8_t*>(&m_code));
	p += sizeof(m_code);

	std::copy_n(p, sizeof(m_payloadSize), reinterpret_cast<uint8_t*>(&m_payloadSize));
	p += sizeof(m_payloadSize);

	if (input.size() < RESPONSE_HEADER_SIZE + m_payloadSize)
	{
		return;
	}

	m_payload = Buffer(m_payloadSize, 0);
	std::copy_n(p, m_payload.size(), m_payload.data());
}

Code ResponseHeader::getCode() const
{
	return m_code;
}

PayloadSize ResponseHeader::getPayloadSize() const
{
	return m_payloadSize;
}

HeaderWithClientID::HeaderWithClientID(const Buffer& input) : 
	ResponseHeader(input)
{
	auto p = m_payload.begin();
	std::copy(m_payload.begin(), m_payload.end(), m_clientID.data());
	p += sizeof(m_clientID);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

ClientID HeaderWithClientID::getClientID() const
{
	return m_clientID;
}
