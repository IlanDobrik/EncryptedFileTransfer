#pragma once

#include <memory>
#include <functional>

#include "Connection.h"
#include "Me.h"
#include "TransferInfo.h"
#include "RSAEncryption.h"
#include "AESEncryption.h"
#include "Response.h"
#include "ILogger.h"


class Client
{
public:
	Client(std::unique_ptr<Connection> connection, std::unique_ptr<ILogger> logger,
		const RSA& rsa, 
		const Me& me, const TransferInfo& transferInfo);
	virtual ~Client();
	void run(const std::string& filePath);


private:
	void registerClient();
	void reconnect();
	void exchangeKeys();
	void uploadFile(const std::string& filePath);
	void uploadPacket(const FileName& filename, const Buffer& packet,
		const CurrentPacketNumber current, const TotalPacketNumber total);
	void CRCCheck(const FileName& fileName, const CheckSum& checksum);
	void finish();

	Response readResponse();

private:
	std::unique_ptr<Connection> m_connection;
	std::unique_ptr<ILogger> m_logger;

	RSA m_rsa;
	std::unique_ptr<AES> m_aes;
	Me m_me;
	const TransferInfo m_transferInfo;

};

