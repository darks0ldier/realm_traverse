#pragma once
#include <iterator>
#include <type_traits>
#include <cNBT/nbt.h>

template<typename _Type,  typename _UnqualifiedType>
class nbt_list_iterator : public std::iterator<std::bidirectional_iterator_tag, _UnqualifiedType, std::ptrdiff_t, _Type*, _Type&>
{
	static_assert(std::is_same<_UnqualifiedType, nbt_node>::value, "_UnqualifiedType @ nbt_list_wrapper::nbt_list_iterator required to be of nbt_node type.");

private:
	list_head* list_entry;
	list_head* current_position;

public:   
	nbt_list_iterator(list_head* _list_entry, list_head* _current_position){
		list_entry = _list_entry;
		current_position =  _current_position;
	}
	~nbt_list_iterator() { }

	nbt_list_iterator& operator=(nbt_list_iterator& other){
		list_entry = other.list_entry;
		current_position = other.current_position;
		return *this;
	}
	
	nbt_list_iterator& operator++(){
		current_position = current_position->flink;
		return *this;
	}
	nbt_list_iterator operator++(int){
		nbt_list_iterator saved = *this;
		++(*this);
		return saved;
	}

	nbt_list_iterator& operator--(){
		current_position = current_position->blink;
		return *this;
	}
	nbt_list_iterator operator--(int){
		nbt_list_iterator saved = *this;
		--(*this);
		return saved;
	}

	template<typename _OtherType, typename _OtherUnqualifiedType>
	bool operator==(const nbt_list_iterator<_OtherType, _OtherUnqualifiedType>& other){
		return current_position == other.current_position;
	}

	template<typename _OtherType, typename _OtherUnqualifiedType>
	bool operator!=(const nbt_list_iterator<_OtherType, _OtherUnqualifiedType>& other){
		return current_position != other.current_position;
	}

	_Type& operator*() const{
		return *list_entry(current_position, nbt_list, entry)->data;
	}
	_Type& operator->() const{
		return *list_entry(current_position, nbt_list, entry)->data;
	}
};
