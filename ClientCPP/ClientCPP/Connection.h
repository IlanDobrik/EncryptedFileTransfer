#pragma once

#include "Common.hpp"
#include "boost/asio.hpp"


using boost::asio::ip::tcp;

class Connection {
public:
	Connection(const std::string& address, const std::string& port);
	virtual ~Connection() = default;

	Buffer read();
	void write(const Buffer& data);

private:
	static tcp::socket _initialize_socket(boost::asio::io_context& io_context, const std::string& address, const std::string& port);

private:
	boost::asio::io_context m_ioContext;
	tcp::socket m_socket;
};