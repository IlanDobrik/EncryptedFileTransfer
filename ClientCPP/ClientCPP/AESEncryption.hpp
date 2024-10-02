#include <vector>

#include "Common.hpp"


static constexpr size_t AES_KEY_SIZE = 256;
static constexpr size_t IV_SIZE = 256 / 8;

class AES {
public:
    AES(const Buffer& key, const Buffer& iv = Buffer(0, IV_SIZE));

    Buffer encrypt(const Buffer& input);
    Buffer decrypt(const Buffer& cipher_text);

    static Buffer GenerateKey();

private:
    const Buffer m_key;
    const Buffer m_iv;
};
