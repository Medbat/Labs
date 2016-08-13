
#pragma once
#define NULL 0

#include "Iter.h"
#include "Elem.h"

class List
{
protected:
	friend class Iter;
	Elem* first;
public:
	List() : first(NULL) {};
	~List()
	{
	}
	int length()
	{
		int ret = 0;
		Elem* temp = first;
		while (temp)
		{
			ret++;
			temp = temp -> next;
		}
		return ret;
	}
	void push(Elem* El)
	{
		El->next = first;
		first = El;
	}
	Elem* pop()
	{
		Elem *p = first;
		if (p)
			first = p->next;
		return p;
	}
	bool empty();
	Iter begin()
	{
		Iter tmp;
		tmp.current_elem = first;
		return tmp;
	}
	Iter end()
	{
		Iter tmp;
		tmp.current_elem = 0;
		return tmp;
	}
};