#pragma once
#include <cNBT/nbt.h>
#include <memory>

class chunk
{
private:
	std::shared_ptr<nbt_node> chunk_node;
	
public:
	chunk(std::shared_ptr<nbt_node> _chunk_node);
	~chunk();

	nbt_node& get_chunk_node();
};
