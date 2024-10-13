#include "FailedRegisterResponse.h"

FailedRegisterResponse::FailedRegisterResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{ }
