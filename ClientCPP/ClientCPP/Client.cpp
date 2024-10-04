#include "Client.h"
#include "RegisterRequest.h"

Client::Client(std::unique_ptr<Connection> connection, const RSA& rsa, const AES& aes, const Me& me, const TransferInfo& transferInfo) :
	m_connection(std::move(connection)), 
	m_rsa(rsa), m_aes(aes), 
	m_me(me), m_transferInfo(transferInfo)
{ }

void Client::uploadFile(const std::string & filePath)
{
	m_connection->write(RegisterRequest(m_transferInfo.clientName).serialize());
	auto x = m_connection->read();


	if (m_me.privateKey.empty())
	{
		
	}




}
