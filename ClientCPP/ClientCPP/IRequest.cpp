#include "IRequest.h"

constexpr uint8_t HEADER_SIZE = sizeof(ClientID) + sizeof(Version) + sizeof(Code) + sizeof(PayloadSize);

IRequest::IRequest(const ClientID& clientId, const Code& code) :
	m_clientID(clientId), m_code(code), m_version(CLIENT_VERSION)
{ }

Buffer IRequest::serialize()
{
	Buffer payload = _serialize();
	Buffer header = serializeHeader();
	Buffer out;

	out.insert(out.end(), header.cbegin(), header.cend());
	out.insert(out.end(), payload.cbegin(), payload.cend());

	return out;
}

Buffer IRequest::serializeHeader()
{
	Buffer header(HEADER_SIZE, 0);
	uint8_t* data = header.data();

	memcpy(data, m_clientID.data(), m_clientID.size());
	data += m_clientID.size();

	memcpy(data, &m_version, sizeof(m_version));
	data += sizeof(m_version);

	memcpy(data, &m_code, sizeof(m_code));
	data += sizeof(m_code);

	return header;
}
