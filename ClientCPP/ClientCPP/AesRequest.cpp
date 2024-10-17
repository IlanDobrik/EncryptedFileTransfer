#include "AesRequest.h"


AesRequest::AesRequest(const ClientID& clientID, const ClientName& clientName, const PublicKey& publicKey) :
	RequestWithClientName(clientID, clientName, AES_REQUEST_CODE), m_publicKey(publicKey)
{ }

Buffer AesRequest::serializePayload()
{
	return Buffer(m_publicKey.cbegin(), m_publicKey.cend());
}

