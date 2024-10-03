#include "RegisterRequest.h"


RegisterRequest::RegisterRequest(const ClientID& clientID, const ClientName& clientName) : 
	IRequest(clientID, REGISTER_REQUEST_CODE), m_name(clientName)
{ }

Buffer RegisterRequest::_serialize()
{
	return Buffer(m_name.cbegin(), m_name.cend());
}
