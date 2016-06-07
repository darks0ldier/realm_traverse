#include "file_utils.hpp"

const byte* file_utils::retrieve_from_file(std::fstream& file_stream, file_utils::file_memory_block_info block_info)
{
	std::streamoff current_position = file_stream.tellg();
	file_stream.seekg(block_info.offset, std::ios_base::beg);

	byte* buffer = new byte[block_info.length];
	file_stream.read(buffer, block_info.length);
	file_stream.seekg(current_position, std::ios_base::beg);

	return const_cast<char*>(buffer);
}
