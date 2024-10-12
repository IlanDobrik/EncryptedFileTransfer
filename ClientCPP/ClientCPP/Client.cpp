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
#include "CRCResponse.h"
#include "cksum.h"


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

void Client::run(const std::string & filePath)
{
	if (m_me.isEmpty()) {
		registerClient();
	}
	else {
		// Already recived UUID from server
		reconnect();
	}

	uploadFile(filePath);
}

// TODO catch handler, finnally handler
// attemptXTimes(3, uploadFile, catch_handler=respond 901, finally_handler= respond 902)
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

void Client::uploadFile(const std::string& filePath)
{
	constexpr uint32_t MAX_PACKET_SIZE = 1024 * 1024; // 1GB

	FileName fileName{0};
	std::copy(filePath.cbegin(), filePath.cend(), fileName.begin());

	const uint64_t fileSize = std::filesystem::file_size(filePath);
	
	const TotalPacketNumber totalPackets = fileSize / MAX_PACKET_SIZE + 
		(0 == fileSize % MAX_PACKET_SIZE ? 0: 1); // Add 1 for less than packetSize
	CurrentPacketNumber currentPacket = 1;

	std::ifstream file(filePath, std::ios_base::binary);
	Crc crc;
	for (;currentPacket - 1 < totalPackets; ++currentPacket) {
		Buffer packet(MAX_PACKET_SIZE, 0);
		
		file.read(reinterpret_cast<char*>(packet.data()), packet.size());
		uint32_t bytesRead = file.gcount();
		packet.resize(bytesRead);

		crc.add(packet);
		uploadPacket(fileName, packet, currentPacket, totalPackets);
	}
	file.close();

	CRCCheck(crc.calc());
}

void Client::uploadPacket(const FileName& filename, const Buffer& packet,
	const CurrentPacketNumber current, const TotalPacketNumber total)
{
	OriginalSize originalFileSize = packet.size();

	Buffer encryptedPacket = m_aes->encrypt(packet);
	Buffer decryptedPacket = m_aes->decrypt(encryptedPacket);
	ContentSize encryptedFileSize = encryptedPacket.size();

	m_connection->write(SendFileRequest(m_me.UUID,
		encryptedFileSize, originalFileSize,
		current, total,
		filename, encryptedPacket).serialize());
}

// TODO
void Client::CRCCheck(const CheckSum& checksum)
{
	auto data = m_connection->read();
	Response response(data);

	switch (response.getCode()) {
	case 1603: {
		auto aba = CRCResponse(data).getCheckSum();
		if (checksum == CRCResponse(data).getCheckSum())
		{
			std::cout << "Fuck yes\n";
			// TODO respond 900
			// Finish
		}
		else {
			// TODO respond 901
		}
		// TODO on 3rd attempt - respond 902 + Finish
		break;
		}
		
	case 1604:
		// Finish
		break;
	default:
		throw std::exception("Bad response for key exchange request");
	}
}
