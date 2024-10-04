#pragma once

#include "boost/asio.hpp"

#include "Common.hpp"
#include "Hardcoded.h"


using boost::asio::ip::tcp;

class Connection {
public:
	Connection(const std::string& address, const std::string& port);
	virtual ~Connection() = default;

	Buffer read(const uint32_t size = DEFAULT_READ_SIZE);
	void write(const Buffer& data);

private:
	static tcp::socket _initialize_socket(boost::asio::io_context& io_context, const std::string& address, const std::string& port);

private:
	boost::asio::io_context m_ioContext;
	tcp::socket m_socket;
};