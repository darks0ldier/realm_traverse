#include <cstring>
#include <cNBT/nbt.h>
#include "location.hpp"
#include "region_file.hpp"
#include <unordered_map>
#include <memory>

class chunk;

class realm
{
private:
	std::string realm_root;
	std::unique_ptr<std::unordered_map<uint32_t, std::shared_ptr<region_file> > > regions_map;

	uint32_t compress_into_single(location::map_location _location);
	
public:
	realm();
	~realm();

	void assign_realm(std::string& realm_root);
	std::shared_ptr<chunk> fetch_chunk(location::map_location chunk_location, region_type type);
};
