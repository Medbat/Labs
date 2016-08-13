#pragma once
#include "Heap.h"
#include "List.h"
#include <fstream>
#include <iostream>
class Automat
{
	int alphabetQuant;
	char **alphabet;
	int stateQuant;
	char **state;
	int errorQuant;
	char **error;
	int** table;

	int templen;
	char* tempname;
	char* tempstate;
	char* temperror;

	void CopyTempData(int i, char* text, char** state, int curstate);
	void SaveError(char* error);
public:
	Automat(char* text);
	~Automat();
	int Check(char*& text);
	virtual void AddLexem(List*& Lexems, int lineNumInCode, int charNumInCode);
	//virtual void AddLexem(List*& Lexems);
	char* getErrorMessage();
};

