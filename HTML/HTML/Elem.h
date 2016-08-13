
#pragma once
#include "List.h"
#include <string>

using namespace std;

class Elem
{
protected:
	Elem* next;
	friend class List;
	friend class Iter;
public:
	Elem* next_elem()
	{
		return next;
	}
	virtual string getElem() = 0;
};