#pragma once

namespace location
{
	struct map_location
	{
		int16_t x;
		int16_t z;
	};			 
	
	struct tile_location_global
	{
		int32_t x;
		uint8_t y;
		int32_t z;
	};

	struct tile_location_local
	{
		uint8_t x;
		uint8_t y;
		uint8_t z;
	};

	typedef char byte;
	typedef char block_id;

	
}
