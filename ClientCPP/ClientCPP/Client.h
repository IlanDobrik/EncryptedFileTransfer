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
#include "File.h"


class Client
{
public:
	Client(std::unique_ptr<Connection> connection, std::unique_ptr<ILogger> logger,
		std::unique_ptr<File> file,
		const RSA& rsa, 
		const Me& me, const TransferInfo& transferInfo);
	virtual ~Client();
	void run();

private:
	void registerClient();
	void reconnect();
	void exchangeKeys();
	void uploadFile();
	void uploadPacket(const Buffer& packet,
		const CurrentPacketNumber current, const TotalPacketNumber total);
	void CRCCheck(const CheckSum& checksum);
	void finish();

	Response readResponse();
	void attemptXTimes(const uint32_t maxRetries, std::function<void(void)> func);

private:
	std::unique_ptr<Connection> m_connection;
	std::unique_ptr<ILogger> m_logger;
	std::unique_ptr<File> m_file;


	RSA m_rsa;
	std::unique_ptr<AES> m_aes;

	Me m_me;
	const TransferInfo m_transferInfo;

};

