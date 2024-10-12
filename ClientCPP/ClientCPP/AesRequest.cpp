#include "AesRequest.h"



AesRequest::AesRequest(const ClientID& clientID, const ClientName& clientName, const PublicKey& publicKey) :
	RequestWithClientName(clientID, clientName, AES_REQUEST_CODE), m_publicKey(publicKey)
{ }

Buffer AesRequest::_serialize()
{
	Buffer rr = RequestWithClientName::_serialize();
	Buffer t = Buffer(m_publicKey.cbegin(), m_publicKey.cend());
	
	Buffer out(rr.cbegin(), rr.cend());
	out.insert(out.end(), t.cbegin(), t.cend());
	return out;
}
