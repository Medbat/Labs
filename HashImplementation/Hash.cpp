#include "hash.h"

Hash::Hash(int _n1, int _n2, int _n3, int _n4, int _n5, int size)
{
	n1 = _n1 <= 0 ? 1 : _n1;
	n2 = _n2 <= 0 ? 1 : _n2;
	n3 = _n3 <= 0 ? 1 : _n3;
	n4 = _n4 <= 0 ? 1 : _n4;
	n5 = _n5 <= 0 ? 1 : _n5;
	int count = n1*n2*n3*n4*n5;
	table = (List**)heap.get_mem(sizeof(List*) * count);//new List*[count];
	for (int i = 0; i < count; i++)
		table[i] = NULL;
	tableElemSize = size;
}

Hash::~Hash()
{
	for (int i = 0; i < n1*n2*n3*n4*n5; i++)
		if (table[i])
			delete table[i];
	delete table;
}

List* Hash::find_list(char* key_word)
{
 	return table[combine_keys(key_word)];
}


Diction_list::~Diction_list()// purge all Article data
{
	void* temp = heap.get_mem(sizeof(Article));
	while (count() > 0)
	{
		take_first(temp);
		del((Article*)temp);
	}
	heap.free_mem(temp);
}

void Diction_list::put(Article* article)// allocate memory for word & description
{
	add((void*)article);
}

Article* Diction_list::find(char* word)
{
	if (!this)
		return NULL;
	int Count = count();
	Article* temp;
	for (int i = 0; i < Count; i++)
	{
		if (!strcmp((temp = (Article*)get(i))->index, word))
			return temp;
	}
	return NULL;
}

int Diction_list::findIndex(char* word)
{
	int Count = count();
	for (int i = 0; i < Count; i++)
	{
		if (!strcmp(((Article*)get(i))->index, word))
			return i;
	}
	return -1;
}

void Diction_list::del(char* word)
{
	int pos = findIndex(word);
	if (pos != -1)
	{
		void* temp = heap.get_mem(sizeof(Article));
		take(pos, temp);
		heap.free_mem(temp);
	}
}

/*
Article* Diction::find(char* word)
{
	return ((Diction_list*)find_list(word))->find(word);
}
Article* Diction::auto_create(char* word)
{
	Article *a = (Article*)heap.get_mem(sizeof(Article));
	a->index = (char*)heap.get_mem(strlen(word) + 1);
	memcpy(a->index, word, strlen(word) + 1);
	a->description = (char*)heap.get_mem(strlen(word) + 1);
	memcpy(a->description, word, strlen(word) + 1);
	return a;
}

void Diction::add(Article* elem)
{
	//Diction_list* list = ((Diction_list*)find_list(elem->word));
	int ind = combine_keys(elem->index);
	if (!table[ind])
		table[ind] = new Diction_list();
	((Diction_list*)table[ind])->put(elem);
}
*/
