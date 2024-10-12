#include "Connection.h"

#include "IResponse.h"

Connection::Connection(const std::string& address, const std::string& port) :
	m_ioContext(), m_socket(_initialize_socket(m_ioContext, address, port))
{ }

Buffer Connection::read(const uint32_t size)
{
	boost::system::error_code error;
	boost::asio::streambuf receive_buffer;
	auto bytesRead = boost::asio::read(m_socket, receive_buffer, boost::asio::transfer_exactly(size), error);

	Buffer out(receive_buffer.size(), 0);
	receive_buffer.sgetn(reinterpret_cast<char*>(out.data()), out.size());

	return out;
}

void Connection::write(const Buffer& data)
{
	auto bytesWritten = boost::asio::write(m_socket, boost::asio::buffer(data.data(), data.size()));
	if (bytesWritten != data.size()) {
		throw std::exception("Failed to write all data");
	}
}

tcp::socket Connection::_initialize_socket(boost::asio::io_context& io_context, const std::string& address, const std::string& port)
{
	tcp::socket s(io_context);
	tcp::resolver resolver(io_context);
	boost::asio::connect(s, resolver.resolve(address, port));

	return s;
}
