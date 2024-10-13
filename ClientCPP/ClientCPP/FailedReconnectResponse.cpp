#include "FailedReconnectResponse.h"

FailedReconnectResponse::FailedReconnectResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{ }
