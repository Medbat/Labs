#pragma once

#include "List.h"
#include "Identificator.h"
#include "Automat.h"
#include "Tree.h"

void ReportError(int lineNum, int charNum, char* message);
Lexem* RecursiveTreeer(List* Lexems, int leftborder, int rightborder, int& MinPriorityOperIndex);
bool isRightToLeftOper(Lexem*);

class Compiler
{
public:
	Compiler();
	bool Compile(char* sourceCode);
private:
	int automatsNumber;
	Automat** automats;
	Automat* standtypes;

	void Initialize();
	char* MakeAWord(int letnum);
	void DeleteApostrophes(char*);
	bool IsConst(char*);
	bool IsDivisorOrBracket(char*);
	bool IsStandardFunction(char*);
	TList* HandleBlockCode(List* Lexems, int &leftborder);
	TList* CaseBody(List* Lexems, int &leftborder);
	bool NestingLevelSearching(List*);
	TList* BuildTree(List* Lexems, int leftborder, int rightborder);
	void PrintLexemList(List* list);
	bool CheckWithAutomatons(char* sourceCodeFile, List* Lexems);
	bool ClarifyLexems(List *Lexems);
	bool ClarifyOperators(List* Lexems);
	bool FindNoOperation(List* Lexems);


	// Проверка всех скобок, если всё хорошо тру, иначе фолс
	bool ValidateBraces(char* sourceCodeFile);
	void ReplaceAll(char* sourceString, int lenOfSourceStr, char* oldValue, int lenOfOV, char* newValue, int lenOfNV);

	bool DefineReplacement(List* Lexems);

	void GetMemForArrayR(void**&, List*, int dimension, TypTypes); // рекурсивно выделить память под массив
};