#include "Client.h"

#include <iostream>
#include <filesystem>

#include "Response.h"

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

#include "CRCRequest.h"
#include "AckResponse.h"


Client::Client(std::unique_ptr<Connection> connection, const RSA& rsa, const Me& me, const TransferInfo& transferInfo) :
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

void Client::registerClient()
{
	m_connection->write(RegisterRequest(ClientID{0}, m_transferInfo.clientName).serialize());
	auto data = readResponse();

	switch (data.responseHeader.getCode()) {
	case SUCCESSFUL_REGISTER_RESPONSE_CODE:
		m_me.UUID = SuccessfulRegisterResponse(data.responsePayload).getClientID();
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
	auto data = readResponse();

	switch (data.responseHeader.getCode()) {
	case SUCCESSFUL_RECONNECT_RESPONSE_CODE:
		m_aes = std::make_unique<AES>(
			m_rsa.decrypt(
				SuccessfulReconnectResponse(data.responsePayload).getAesKey()));
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
	auto data = readResponse();

	switch (data.responseHeader.getCode()) {
	case AES_RESPONSE_CODE:
		m_aes = std::make_unique<AES>(
			m_rsa.decrypt(
				AesResponse(data.responsePayload).getAesKey()));
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
	
	const TotalPacketNumber totalPackets = static_cast<TotalPacketNumber>(
		fileSize / MAX_PACKET_SIZE + 
		(0 == fileSize % MAX_PACKET_SIZE ? 0: 1)); // Add 1 for left over
	CurrentPacketNumber currentPacket = 1;

	std::ifstream file(filePath, std::ios_base::binary);
	Crc crc;
	for (;currentPacket - 1 < totalPackets; ++currentPacket) {
		Buffer packet(MAX_PACKET_SIZE, 0);
		
		file.read(reinterpret_cast<char*>(packet.data()), static_cast<std::streamsize>(packet.size()));
		uint32_t bytesRead = file.gcount();
		packet.resize(bytesRead);

		crc.add(packet);
		uploadPacket(fileName, packet, currentPacket, totalPackets);
	}
	file.close();

	CRCCheck(fileName, crc.calc());
}

void Client::uploadPacket(const FileName& filename, const Buffer& packet,
	const CurrentPacketNumber current, const TotalPacketNumber total)
{
	OriginalSize originalFileSize = static_cast<OriginalSize>(packet.size());

	Buffer encryptedPacket = m_aes->encrypt(packet);
	Buffer decryptedPacket = m_aes->decrypt(encryptedPacket);
	ContentSize encryptedFileSize = static_cast<ContentSize>(encryptedPacket.size());

	m_connection->write(SendFileRequest(m_me.UUID,
		encryptedFileSize, originalFileSize,
		current, total,
		filename, encryptedPacket).serialize());
}

void Client::CRCCheck(const FileName& fileName, const CheckSum& checksum)
{
	auto data = readResponse();

	switch (data.responseHeader.getCode()) {
	case CRC_RESPONSE_CODE: {
		if (checksum == CRCResponse(data.responsePayload).getCheckSum()) {
			m_connection->write(OKCRCRequest(m_me.UUID, fileName).serialize());
		}
		else {
			m_connection->write(BadCRCRequest(m_me.UUID, fileName).serialize());
		}
		// Finish
		break;
		}
	case ACK_RESPONSE_CODE:
		// Finish
		break;
	default:
		throw std::exception("Bad response for CRC request");
	}
}


Response Client::readResponse()
{
	auto header = m_connection->read(RESPONSE_HEADER_SIZE);
	ResponseHeader responseHeader(header);

	auto payload = m_connection->read(responseHeader.getPayloadSize());

	return {header, payload};
}
