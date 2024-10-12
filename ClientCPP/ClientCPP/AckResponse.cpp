#include "AckResponse.h"

AckResponse::AckResponse(const Buffer& input) : 
	HeaderWithClientID(input)
{ }
