#pragma once
#include "file_utils.hpp"
#include "byte_utils.hpp"
#include "location.hpp"
#include <cNBT/nbt.h>
#include <memory>

enum region_type
{
	overworld,
	nether,
	end
};

class region_file
{
private:
	std::fstream region_fs;
	
	file_utils::file_memory_block_info get_chunk_location(location::map_location chunk_location);
	static std::string compose_region_path(std::string& realm_root, region_type type, location::map_location region_location);
	
public:
	region_file();
	~region_file();

	void set_region_file(std::string& realm_root, region_type type, location::map_location region_location);

	std::shared_ptr<nbt_node> fetch_chunk(location::map_location chunk_location);
};
