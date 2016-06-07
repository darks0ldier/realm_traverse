#include "realm.hpp"
#include "region_file.hpp"
#include "chunk.hpp"

realm::realm()
{
	regions_map = std::make_unique<std::unordered_map<uint32_t, std::shared_ptr<region_file> > >();
	realm_root = "";
}

realm::~realm()
{
    
}

uint32_t realm::compress_into_single(location::map_location _location)
{
	return (_location.x << 16) ^ _location.z;
}

void realm::assign_realm(std::string& realm_root)
{
	this->realm_root = realm_root;
}

std::shared_ptr<chunk> realm::fetch_chunk(location::map_location chunk_location, region_type type)
{
	location::map_location region_location = {chunk_location.x & 31, chunk_location.z & 31};
	std::shared_ptr<region_file> _region_file = std::shared_ptr<region_file>(nullptr);

	uint32_t region_location_compressed = compress_into_single(region_location);
	
	if (regions_map->count(region_location_compressed) == 0)
	{
		_region_file = std::make_shared<region_file>();
		_region_file->set_region_file(realm_root, type, region_location);
		(*regions_map)[region_location_compressed] = _region_file;
	}
	else
	{
		_region_file = regions_map->at(region_location_compressed);
	}
	
	return std::make_shared<chunk>( _region_file->fetch_chunk(chunk_location));
}
