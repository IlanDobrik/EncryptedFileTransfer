#include "SuccessfulRegisterResponse.h"
#include <sstream>

SuccessfulRegisterResponse::SuccessfulRegisterResponse(const Buffer& input) :
	IResponse(input)
{	
	auto p = m_payload.begin();
	std::copy(m_payload.begin(), m_payload.end(), m_clientID.data());
	p += sizeof(m_clientID);

	m_payload = Buffer(p, m_payload.end()); //Move pointer so others can inherite and continue parse
}
