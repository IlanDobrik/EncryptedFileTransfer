#include "CRCRequest.h"

OKCRCRequest::OKCRCRequest(const ClientID& clientID, const FileName& filename) :
	RequestWithFileName(clientID, filename, OK_CRC_REQUEST_CODE)
{
}

BadCRCRequest::BadCRCRequest(const ClientID& clientID, const FileName& filename) : 
	RequestWithFileName(clientID, filename, BAD_CRC_REQUEST_CODE)
{
}

FinalBadCRCRequest::FinalBadCRCRequest(const ClientID& clientID, const FileName& filename) : 
	RequestWithFileName(clientID, filename, FINAL_BAD_CRC_REQUEST_CODE)
{
}

