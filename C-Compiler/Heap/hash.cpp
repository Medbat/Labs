#include "stdafx.h"
#include "hash.h"
bool isEqual(char*, char*);

DataBase* Base = new DataBase();

Hash::Hash(int _n1, int _n2, int _n3, int _n4, int _n5)
{
	n1 = _n1;
	n2 = _n2;
	n3 = _n3;
	n4 = _n4;
	n5 = _n5;
	if (n2 == 0 && n3 == 0 && n4 == 0 && n5 == 0)
	{
		table = (List**)heap->get_mem(n1*sizeof(List*));
		return;
	}
	if (n3 == 0 && n4 == 0 && n5 == 0)
	{
		table = (List**)heap->get_mem(n1*n2*sizeof(List*));
		return;
	}
	if (n4 == 0 && n5 == 0)
	{
		table = (List**)heap->get_mem(n1*n2*n3*sizeof(List*));
		return;
	}
	if (n5 == 0)
	{
		table = (List**)heap->get_mem(n1*n2*n3*n4*sizeof(List*));
		return;
	}
	table = (List**)heap->get_mem(n1*n2*n3*n4*n5*sizeof(List*));
}

Hash::~Hash()
{
	heap->free_mem(table);
	table = NULL;
}

char* Hash::NestingLevelUp(char* nestLevel)
{

	char temp[1024] = "";
	int length = 0;
	int i = strlen(nestLevel) - 1;
	bool lvlUp = false;
	while (i != 0)
	{
		//Копируем сначала название переменной
		while (i >= 0 && nestLevel[i] != '.')
		{
			temp[length++] = nestLevel[i];
			i--;
		}
		if (i < 0) break;
		i--;
		lvlUp = true;//Точно апнулись
		while (i >= 0 && nestLevel[i] != '.')
		{
			i--;
		}
		if (i < 0) break;//конец
		while (i >= 0) temp[length++] = nestLevel[i--];
		break;//Не знаю зачем нужен этот большой внешний цикл, но пусть будет так
	}
	if (!lvlUp) return NULL;
	char *result = (char*)heap->get_mem((length + 1)*sizeof(char));
	for (int i = 0; i < length / 2; i++)//Переворачиваем массив, ибо в обратном порядке всё 
		swap(temp[i], temp[length - i - 1]);
	strcpy(result, temp);
	return result;
}

List* Hash::find_list(char*& key_word)
{
	char* tempKeyword = (char*)heap->get_mem(strlen(key_word)*sizeof(char));
	strcpy(tempKeyword, key_word);
	while (key_word && !((Lexem_List*)table[combine_keys(key1(key_word), key2(key_word), key3(key_word), key4(key_word), key5(key_word))])->find(key_word))
	{
		key_word = NestingLevelUp(key_word);
	}
	if (!key_word) key_word = tempKeyword;
	return table[combine_keys(key1(key_word), key2(key_word), key3(key_word), key4(key_word), key5(key_word))];
}

Diction_list::~Diction_list()
{
	void* toJunk = heap->get_mem(sizeof(void*));
	while (count()) take_first(toJunk);
}

void Diction_list::put(Article* article)
{
	add(article);
}

Article* Diction_list::find(char* word)
{
	int index = 0;
	while (isEqual(((Article*)get(index))->word, word) && index < count())
		index++;
	if (index == count()) return NULL;
	return (Article*)get(index);
}

void Diction_list::del(char* word)
{
	int index = 0;
	while (((Article*)get(index))->word != word && index < count())
		index++;
	if (index == count()) return;
	void* toJunk = heap->get_mem(sizeof(void*));
	take(index, toJunk);
}


Diction::~Diction()
{
	char* temp = (char*)heap->get_mem(2*sizeof(char));
	for (char i = 'A'; i < 'Я'; i++)
	{
		*temp = i;
		for (char j = 'A'; j < 'Я'; j++)
		{
			*(char*)((int)temp + sizeof(char)) = j;
			heap->free_mem((void*)find_list(temp));
		}
	}
	heap->free_mem((void*)temp);
}

Article* Diction::find(char* word)
{
	return ((Diction_list*)find_list(word))->find(word);
}

Article* Diction::auto_create(char* word)
{
	if (!((Diction_list*)find_list(word))->find(word))
	{
		Article* result = (Article*)heap->get_mem(sizeof(Article*));
		result->description[0] = '\0';
		int length = 0;
		for (length = 0; word[length] != '\0'; length++);

		result->word = (char*)heap->get_mem(sizeof(word)*length);
		for (int i = 0; i < length; i++)
		{
			result->word[i] = word[i];
		}
		result->word[length] = '\0';

		((Diction_list*)find_list(word))->add(word);
	}
	return ((Diction_list*)find_list(word))->find(word);
}

void Lexem_List::put(Lexem* var)
{
	add(var);
}

