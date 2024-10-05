#pragma once

#include <memory>
#include <functional>

#include "Connection.h"
#include "Me.hpp"
#include "TransferInfo.hpp"
#include "RSAEncryption.hpp"
#include "AESEncryption.hpp"


class Client
{
public:
	Client(std::unique_ptr<Connection> connection, const RSA& rsa, const AES& aes, const Me& me, const TransferInfo& transferInfo);
	virtual ~Client();
	void uploadFile(const std::string& filePath);


private:
	static void attemptXTimes(const uint32_t maxRetries, std::function<void()>);
	void registerClient();
	void reconnect();
	void exchangeKeys();
	void _uploadFile(const std::string& filePath);
	void CRCCheck();

private:
	std::unique_ptr<Connection> m_connection;
	RSA m_rsa;
	std::unique_ptr<AES> m_aes;
	Me m_me;
	const TransferInfo m_transferInfo;

};

