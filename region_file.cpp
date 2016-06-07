#include "region_file.hpp"
#include <sstream>

#define FILE_SECTOR_SIZE 4096

region_file::region_file()
{
	region_fs = std::fstream();
}

region_file::~region_file()
{
	region_fs.close();
}

file_utils::file_memory_block_info region_file::get_chunk_location(location::map_location chunk_location)
{
	std::streampos header_offset = 4 * ((chunk_location.x & 31) + (chunk_location.z & 31) * 32);
	const byte* header_data = file_utils::retrieve_from_file(region_fs, {header_offset, 4});

	return {byte_utils::pack_bytes(header_data, 0, 3) * FILE_SECTOR_SIZE, byte_utils::pack_bytes(header_data, 3, 1) * FILE_SECTOR_SIZE};
}

std::string region_file::compose_region_path(std::string& realm_root, region_type type, location::map_location region_location)
{
	std::string realm_type_interfix = "";
	switch(type)
	{
	case region_type::overworld:
		realm_type_interfix = ""; break;
	case region_type::nether:
		realm_type_interfix = "DIM-1/"; break;
	case region_type::end:
		realm_type_interfix = "DIM1/"; break;
	};

	std::ostringstream fullpath_format_stream;
	fullpath_format_stream << realm_root << "/";
	fullpath_format_stream << realm_type_interfix << "region/";
	fullpath_format_stream << "r." << region_location.x << "." << region_location.z << ".mca";

	return fullpath_format_stream.str();
}

void region_file::set_region_file(std::string& realm_root, region_type type, location::map_location region_location)
{
	std::string region_path = region_file::compose_region_path(realm_root, type, region_location);
	this->region_fs.open(region_path.c_str(), std::ios::in | std::ios::binary);
}

std::shared_ptr<nbt_node> region_file::fetch_chunk(location::map_location chunk_location)
{
	file_utils::file_memory_block_info chunk_location_blob_info = this->get_chunk_location(chunk_location);

	std::unique_ptr<const byte> chunk_length_blob = std::unique_ptr<const byte>(file_utils::retrieve_from_file(region_fs, {chunk_location_blob_info.offset, 4}));
	std::streamsize chunk_length = byte_utils::pack_bytes(chunk_length_blob.get(), 0, 4);

	std::unique_ptr<const byte> compressed_chunk_data = std::unique_ptr<const byte>(file_utils::retrieve_from_file(region_fs, {chunk_location_blob_info.offset + 5, chunk_length - 1}));

	return std::shared_ptr<nbt_node>(nbt_parse_compressed(compressed_chunk_data.get(), chunk_length - 1));
}
