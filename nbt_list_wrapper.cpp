#include "nbt_list_wrapper.hpp"

nbt_list_wrapper::~nbt_list_wrapper()
{
}

nbt_list_wrapper::const_iterator nbt_list_wrapper::cbegin()
{
	return const_iterator(&list->entry, list->entry.flink);
}

nbt_list_wrapper::const_iterator nbt_list_wrapper::cend()
{
	return const_iterator(&list->entry, &list->entry);
}
