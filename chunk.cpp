#include "chunk.hpp"

chunk::chunk(std::shared_ptr<nbt_node> _chunk_node)
{
	chunk_node = _chunk_node;
}

chunk::~chunk()
{
	
}

nbt_node& chunk::get_chunk_node()
{
	return *(chunk_node.get());
}
