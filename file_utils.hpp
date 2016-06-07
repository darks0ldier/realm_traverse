#pragma once
#include <fstream>

typedef char byte;

namespace file_utils
{
	struct file_memory_block_info
	{
		std::streamoff offset;
		std::streamsize length;
	};    

	const byte* retrieve_from_file(std::fstream& file_stream, file_memory_block_info block_info);
};
	
