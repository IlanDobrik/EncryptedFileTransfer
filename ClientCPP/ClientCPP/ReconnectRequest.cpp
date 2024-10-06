#include "ReconnectRequest.h"

ReconnectRequest::ReconnectRequest(const ClientID& clientID, const ClientName& clientName) :
	RequestWithName(clientID, clientName, RECONNECT_REQUEST_CODE)
{ }
