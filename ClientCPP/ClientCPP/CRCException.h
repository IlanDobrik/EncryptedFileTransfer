#pragma once

#include "ClientException.h"


class CRCException : public ClientException {
public:
	CRCException() : ClientException("Bad CRC") {}
	virtual ~CRCException() = default;
};
