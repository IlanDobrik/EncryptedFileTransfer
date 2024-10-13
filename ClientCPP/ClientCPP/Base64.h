#pragma once

#include "cryptopp\base64.h"

#include "Common.h"


class Base64 {
public:
	static Buffer encode(const Buffer& input);
	static Buffer decode(const Buffer& input);
};

