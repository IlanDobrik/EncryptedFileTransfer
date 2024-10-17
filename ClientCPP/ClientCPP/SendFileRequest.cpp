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
{ }

Buffer SendFileRequest::serializePayload()
{
	uint32_t payloadSize = sizeof(m_contentSize) + sizeof(m_originalSize) + \
		sizeof(m_currentPacket) + sizeof(m_totalPackets) + \
		sizeof(m_fileName) + static_cast<uint32_t>(m_content.size());
	Buffer out(payloadSize, 0);

	auto p = out.begin();

	p = write_primitive(p, m_contentSize);
	p = write_primitive(p, m_originalSize);
	p = write_primitive(p, m_currentPacket);
	p = write_primitive(p, m_totalPackets);
	p = write_buffer(p, m_fileName);
	p = write_buffer(p, m_content);

	return out;
}
