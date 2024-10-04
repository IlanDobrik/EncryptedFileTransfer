#include "IResponse.h"

Response::Response(const Buffer& input)
{
	if (input.size() < RESPONSE_HEADER_SIZE)
	{
		throw std::exception("Input too short!");
	}
	
	auto p = input.begin();

	std::copy(p, p + sizeof(m_version), &m_version);
	p += sizeof(m_version);

	std::copy(p, p + sizeof(m_code), &m_code);
	p += sizeof(m_code);

	std::copy(p, p + sizeof(m_payloadSize), &m_payloadSize);
	p += sizeof(m_payloadSize);

	if (input.size() < RESPONSE_HEADER_SIZE + m_payloadSize)
	{
		throw std::exception("Payload is smaller than payload size");
	}

	m_payload = Buffer(m_payloadSize, 0);
	std::copy(p, p + m_payload.size(), m_payload.data());
}

Code Response::getCode() const
{
	return m_code;
}
