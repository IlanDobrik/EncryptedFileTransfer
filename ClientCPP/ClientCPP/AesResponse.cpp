#include "AesResponse.h"

AesResponse::AesResponse(const Buffer& input) :
	Response(input), m_aesKey(Buffer(m_payloadSize, 0)) // TODO incorrect - should be minus clientID
{
	auto p = m_payload.begin();
	std::copy(m_payload.begin(), m_payload.end(), m_aesKey.data());
	p += sizeof(m_aesKey);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}

Buffer AesResponse::getAesKey() const
{
	return m_aesKey;
}
