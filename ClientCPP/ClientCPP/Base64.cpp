#include "Base64.h"

Buffer Base64::encode(const Buffer& input)
{
    if (input.empty()) {
        return input;
    }

    Buffer encoded;
    CryptoPP::VectorSource ss(input, true,
        new CryptoPP::Base64Encoder(new CryptoPP::VectorSink(encoded)));
    return encoded;
}


Buffer Base64::decode(const Buffer& input)
{
    if (input.empty()) {
        return input;
    }

    Buffer decoded;
    CryptoPP::VectorSource ss(input, true,
        new CryptoPP::Base64Decoder(new CryptoPP::VectorSink(decoded)));
    return decoded;
}