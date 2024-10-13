#include "Response.h"

ResponseHeader::ResponseHeader(const Buffer& input)
{
	if (input.size() < RESPONSE_HEADER_SIZE)
	{
		throw std::exception("Input too short!");
	}
	
	auto p = input.begin();

	p = write(p, &m_version);
	p = write(p, &m_code);
	p = write(p, &m_payloadSize);
}

Code ResponseHeader::getCode() const
{
	return m_code;
}

PayloadSize ResponseHeader::getPayloadSize() const
{
	return m_payloadSize;
}

ResponsePayloadWithClientID::ResponsePayloadWithClientID(const Buffer& input) : 
	ResponsePayload(input)
{
	auto p = m_payload.begin();
	p = write(p, m_clientID.data());

	m_payload = Buffer(p, m_payload.end()); // Move pointer so others can inherite and continue parse
}

ClientID ResponsePayloadWithClientID::getClientID() const
{
	return m_clientID;
}

ResponsePayload::ResponsePayload(const Buffer& payload) :
	m_payload(payload)
{ }
