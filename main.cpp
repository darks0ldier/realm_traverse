#include "region_file.hpp"
#include "nbt_list_wrapper.hpp"
#include "realm.hpp"
#include "chunk.hpp"

#include <cNBT/nbt.h>

int main(int argc, char** argv)
{
	region_file* _region_file = new region_file();
	std::string realm_root = "resources/realms/_0";
	_region_file->set_region_file(realm_root, region_type::overworld, {0, 0});

	auto chunk = _region_file->fetch_chunk({0, 0});
	printf("Chunk Type: %d\n", chunk->type);

	// printf("%s", nbt_dump_ascii(chunk));
	
	auto _Level = std::shared_ptr<nbt_node>(nbt_find_by_name(chunk.get(), "Level"));
	auto _Sections = std::shared_ptr<nbt_node>(nbt_find_by_name(_Level.get(), "Sections"));    
	
	nbt_list_wrapper _list_wrapper = nbt_list_wrapper(_Sections->payload.tag_list);
	
	int index = 0;
	for (auto _iterator = _list_wrapper.cbegin(); _iterator != _list_wrapper.cend(); _iterator++)
	{
		printf("Sector Data #%d: %d\n", ++index, (*_iterator).type);
	}

	auto _realm = std::make_unique<realm>();
	_realm->assign_realm(realm_root);

	auto _chunk = _realm->fetch_chunk({0, 0}, region_type::overworld);
	printf("_chunk [modern approach] type: %d\n", _chunk->get_chunk_node().type);

	printf("%s\n", nbt_dump_ascii(&_chunk->get_chunk_node()));
	
	delete _region_file;
	return 0;
}

