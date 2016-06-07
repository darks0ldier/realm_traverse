#pragma once
#include <cstdint>
#include <cstring>

typedef char byte;

namespace byte_utils
{
	uint32_t pack_bytes(const byte* bytes, size_t offset, uint8_t count);
};
