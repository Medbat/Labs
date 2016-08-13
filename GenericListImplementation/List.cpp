#include "list.h"
#include <utility>

List::List(int _element_size, int _element_count)
{
	element_size = _element_size;
	element_count = _element_count;
	first = last = NULL;
}

void List::add(void* data)
{
	if (!last || (last_index + 1) % element_count == 0)
		new_segment();
	last_index++;
	//memcpy((void*)((char*)(last->data) + (last_index % element_count) * element_size), data, element_size);
	*((char*)(last->data) + (last_index % element_count) * element_size) = *(char*)data;
}

void List::new_segment()
{
	Segment* temp = (Segment*)(heap.get_mem(sizeof(Segment)));
	temp->data = heap.get_mem(element_size * element_count);

	temp->next = temp->prev = NULL;
	if (last == NULL)
	{
		first = last = temp;
		first_index = 0; 
		last_index = -1;
	}
	else
	{
		last->next = temp;
		temp->prev = last;
		last = temp;
	}
}

int List::count()
{
	if (!first)
		return 0;
	return last_index - first_index + 1;
}

// я прошу нулевой
void* List::get(int pos)
{
	if (pos < 0 || pos >= count())
	{
		error = true;
		return NULL;
	}
	Segment* temp = first;
	for (int i = 0; i < (first_index + pos) / element_count; i++)
		temp = temp->next;
	return (void*)((char*)temp->data + element_size*((first_index + pos) % element_count));
}

void List::take_first(void* store)
{
	if (!first)
	{
		error = true;
		return;
	}
	memcpy(store, (void*)((char*)first->data + first_index * element_size), element_size);
	first_index++;
	if (first_index == element_count)
	{
		Segment* temp = first;
		first = first->next;
		if (first)
			first->prev = NULL;	
		delete_segment(temp);
		first_index = 0;
		last_index -= element_count;
	}
}

void List::take_last(void* store)
{
	if (!last)
	{
		error = true;
		return;
	}
	memcpy(store, (char*)last->data + (last_index % element_count) * element_size, element_size);
	last_index--;
	if (!((last_index + 1) % element_count))
	{
		if (last == first)
		{
			delete_segment(last);
			last = first = NULL;
			return;
		}
		Segment* temp = last;
		last->prev->next = NULL;
		last = last->prev;
		delete_segment(temp);
	}
}

void List::take(int pos, void* store)
{
	if (!last || pos >= count() || pos < 0)
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

	Segment* temp;
	temp = first;
	for (int i = 0; i < (first_index + pos) / element_count; i++)
		temp = temp->next;
	memcpy(store, (void*)((char*)temp->data + element_size*((first_index + pos) % element_count)), element_size);

	void* save = (heap.get_mem(sizeof(int)));
	take_first(save);
	pos = (first_index + pos - 1) % element_count;
	while (temp)
	{
		for (int i = pos; i > (temp==first?first_index:0); i--)
			memcpy((void*)((char*)(temp->data) + i*element_size), (void*)((char*)(temp->data) + (i - 1)*element_size), element_size);
		pos = element_count - 1;
		if (!(temp->prev))
			memcpy((void*)((char*)(temp->data) + (temp == first ? first_index * element_size : 0)), save, element_size);
		else
			memcpy((void*)((char*)(temp->data) + (temp == first ? first_index * element_size : 0)), 
			(void*)((char*)(temp->prev->data) + element_size*(element_count-1)), 
			element_size);
		temp = temp->prev;
	}
	
}

void List::delete_segment(Segment* seg)
{
	heap.free_mem(seg->data);
	heap.free_mem(seg);
}

List::~List()
{
	Segment* temp = first;
	while (temp != NULL)
	{
		first = temp->next;
		delete_segment(temp);
		temp = first;
	}
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

/*
List::List(int _element_size, int _element_count)
{
	element_size = _element_size;
	element_count = _element_count;
	first = last = NULL;
}

void* List::get(int pos)
{
	error = false;
	if (first == NULL || (pos < 0 || pos >= count()))
	{
		error = true;
		return NULL;
	}

	Segment* temp = first;
	for (int i = 0; i < pos; i++)
		temp = temp->next;

	return temp->data;
}


void List::add(void* data)
{
	error = false;
	if (count() >= element_count)
	{
		error = true;
		return;
	}
	new_segment();
	last->data = data;
}

void List::take_first(void*& store)
{
	error = false;
	if (first == NULL)
	{
		error = true;
		return;
	}

	store = first->data;

	Segment* temp = first;
	first = first->next;

	delete_segment(temp);
	if (first)
		first->prev = NULL;
	first_index++;
}

void List::take_last(void*& store)
{
	error = false;
	if (last == NULL)
	{
		error = true;
		return;
	}

	store = last->data;

	Segment* temp = last;
	last = last->prev;

	delete_segment(temp);
	if (last)
		last->next = NULL;
	last_index--;
}

void List::take(int pos, void*& store)
{
	error = false;
	if (last == NULL || (pos < 0 || pos >= count()))
	{
		error = true;
		return;
	}
	
	Segment* temp = first;
	for (int i = 0; i < pos; i++)
		temp = temp->next;

	store = temp->data;

	if (temp == first)
	{
		take_first(store);
		return;
	}
	if (temp == last)
	{
		take_last(store);
		return;
	}

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete_segment(temp);
	last_index--;
}

void List::sort(bool dir, int compare(void*, void *))
{
	for (int i = count() - 1; i >= 0; i--)
		for (int j = 0; j < i; j++)
		{
			void *t1 = get(j);
			void *t2 = get(j+1);
			if (compare(t1, t2) == 1 && dir || compare(t1, t2) == -1 && !dir)
			{
				swap(find(j)->data, find(j + 1)->data);
			}
		}
}

void List::swap(void*& a, void*& b)
{
	void* temp = a;
	a = b;
	b = temp;
}

int intComparer(void* c, void* d)
{
	int a = *((int*) c);
	int b = *((int*) d);
	if (a < b)
		return -1;
	if (a > b)
		return 1;
	return 0;
}

int List::count()
{
	if (first == NULL)
		return 0;
	return last_index - first_index + 1;
}


void List::new_segment()
{
	Segment* temp = (Segment*)(heap.get_mem(sizeof(Segment)));
	temp->next = temp->prev = NULL;
	if (last == NULL)
	{
		first = last = temp;
		first_index = last_index = 0;
	}
	else
	{
		last->next = temp;
		temp->prev = last;
		last = temp;
		last_index++;
	}
}

void List::delete_segment(Segment* seg)
{
	heap.free_mem(seg);
}
*/