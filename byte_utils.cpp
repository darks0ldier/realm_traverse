#include "byte_utils.hpp"

uint32_t byte_utils::pack_bytes(const byte* bytes, size_t offset, uint8_t count)
{   
	/*if ((offset + count > strlen(bytes)) | (count > 4)) return 0;*/

	uint32_t packed = 0;
	for (size_t index = 0; index < count; index++)
	{
		packed += (bytes[offset+index] << (8 * (count - 1 - index)));
	}

	return packed;
}
