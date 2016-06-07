#pragma once
#include <cNBT/nbt.h>
#include <memory>

class chunk
{
public:
	chunk(std::shared_ptr<nbt_node> chunk_node);
	~chunk();
};
