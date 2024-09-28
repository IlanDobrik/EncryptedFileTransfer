#include "Base64.hpp"

Buffer Base64::encode(const Buffer& input)
{
    Buffer encoded;
    CryptoPP::StringSource ss(input.data(), true,
        new CryptoPP::Base64Encoder(new CryptoPP::VectorSink(encoded)));
    return encoded;
}


Buffer Base64::decode(const Buffer& input)
{
    Buffer decoded;
    CryptoPP::StringSource ss(input.data(), true,
        new CryptoPP::Base64Decoder(new CryptoPP::VectorSink(decoded)));
    return decoded;
}