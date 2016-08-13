#pragma once
#include "Heap.h"
#include "List.h"
#include "Identificator.h"

class Hash
{
public:
	Hash(int _n1 = 0, int _n2 = 0, int _n3 = 0, int _n4 = 0, int _n5 = 0);
	~Hash();
	List* find_list(char*& key_word);
protected:
	virtual int key1(char* key_word) { return 0; }
	virtual int key2(char* key_word) { return 0; }
	virtual int key3(char* key_word) { return 0; }
	virtual int key4(char* key_word) { return 0; }
	virtual int key5(char* key_word) { return 0; }
	int combine_keys(int k1, int k2, int k3, int k4, int k5)
	{
		return  k1 +
			k2*n1 +
			k3*n2*n1 +
			k4*n3*n2*n1 +
			k5*n4*n3*n2*n1;
	}
	List** table;
private:

	char* NestingLevelUp(char* nestLevel);
	int    n1, n2, n3, n4, n5;
};

struct Article
{
	char* word;
	char* description;
};

class Diction_list : public List
{
public:
	Diction_list() : List(sizeof(Article)){};
	~Diction_list(); // purge all Article data

	void     put(Article* article); // allocate memory for word & description
	Article* find(char* word);
	void     del(Article* article) { del(article->word); }
	void     del(char* word);
};

class Diction : public Hash
{
public:
	Diction() : Hash(33, 33, 0, 0, 0){};
	~Diction();

	int key1(char* key_word) 
	{
		int f = key_word[0] - 'A';
		if (f<33 && f>0) 
			return f;
			f = key_word[0] - 'à';
		if (f<33 && f>0)
			return f;
		return 0;
	}

	int key2(char* key_word) 
	{
		int f = key_word[1] - 'A';
		if (f<33 && f>0) return f;
		else
		{
			f = key_word[1] - 'à';
			if (f<33 && f>0) return f;
		}
		return 0;
	}

	Article* find(char* word);
	Article* auto_create(char* word);
};


class DataBase : public Hash
{
	//void FillTheHash(char*, char);
public:
	DataBase();
	~DataBase();

	int key1(char* key_word)
	{
		int result = 0;
		for (int i = 0; i < strlen(key_word) - 1; i++)
			if (key_word[i] >= '0' && key_word[i] <= '9')
				result += key_word[i];
		return abs(result % 100);
	}

	int key2(char* key_word)
	{
		return abs(key_word[strlen(key_word) - 1] % 25);
	}

	Lexem* find(char* keyWord);
	char* NestingLevelUp(char* nestLevel);
	Lexem* auto_create(Lexem*& lex, bool isNewVar);
};

class Lexem_List : public List
{
public:
	Lexem_List() : List(sizeof(Lexem)){};
	~Lexem_List(); // purge all Lexem data
	void     put(Lexem* vari); // allocate memory
	Lexem* find(char* word);
	void     del(Lexem* vari) { del(vari->GetName()); }
	void     del(char* word);
};
extern DataBase* Base;