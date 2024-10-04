#include "AesRequest.h"



AesRequest::AesRequest(const ClientID& clientID, const ClientName& clientName, const PublicKey& publicKey) :
	RegisterRequest(clientName), m_publicKey(publicKey) // TODO client ID?
{ 
	m_code = AES_REQUEST_CODE; // TODO more elegent?
}

Buffer AesRequest::_serialize()
{
	Buffer rr = RegisterRequest::_serialize();
	Buffer t = Buffer(m_publicKey.cbegin(), m_publicKey.cend());
	
	Buffer out(rr.cbegin(), rr.cend());
	out.insert(out.end(), t.cbegin(), t.cend());
	return out;
}
