#pragma once

#include <memory>
#include <functional>

#include "Connection.h"
#include "Me.h"
#include "TransferInfo.h"
#include "RSAEncryption.h"
#include "AESEncryption.h"
#include "Response.h"


class Client
{
public:
	Client(std::unique_ptr<Connection> connection, 
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

	Response readResponse();

private:
	std::unique_ptr<Connection> m_connection;
	RSA m_rsa;
	std::unique_ptr<AES> m_aes;
	Me m_me;
	const TransferInfo m_transferInfo;

};

