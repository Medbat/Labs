
#pragma once

#include "Elem.h"

class Iter
{
	friend class List;
	Elem* current_elem;
public:
	Iter() : current_elem(0) {}
	Iter operator++()
	{
		if (current_elem)
			current_elem = current_elem -> next_elem();
		return *this;
	}
	Elem& operator*() 
	{
		return *current_elem; 
	}
	Elem* operator->()
	{ 
		return current_elem; 
	}
	bool operator!=(Iter v)
	{
		return current_elem != v.current_elem;
	}
};