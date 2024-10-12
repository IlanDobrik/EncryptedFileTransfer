#include "RegisterRequest.h"


RegisterRequest::RegisterRequest(const ClientID& clientID, const ClientName& clientName) : 
	RequestWithClientName(clientID, clientName, REGISTER_REQUEST_CODE)
{ }
