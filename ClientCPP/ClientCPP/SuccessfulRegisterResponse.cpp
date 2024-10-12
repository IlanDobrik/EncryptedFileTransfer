#include "SuccessfulRegisterResponse.h"
#include <sstream>

SuccessfulRegisterResponse::SuccessfulRegisterResponse(const Buffer& input) :
	HeaderWithClientID(input)
{ }

