#include "SendFileRequest.h"

SendFileRequest::SendFileRequest(const ClientID& clientId, 
	const ContentSize contentSize, const OriginalSize originalSize, 
	const CurrentPacketNumber currentPacket, const TotalPacketNumber totalPackets, 
	const FileName& fileName, const Buffer& content) :
	Request(clientId, SEND_FILE_REQUEST_CODE),
	m_contentSize(contentSize),
	m_originalSize(originalSize),
	m_currentPacket(currentPacket),
	m_totalPackets(totalPackets),
	m_fileName(fileName),
	m_content(content)
{
}

Buffer SendFileRequest::_serialize()
{
	uint32_t payloadSize = sizeof(m_contentSize) + sizeof(m_originalSize) + sizeof(m_currentPacket) + sizeof(m_totalPackets) + sizeof(m_fileName) + m_content.size();
	Buffer out(payloadSize, 0);

	auto p = out.begin();

	p = std::copy_n(reinterpret_cast<const uint8_t*>(&m_contentSize), sizeof(m_contentSize), p);
	p = std::copy_n(reinterpret_cast<const uint8_t*>(&m_originalSize), sizeof(m_originalSize), p);
	p = std::copy_n(reinterpret_cast<const uint8_t*>(&m_currentPacket), sizeof(m_currentPacket), p);
	p = std::copy_n(reinterpret_cast<const uint8_t*>(&m_totalPackets), sizeof(m_totalPackets), p);
	p = std::copy_n(reinterpret_cast<const uint8_t*>(&m_fileName), sizeof(m_fileName), p);
	p = std::copy_n(m_content.data(), m_content.size(), p);

	return out;
}
