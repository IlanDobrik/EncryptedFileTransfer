#pragma once

#include "IRequest.h"
#include "Hardcoded.h"
#include "Common.hpp"


constexpr Code SEND_FILE_REQUEST_CODE = 828;

class SendFileRequest : public Request {
public:
	SendFileRequest(const ClientID& clientId, 
		const ContentSize contentSize, const OriginalSize originalSize, 
		const CurrentPacketNumber currentPacket, const TotalPacketNumber totalPackets, 
		const FileName& fileName, const Buffer& content);
	virtual ~SendFileRequest() = default;

	virtual Buffer _serialize();

private:
	const ContentSize m_contentSize;
	const OriginalSize m_originalSize;
	const CurrentPacketNumber m_currentPacket;
	const TotalPacketNumber m_totalPackets;
	const FileName m_fileName;
	Buffer m_content; // TODO const?
};
