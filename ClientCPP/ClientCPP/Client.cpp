#include "Client.h"

#include <iostream>
#include <filesystem>

#include "IResponse.h"

#include "RegisterRequest.h"
#include "SuccessfulRegisterResponse.h"
#include "FailedRegisterResponse.h"

#include "AesRequest.h"
#include "AesResponse.h"

#include "ReconnectRequest.h"
#include "SuccessfulReconnectResponse.h"
#include "FailedReconnectResponse.h"

#include "SendFileRequest.h"


Client::Client(std::unique_ptr<Connection> connection, const RSA& rsa, const AES& aes, const Me& me, const TransferInfo& transferInfo) :
	m_connection(std::move(connection)), 
	m_rsa(rsa), m_aes(nullptr), 
	m_me(me), m_transferInfo(transferInfo)
{ 
	m_me.name = m_transferInfo.clientName;
}

Client::~Client()
{
	try {
		Me::save(m_me, ME_PATH);
	}
	catch (...) { }
}

void Client::uploadFile(const std::string & filePath)
{
	if (m_me.UUID.empty()) {
		registerClient();
	}
	else {
		// Already recived UUID from server
		reconnect();
	}

	_uploadFile(filePath);
	CRCCheck();
}

void Client::attemptXTimes(const uint32_t maxRetries, std::function<void(void)> f)
{
	uint32_t currentTry = 1;
	while (true) {
		try  {
			return f();
		}
		catch (std::exception e) {
			if (currentTry < maxRetries) {
				std::cout << "Attempt " << currentTry << ": " << e.what();
				currentTry++;
			}
			else {
				// TODO send abort?
				throw e;
			}
		}
	}
}

void Client::registerClient()
{
	m_connection->write(RegisterRequest(ClientID{0}, m_transferInfo.clientName).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case SUCCESSFUL_REGISTER_RESPONSE_CODE:
		m_me.UUID = SuccessfulRegisterResponse(data).getClientID();
		exchangeKeys();
		break;
	case FAILED_REGISTER_RESPONSE_CODE:
		throw std::exception("Failed to register");
		break;
	default:
		throw std::exception("Bad response for registeration request");
	}
}

void Client::reconnect()
{
	m_connection->write(ReconnectRequest(m_me.UUID, m_me.name).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case SUCCESSFUL_RECONNECT_RESPONSE_CODE:
		m_aes = std::make_unique<AES>(
			m_rsa.decrypt(
				SuccessfulReconnectResponse(data).getAesKey()));
		break;
	case FAILED_RECONNECT_RESPONSE_CODE:
		m_me.reset();
		registerClient();
		break;
	default:
		throw std::exception("Bad response for registeration request");
	}
}

void Client::exchangeKeys()
{
	m_connection->write(AesRequest(m_me.UUID, m_me.name, m_rsa.getPublicKey()).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case AES_RESPONSE_CODE:
		m_aes = std::make_unique<AES>(
			m_rsa.decrypt(
				AesResponse(data).getAesKey()));
		m_me.WTF_IS_THIS = m_aes->getKey();
		break;

	default:
		throw std::exception("Bad response for key exchange request");
	}
}

void Client::_uploadFile(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios_base::binary);
	OriginalSize originalFileSize = std::filesystem::file_size(filePath);
	ContentSize encryptedFileSize = originalFileSize; // TODO
	FileName fileName;
	std::copy(filePath.cbegin(), filePath.cend(), fileName.begin());
	Buffer content;

	m_connection->write(SendFileRequest(m_me.UUID, encryptedFileSize, originalFileSize, CurrentPacketNumber(0), TotalPacketNumber(0), fileName, content).serialize());
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	default:
		throw std::exception("Bad response for file upload");
	}
}

// TODO
void Client::CRCCheck()
{
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case 1603:
		// OK
		break;
	case 1604:
		// 
		break;
	default:
		throw std::exception("Bad response for key exchange request");
	}

	// TODO response with 900 if CRC matches
	// 901 if not
	// 902 after 3rd attempt + exit
}
