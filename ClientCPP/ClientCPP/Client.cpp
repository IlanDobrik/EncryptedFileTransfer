#include "Client.h"

#include <iostream>

#include "IResponse.h"

#include "RegisterRequest.h"
#include "SuccessfulRegisterResponse.h"
#include "FailedRegisterResponse.h"

#include "AesRequest.h"
#include "AesResponse.h"


Client::Client(std::unique_ptr<Connection> connection, const RSA& rsa, const AES& aes, const Me& me, const TransferInfo& transferInfo) :
	m_connection(std::move(connection)), 
	m_rsa(rsa), m_aes(nullptr), 
	m_me(me), m_transferInfo(transferInfo)
{ }

void Client::uploadFile(const std::string & filePath)
{
	if (m_me.privateKey.empty())
	{
		attemptXTimes(MAX_RETRY_COUNT, [this]() { registerClient(); }); // TODO prettier?
	}
	else {
		m_aes = std::make_unique<AES>(AesResponse(m_me.privateKey).getAesKey());
	}
}

void Client::attemptXTimes(const uint32_t maxRetries, std::function<void(void)> f)
{
	uint32_t currentTry = 1;
	while (true) {
		try 
		{
			return f();
		}
		catch (std::exception e)
		{
			if (currentTry < maxRetries) {
				std::cout << "Attempt " << currentTry << ": " << e.what();
				currentTry++;
			}
			else {
				throw e;
			}
		}
	}
}

void Client::registerClient()
{
	m_connection->write(RegisterRequest(m_transferInfo.clientName).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case SUCCESSFUL_REGISTER_RESPONSE_CODE:
		m_me.UUID = SuccessfulRegisterResponse(data).getClientID();
		attemptXTimes(MAX_RETRY_COUNT, [this]() { exchangeKeys(); }); // TODO prettier?
		break;
	case FAILED_REGISTER_RESPONSE_CODE:
		throw std::exception("Failed to register");
		break;
	default:
		throw std::exception("Bad response for registeration request");
	}

}

void Client::exchangeKeys()
{
	m_connection->write(AesRequest(m_me.UUID, m_transferInfo.clientName, m_rsa.getPublicKey()).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case AES_RESPONSE_CODE:
		m_aes = std::make_unique<AES>(
			m_rsa.decrypt(
				AesResponse(data).getAesKey()));
		break;
	default:
		throw std::exception("Bad response for key exchange request");
	}
}
