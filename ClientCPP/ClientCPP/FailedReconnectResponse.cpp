#include "FailedReconnectResponse.h"

FailedReconnectResponse::FailedReconnectResponse(const Buffer& input) :
	HeaderWithClientID(input)
{ }
