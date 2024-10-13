#include "AckResponse.h"

AckResponse::AckResponse(const Buffer& input) : 
	ResponsePayloadWithClientID(input)
{ }