Lexem* Lexem_List::find(char* word)
{
	int index = 0;
	while (index < count() && !isEqual(((Lexem*)get(index))->GetKeyword(), word))
		index++;
	if (index == count()) 
		return NULL;
	Lexem* temp = (Lexem*)get(index);
	
	return temp;
}

void Lexem_List::del(char* word)
{
	int index = 0;
	while (((Lexem*)get(index))->GetKeyword()!= word && index < count())
		index++;
	if (index == count()) return;
	void* toJunk = heap->get_mem(sizeof(void*));
	take(index, toJunk);
	heap->free_mem(toJunk);
}

DataBase::DataBase() : Hash(100, 25)
{
	for (int i = 0; i < 100*25; i++)
	{
		table[i] = new Lexem_List();
	}
}

//void DataBase::FillTheHash(char* temp, char a)
//{
//	List* templist = NULL;
//	temp[0] = a;
//	for (char j = 'A'; j < 'Z'; j++)
//	{
//		temp[1] = j;
//		templist = find_list(temp);
//		templist = new Lexem_List();
//	}
//	for (char j = 'a'; j < 'z'; j++)
//	{
//		temp[1] = j;
//		templist = find_list(temp);
//		templist = new Lexem_List();
//	}
//	temp[1] = '_';
//	templist = find_list(temp);
//	templist = new Lexem_List();
//}

DataBase::~DataBase()
{
	char* temp = (char*)heap->get_mem(2 * sizeof(char));
	List* templist = NULL;
	temp[0] = 'v';
	for (char j = 'A'; j < 'Z'; j++)
	{
		temp[1] = j;
		templist = find_list(temp);
		delete templist;
	}
	for (char j = 'a'; j < 'z'; j++)
	{
		temp[1] = j;
		templist = find_list(temp);
		delete templist;
	}
	temp[1] = '_';
	templist = find_list(temp);
	delete templist;
}

Lexem* DataBase::find(char* keyWord)
{
	Lexem_List* temp = (Lexem_List*)find_list(keyWord);
	return temp->find(keyWord);
}

char* DataBase::NestingLevelUp(char* nestLevel)
{

	char temp[1024] = "";
	int length = 0;
	int i = strlen(nestLevel) - 1;
	bool lvlUp = false;
	while (i != 0)
	{
		if (i < 0) break;
		i--;
		lvlUp = true;//Точно апнулись
		while (i >= 0 && nestLevel[i] != '.')
		{
			i--;
		}
		if (i < 0) break;//конец
		while (i >= 0) temp[length++] = nestLevel[i--];
		break;//Не знаю зачем нужен этот большой внешний цикл, но пусть будет так
	}
	if (!lvlUp) return NULL;
	char *result = (char*)heap->get_mem((length + 1)*sizeof(char));
	for (int i = 0; i < length / 2; i++)//Переворачиваем массив, ибо в обратном порядке всё 
		swap(temp[i], temp[length - i - 1]);
	strcpy(result, temp);
	return result;
}
Lexem* DataBase::auto_create(Lexem*& lex, bool isNewVar)
{
	char* nestingLevel = NULL;
	if (lex->GetNestingLevel())
	{
		nestingLevel = (char*)heap->get_mem(strlen(lex->GetNestingLevel()) + 1);
		strcpy(nestingLevel, lex->GetNestingLevel());
	}
	
	char* keyword = (char*)heap->get_mem(strlen(lex->GetKeyword()) + 1);
	strcpy(keyword, lex->GetKeyword());
	
	Lexem* tempLexem = new Lexem(*lex);
	Lexem* res = ((Lexem_List*)find_list(keyword))->find(keyword);
	
	if (!isNewVar)//Ищем переменную выше, если только это не объявление переменной
		while (nestingLevel != NULL && res == NULL)
		{
			nestingLevel = NestingLevelUp(nestingLevel);
			tempLexem->SetNestingLevel(nestingLevel, (nestingLevel ? strlen(nestingLevel) : 0));
			strcpy(keyword, tempLexem->GetKeyword());
			res = ((Lexem_List*)find_list(keyword))->find(keyword);
		}
	
	if (!res)
	{
		Lexem* result = new Lexem(*(Lexem*)lex);
		result->SwitchToVariable();
		char* temp = lex->GetKeyword();
		((Lexem_List*)find_list(temp))->add(result);
		return result;
	}
	lex = res;
	//lex->SetNestingLevel(res->GetNestingLevel(), res->GetNestingLevelLength());
	return res;
}

bool isEqual(char* a, char* b)
{
	int acount = 0, bcount = 0;
	for (int i = 0; a[i] != '\0'; i++) acount++;
	for (int i = 0; b[i] != '\0'; i++) bcount++;
	if (acount != bcount) return false;

	for (int i = 0; i < acount; i++)
	{
		if (a[i] != b[i]) return false;
	}

	return true;
}