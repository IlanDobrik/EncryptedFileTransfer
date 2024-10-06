#include "RegisterRequest.h"


RegisterRequest::RegisterRequest(const ClientID& clientID, const ClientName& clientName) : 
	RequestWithName(clientID, clientName, REGISTER_REQUEST_CODE)
{ }
