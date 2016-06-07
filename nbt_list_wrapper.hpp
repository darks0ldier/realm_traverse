#pragma once
#include "nbt_list_iterator.hpp"

class nbt_list_wrapper
{
private:
	nbt_list* list;
	
public:
	nbt_list_wrapper(nbt_list* _list) : list(_list) { }
	~nbt_list_wrapper();

	typedef nbt_list_iterator<nbt_node, nbt_node> iterator;
	typedef nbt_list_iterator<const nbt_node, nbt_node> const_iterator;
	
	nbt_list_wrapper::const_iterator cbegin();
	nbt_list_wrapper::const_iterator cend();
};
