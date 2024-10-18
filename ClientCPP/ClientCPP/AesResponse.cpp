#include "AesResponse.h"

AesResponse::AesResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input), m_aesKey(Buffer(m_payload.size(), 0)) // TODO incorrect - should be minus clientID
{
	if (m_payload.size() < m_aesKey.size())
	{
		throw std::exception("Input too short!");
	}

	auto p = m_payload.begin();
	p = read_buffer(p, m_aesKey);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

Buffer AesResponse::getAesKey() const
{
	return m_aesKey;
}
