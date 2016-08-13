#pragma once
#include "hash.h"

class Automaton
{
public:
	Automaton(char*);
	void Test();
	char* define(char* source, int &position, char* &error, bool trace = false);
private:
	// входные символы
	int alphabetN;
	char** alphabet;
	// состояния
	int statesN;
	char** states;
	// ошибки
	int errorsN;
	char** errors; 
	// таблица переходов
	int tableM, tableN;
	char** table;        
};