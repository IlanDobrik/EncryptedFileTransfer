#include "Response.h"

#include "ClientException.h"

ResponseHeader::ResponseHeader(const Buffer& input)
{
	if (input.size() < RESPONSE_HEADER_SIZE)
	{
		throw ClientException("Input shorter than header size");
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
	if (m_payload.size() < m_clientID.size())
	{
		throw ClientException("Payload smaller than clientID");
	}

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
