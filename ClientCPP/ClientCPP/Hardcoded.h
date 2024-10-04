#pragma once

#include <cstdint>
#include <array>

constexpr uint8_t CLIENT_VERSION = 1;

// IRequest
using Version = uint8_t;
using ClientID = std::array<uint8_t, 16>;
using Code = uint16_t;
using PayloadSize = uint32_t;

// RegisterRequest
using ClientName = std::array<uint8_t, 255>;

// AesRequest
using PublicKey = std::array<uint8_t, 160>;


constexpr uint8_t REQUEST_HEADER_SIZE = sizeof(ClientID) + sizeof(Version) + sizeof(Code) + sizeof(PayloadSize);
constexpr uint8_t RESPONSE_HEADER_SIZE = sizeof(Version) + sizeof(Code) + sizeof(PayloadSize);