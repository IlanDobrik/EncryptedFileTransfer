#include "ClientException.h"

ClientException::ClientException(const std::string& what) :
	m_what(what)
{ }

const char* ClientException::what() const
{
	return m_what.c_str();
}
