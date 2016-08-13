#include "stdafx.h"
#include "List.h"

#define LISTSIZE 64


List::List(int _element_size, int _element_count)
{
	element_size = _element_size;
	element_count = _element_count;
	first_index = 0;
	last_index = -1;
	first = NULL;
	last = NULL;
	error = false;
}

List::~List()
{
	Segment* cur = last;
	while (last)
	{
		last = cur->prev;
		delete_segment(cur);
		cur = last;
	}
	last = NULL;
	first = NULL;
}

void List::delete_segment(Segment* seg)
{
	//Segment* cur = first;
	//while (cur != seg && cur != NULL) cur = cur->next;
	heap->free_mem(seg->data);
	seg->data = NULL;
	seg->prev = NULL;
	seg->next = NULL;
	heap->free_mem((void*)seg);
}

void List::add(void* data)
{
	error = false;
	if (!first || last_index% element_count == element_count - 1)
	{
		new_segment();
		memcpy((char*)last->data, data, element_size);
		last_index++;
	}
	else memcpy((char*)last->data+(++last_index%element_count)*element_size, data, element_size);
}

void List::new_segment()
{
	Segment* seg = (Segment*)heap->get_mem(sizeof(Segment));
	seg->data=heap->get_mem(element_count*element_size);
	if (first == NULL)
	{
		first = seg;
		last = seg;
		seg->next = NULL;
		seg->prev = NULL;
		return;
	}
	seg->next = NULL;
	seg->prev = last;
	last = seg;
	seg->prev->next = seg;
}

void* List::get(int pos)
{
	error = false;
	if (pos<0 || pos>count() || count()==0)
	{
		error = true;
		return NULL;
	}
	
	//if(pos < element_count - first_index%element_count)
	//	return (void*)((char*)first->data+(first_index+pos%element_count)*element_size);

	Segment* cur = first;
	int cur_index = 0;
	while (cur_index + element_count - 1 < pos + first_index)
	{
		cur = cur->next;
		cur_index += element_count;
	}
	return (void*)((char*)cur->data+((first_index + pos) % element_count)*element_size);
}


void List::set(int pos, void* dat)
{
	void* toset = get(pos);
	memcpy(toset, dat, element_size);
}

int List::count()
{
	error = false;
	return last_index - first_index + 1;
}

void List::take_first(void* store)
{
	error = false;
	if (count()==0)
	{
		error = true;
		return;
	}
	memcpy(store, (char*)first->data+(first_index%element_count)*element_size, element_size);
	if (++first_index % element_count == 0)
	{
		if (first->next) first->next->prev = NULL;
		else
		{
			delete_segment(first);
			first = NULL;
			last = NULL;
			return;
		}
		Segment* cur = first;
		first = first->next;
		delete_segment(cur);
		cur = NULL;
	}
}

void List::take_last(void* store)
{
	error = false;
	if (count()==0)
	{
		error = true;
		return;
	}
	store = last->data;
	memcpy(store, (char*)last->data+(last_index%element_count)*element_size, element_size);
	if (last_index-- % element_count == 0)
	{
		if (last->prev) last->prev->next = NULL;
		else
		{
			delete_segment(last);
			first = NULL;
			last = NULL;
			return;
		}
		Segment* cur = last;
		last = last->prev;
		delete_segment(cur);
	}
}

void List::take(int pos, void* store)
{
	error = false;
	if (pos<0 || pos>count() || count() == 0)
	{
		error = true;
		return;
	}
	if (pos == 0) 
	{
		take_first(store);
		return;
	}
	if (pos == count() - 1)
	{
		take_last(store);
		return;
	}

	//memcpy(store, get(pos), element_size);

	Segment* temp = first;
	for (int i = 0; i < (first_index + pos) / element_count; i++)
		temp = temp->next;
	memcpy(store, (void*)((char*)temp->data + element_size*((first_index + pos) % element_count)), element_size);

	void* save = (heap->get_mem(sizeof(int)));
	take_first(save);
	pos = (first_index + pos - 1) % element_count;
	while (temp)
	{
		for (int i = pos; i >(temp == first ? first_index : 0); i--)
			memcpy((void*)((char*)(temp->data) + i*element_size), (void*)((char*)(temp->data) + (i - 1)*element_size), element_size);
		pos = element_count - 1;
		if (!(temp->prev))
			memcpy((void*)((char*)(temp->data) + (temp == first ? first_index * element_size : 0)), save, element_size);
		else
			memcpy((void*)((char*)(temp->data) + (temp == first ? first_index * element_size : 0)),
			(void*)((char*)(temp->prev->data) + element_size*(element_count - 1)),
			element_size);
		temp = temp->prev;
	}


	/*Segment* Cur = first;
	for (int i = 0; i < pos; i++) Cur = Cur->next;
	Segment* Prev = Cur->prev;
	Segment* Next = Cur->next;
	if (Prev) Prev->next = Cur->next;
	else
	{
		first = first->next;
		first_index++;
		last_index++;
	}
	if (Next) Next->prev = Cur->prev;
	else last = last->prev;
	store = Cur->data;
	delete_segment(Cur);
	Cur = NULL;
	last_index--;*/
}

void List::sort(bool dir, int compare(void*, void *))
{
	for (int i = count() - 1; i >= 0; i--)
		for (int j = 0; j < i; j++)
		{
		void *t1 = get(j);
		void *t2 = get(j + 1);
		if (compare(t1, t2) == 1 && dir || compare(t1, t2) == -1 && !dir)
		{
			swap(t1, t2);
		}
		}
}


void List::swap(void*& a, void*& b)
{
	void* temp = heap->get_mem(element_size);
	memcpy(temp, a, element_size);
	memcpy(a, b, element_size);
	memcpy(b, temp, element_size);
}

int intComparer(void* c, void* d)
{
	int a = *((int*)c);
	int b = *((int*)d);
	if (a < b)
		return -1;
	if (a > b)
		return 1;
	return 0;
}
