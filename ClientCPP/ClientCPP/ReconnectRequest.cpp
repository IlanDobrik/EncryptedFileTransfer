#include "ReconnectRequest.h"

ReconnectRequest::ReconnectRequest(const ClientID& clientID, const ClientName& clientName) :
	RequestWithClientName(clientID, clientName, RECONNECT_REQUEST_CODE)
{ }
