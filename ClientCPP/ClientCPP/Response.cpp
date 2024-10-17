#include "Response.h"

ResponseHeader::ResponseHeader(const Buffer& input)
{
	if (input.size() < RESPONSE_HEADER_SIZE)
	{
		throw std::exception("Input too short!");
	}
	
	auto p = input.begin();

	p = read_primitive(p, m_version);
	p = read_primitive(p, m_code);
	p = read_primitive(p, m_payloadSize);
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
	p = read_buffer(p, m_clientID);

	m_payload = Buffer(p, m_payload.end()); // Move pointer so others can inherite and continue parse
}

ClientID ResponsePayloadWithClientID::getClientID() const
{
	return m_clientID;
}

ResponsePayload::ResponsePayload(const Buffer& payload) :
	m_payload(payload)
{ }
