#pragma once
#include "hash.h"

class Automaton
{
public:
	Automaton(char*);
	void Test();
	char* define(char* source, int &position, char* &error, bool trace = false);
private:
	// ������� �������
	int alphabetN;
	char** alphabet;
	// ���������
	int statesN;
	char** states;
	// ������
	int errorsN;
	char** errors; 
	// ������� ���������
	int tableM, tableN;
	char** table;        
};