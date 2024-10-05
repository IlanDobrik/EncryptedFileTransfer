#include "ReconnectRequest.h"

// TODO fix the clinetID shit
ReconnectRequest::ReconnectRequest(const ClientID& clientID, const ClientName& clientName) :
	RegisterRequest(clientName)
{
	m_code = RECONNECT_REQUEST_CODE;
	m_clientID = clientID;
}
