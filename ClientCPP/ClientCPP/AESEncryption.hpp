#include <vector>

#include "Common.hpp"


class AES {
public:
    AES(const Buffer& key, const Buffer& iv);

    Buffer encrypt(const Buffer& input);
    Buffer decrypt(const Buffer& cipher_text);

private:
    const Buffer m_key;
    const Buffer m_iv;
};
