#include "Request.h"


Request::Request(const ClientID& clientId, const Code& code) :
	m_clientID(clientId), m_code(code), m_version(CLIENT_VERSION)
{ }

Buffer Request::serialize()
{
	Buffer payload = serializePayload();
	Buffer header = serializeHeader(static_cast<PayloadSize>(payload.size()));
	Buffer out;

	out.insert(out.end(), header.cbegin(), header.cend());
	out.insert(out.end(), payload.cbegin(), payload.cend());

	return out;
}

Buffer Request::serializePayload()
{
	return Buffer();
}

Buffer Request::serializeHeader(const PayloadSize payloadSize)
{
	Buffer header(REQUEST_HEADER_SIZE, 0);
	auto p = header.begin();

	p = write_buffer(p, m_clientID);
	p = write_primitive(p, m_version);
	p = write_primitive(p, m_code);
	p = write_primitive(p, payloadSize);

	return header;
}

RequestWithClientName::RequestWithClientName(const ClientID& clientId, const ClientName& clientName, const Code& code) : 
	Request(clientId, code), m_clientName(clientName)
{ }

Buffer RequestWithClientName::serializeHeader(const PayloadSize payloadSize)
{
	Buffer header = Request::serializeHeader(payloadSize + static_cast<uint32_t>(m_clientName.size()));
	header.insert(header.end(), m_clientName.cbegin(), m_clientName.cend());

	return header;
}

RequestWithFileName::RequestWithFileName(const ClientID& clientId, const FileName& fileName, const Code& code) :
	Request(clientId, code), m_fileName(fileName)
{
}

Buffer RequestWithFileName::serializeHeader(const PayloadSize payloadSize)
{
	Buffer header = Request::serializeHeader(payloadSize + m_fileName.size());
	header.insert(header.end(), m_fileName.cbegin(), m_fileName.cend());

	return header;
}
