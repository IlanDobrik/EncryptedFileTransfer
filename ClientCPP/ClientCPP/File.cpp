#include "File.h"

#include <filesystem>


File::File(const std::string& filename, const std::ios_base::openmode mode) :
	m_path(filename)
{ 
	m_file = std::fstream(filename, mode);
	if (!m_file.is_open()) {
		throw std::exception("Failed to open file");
	}
}

File::~File()
{
	try {
		m_file.close();
	}
	catch (...) { }
}

Buffer File::read(const uint32_t size)
{
	Buffer chunk(size, 0);
	
	m_file.read(reinterpret_cast<char*>(chunk.data()), static_cast<std::streamsize>(chunk.size()));
	uint32_t bytesRead = static_cast<uint32_t>(m_file.gcount());
	chunk.resize(bytesRead);

	return chunk;
}

void File::write(const std::string& data)
{
	m_file << data.data();
}

ContentSize File::getSize() const
{
	return static_cast<ContentSize>(std::filesystem::file_size(m_path));
}

std::string File::getName() const
{
	auto lastSlash = m_path.find_last_of("\\/");
	if (std::string::npos == lastSlash) {
		return m_path;
	}

	return m_path.substr(lastSlash + 1);
}

std::string File::getLine()
{
	std::string line;
	std::getline(m_file, line);

	return line;
}

Buffer File::getLineBin()
{
	std::string line;
	std::getline(m_file, line);

	return Buffer(line.begin(), line.end());;
}
