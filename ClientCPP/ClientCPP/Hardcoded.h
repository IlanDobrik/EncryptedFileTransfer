#pragma once

#include <cstdint>
#include <array>

#define TRANSFER_INFO_PATH "./transfer.info"
#define ME_PATH "./me.info"
#define RSA_PRIVATE_KEY_PATH "./priv.key"


constexpr uint8_t CLIENT_VERSION = 3;
constexpr uint32_t MAX_RETRY_COUNT = 3;
constexpr uint32_t DEFAULT_READ_SIZE = 1024;


// Request
using Version = uint8_t;
using ClientID = std::array<uint8_t, 16>;
using Code = uint16_t;
using PayloadSize = uint32_t;

// RegisterRequest
using ClientName = std::array<uint8_t, 255>;

// AesRequest
using PublicKey = std::array<uint8_t, 160>;

// SendFileRequest
using ContentSize = uint32_t;
using OriginalSize = uint32_t;
using CurrentPacketNumber = uint16_t;
using TotalPacketNumber = uint16_t;
using FileName = std::array<uint8_t, 255>;

constexpr uint8_t REQUEST_HEADER_SIZE = sizeof(ClientID) + sizeof(Version) + sizeof(Code) + sizeof(PayloadSize);
constexpr uint8_t RESPONSE_HEADER_SIZE = sizeof(Version) + sizeof(Code) + sizeof(PayloadSize);