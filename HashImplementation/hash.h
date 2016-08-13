#pragma once

#include "list.h"

class HashElem
{
public:
	char* index;
};

class Hash
{
public:
	Hash(int _n1, int _n2, int _n3, int _n4, int _n5, int size);
	~Hash();

	List* find_list(char* key_word);
	void add(HashElem* newEntry)
	{
		List* temp = find_list(newEntry->index);
		int key = combine_keys(newEntry->index);
		if (!temp)
			table[key] = new List(tableElemSize);
		table[key]->add(newEntry);
	}

	HashElem* find(char* key_word)
	{
		List* temp = find_list(key_word);
		if (!temp)
			return NULL;
		for (int i = 0; i < temp->count(); i++)
		{
			HashElem* ret = (HashElem*)(temp->get(i));
			if (!strcmp(ret->index, key_word))
				return ret;
		}
	}

protected:
	virtual int key1(char* key_word) { return 0; };
	virtual int key2(char* key_word) { return 0; };
	virtual int key3(char* key_word) { return 0; };
	virtual int key4(char* key_word) { return 0; };
	virtual int key5(char* key_word) { return 0; };
	int combine_keys(char* key_word)
	{
		return combine_keys(abs(key1(key_word)) % n1, abs(key2(key_word)) % n2, abs(key3(key_word)) % n3, 
			abs(key4(key_word)) % n4, abs(key5(key_word)) % n5);
	}
    int combine_keys(int k1, int k2, int k3, int k4, int k5)
	{  
		return 	k1+
			k2*n1+
			k3*n1*n2+
			k4*n1*n2*n3+
			k5*n1*n2*n3*n4;
	}
protected:
	List** table;
	int    tableElemSize;
private:
	int    n1,n2,n3,n4,n5;
};

class Article : public HashElem
{
public:
	char* description;
	int size;
	//void* ptr;
};


class Diction_list : public List
{
public:
	Diction_list() : List(sizeof(Article)){}
	~Diction_list(); // purge all Article data

	void     put(Article* article); // allocate memory for word & description
	Article* find(char* word);
	int      findIndex(char* word);
	void     del(Article* article) { del(article->index); }
	void     del(char* word);
};

class Diction : public Hash
{
public: 
	Diction(int size) : Hash(26, 26, 0, 0, 0, size) {  }
	~Diction() {}
	
	int key1(char* key_word) 
	{ 
		int f = key_word[0]-'À';
		if (f<26 && f>0) 
			return f;
		else             
			return 0; 
	}
	int key2(char* key_word) 
	{ 
		if (strlen(key_word) < 2)
			return 25;
		return (key_word[1] + 64) % 25; 
	}
	/*
	void add(Article* elem);
	Article* find (char* word);
	Article* auto_create(char* word);*/
};