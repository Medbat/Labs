#pragma once
#include "Heap.h"

#define LISTSIZE 64
int intComparer(void*, void*);
class List
{
public:
	List(int _element_size, int _element_count = LISTSIZE);
	~List();

	void*      get(int pos);
	void       set(int pos, void*);
	void       add(void* data);

	// returns and deletes elements
	void       take_first(void* store);
	void       take_last(void* store);
	void       take(int pos, void* store);
	void       sort(bool dir, int compare(void*, void *) = intComparer);

	int        count();
	bool       Error() { return error; } // true if error in last operation
private:
	struct Segment
	{
		void*    data;
		Segment* prev;
		Segment* next;
	};
	Segment*         first;
	Segment*         last;
	int              first_index;
	int              last_index;

	int              element_size;
	int              element_count;
	bool             error;

	void new_segment();
	void delete_segment(Segment* seg);
	Segment* find(int pos)
	{
		Segment* temp = first;
		for (int i = 0; i < pos; i++)
			temp = temp->next;
		return temp;
	}
	void swap(void*&, void*&);
};