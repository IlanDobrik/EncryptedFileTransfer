#pragma once

#include "base64.h"

#include "Common.hpp"


class Base64 {
public:
	static Buffer encode(const Buffer& input);
	static Buffer decode(const Buffer& input);
};

