#pragma once

#include <exception>
#include <string>


class ClientException : public std::exception
{
public:
	explicit ClientException(const std::string& what);
	virtual ~ClientException() = default;
	const char* what() const;

private:
	const std::string m_what;
};

