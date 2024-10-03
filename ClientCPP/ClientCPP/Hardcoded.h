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

