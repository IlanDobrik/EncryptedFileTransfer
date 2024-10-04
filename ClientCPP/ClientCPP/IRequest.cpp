#include "IRequest.h"


Request::Request(const ClientID& clientId, const Code& code) :
	m_clientID(clientId), m_code(code), m_version(CLIENT_VERSION)
{ }

Buffer Request::serialize()
{
	Buffer payload = _serialize();
	Buffer header = serializeHeader(static_cast<PayloadSize>(payload.size()));
	Buffer out;

	out.insert(out.end(), header.cbegin(), header.cend());
	out.insert(out.end(), payload.cbegin(), payload.cend());

	return out;
}

Buffer Request::_serialize()
{
	return Buffer();
}

Buffer Request::serializeHeader(const PayloadSize payloadSize)
{
	Buffer header(REQUEST_HEADER_SIZE, 0);
	uint8_t* data = header.data(); // TODO remove raw pointer?

	memcpy(data, m_clientID.data(), m_clientID.size());
	data += m_clientID.size();

	memcpy(data, &m_version, sizeof(m_version));
	data += sizeof(m_version);

	memcpy(data, &m_code, sizeof(m_code));
	data += sizeof(m_code);

	memcpy(data, &payloadSize, sizeof(payloadSize));
	data += sizeof(payloadSize);

	return header;
}
