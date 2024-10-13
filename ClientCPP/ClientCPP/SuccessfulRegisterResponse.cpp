#include "SuccessfulRegisterResponse.h"
#include <sstream>

SuccessfulRegisterResponse::SuccessfulRegisterResponse(const Buffer& input) :
	ResponsePayloadWithClientID(input)
{ }

