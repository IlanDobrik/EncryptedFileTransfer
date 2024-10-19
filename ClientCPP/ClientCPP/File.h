#pragma once

#include <string>
#include <fstream>

#include "Common.h"
#include "Hardcoded.h"

class File {
public:
	explicit File(const std::string& filename, const std::ios_base::openmode mode);
	virtual ~File();

	Buffer read(const uint32_t size);
	void write(const std::string& data);

	OriginalSize getSize() const;
	std::string getName() const;

	std::string getLine();
	Buffer getLineBin();

	void seekStart();

private:
	const std::string m_path;
	std::fstream m_file;
};

