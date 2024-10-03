#pragma once

#include "Common.hpp"
#include "Hardcoded.h"


class IRequest {
public:
	IRequest(const ClientID& clientId, const Code& code);
	Buffer serialize();
	
protected:
	virtual ~IRequest() = default;
	virtual Buffer _serialize() = 0;

private:
	Buffer serializeHeader();

private:
	Version m_version;

protected:
	ClientID m_clientID;
	Code m_code;
};
