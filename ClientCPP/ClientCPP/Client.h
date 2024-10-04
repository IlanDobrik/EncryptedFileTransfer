#pragma once

#include <memory>

#include "Connection.h"
#include "Me.hpp"
#include "TransferInfo.hpp"
#include "RSAEncryption.hpp"
#include "AESEncryption.hpp"


class Client
{
public:
	Client(std::unique_ptr<Connection> connection, const RSA& rsa, const AES& aes, const Me& me, const TransferInfo& transferInfo);
	void uploadFile(const std::string& filePath);

private:
	std::unique_ptr<Connection> m_connection;
	RSA m_rsa;
	AES m_aes;
	const Me m_me;
	const TransferInfo m_transferInfo;

};

