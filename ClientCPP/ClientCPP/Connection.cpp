#include "Connection.h"

Connection::Connection(const std::string& address, const std::string& port) :
	m_ioContext(), m_socket(_initialize_socket(m_ioContext, address, port))
{ }

Buffer Connection::read()
{
	// boost::asio::read()
	return Buffer();
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
