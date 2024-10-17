#pragma once

#include "cryptopp\base64.h"

#include "Common.h"


namespace Base64 {
	Buffer encode(const Buffer& input);
	Buffer decode(const Buffer& input);
};

