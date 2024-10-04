#include "RegisterRequest.h"


RegisterRequest::RegisterRequest(const ClientName& clientName) : 
	IRequest(ClientID(), REGISTER_REQUEST_CODE), m_name(clientName)
{ }

Buffer RegisterRequest::_serialize()
{
	return Buffer(m_name.cbegin(), m_name.cend());
}
