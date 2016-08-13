#include "stdafx.h"
#include "Automat.h"
#include "List.h"
#include "Identificator.h"
#include "Compiler.h"

void AddLexem(List*& Lexems, int i, char* text, char** state, int curstate);

Automat::Automat(char* text)
{
	ifstream curautomat(text);
	char* autobuf = (char*)heap->get_mem(1024 * sizeof(char));
	curautomat >> autobuf;
	alphabetQuant = atoi(autobuf);
	alphabet = (char**)heap->get_mem(alphabetQuant * sizeof(char*));

	for (int i = 0; i < alphabetQuant; i++)
	{
		curautomat >> autobuf;
		alphabet[i] = (char*)heap->get_mem((strlen(autobuf) + 1) * sizeof(char));
		int j;
		for (j = 0; autobuf[j] != '\0'; j++)
			alphabet[i][j] = autobuf[j];
		alphabet[i][j] = '\0';
	}

	curautomat >> autobuf;
	stateQuant = atoi(autobuf);
	state = (char**)heap->get_mem(stateQuant * sizeof(char*));

	for (int i = 0; i < stateQuant; i++)
	{
		curautomat >> autobuf;
		state[i] = (char*)heap->get_mem((strlen(autobuf) + 1) * sizeof(char));
		int j;
		for (j = 0; autobuf[j] != '\0'; j++)
			state[i][j] = autobuf[j];
		state[i][j] = '\0';
	}

	curautomat >> autobuf;
	errorQuant = atoi(autobuf);
	error = (char**)heap->get_mem(errorQuant * sizeof(char*));

	for (int i = 0; i < errorQuant; i++)
	{
		curautomat >> autobuf;
		error[i] = (char*)heap->get_mem((strlen(autobuf) + 1) * sizeof(char));
		int j;
		for (j = 0; autobuf[j] != '\0'; j++)
			error[i][j] = autobuf[j];
		error[i][j] = '\0';
	}

	table = (int**)heap->get_mem(stateQuant*sizeof(int*));
	for (int i = 0; i < stateQuant; i++)
	{
		table[i] = (int*)heap->get_mem((alphabetQuant + 1)*sizeof(int));
		for (int j = 0; j < alphabetQuant + 1; j++)
		{
			curautomat >> autobuf;
			table[i][j] = atoi(autobuf);
		}
	}

	templen = 0;
	tempname = (char*)heap->get_mem(16 * sizeof(char));
	tempstate = (char*)heap->get_mem(16 * sizeof(char));
	temperror = NULL;
	curautomat.close();
}

Automat::~Automat()
{
	for (int i = 0; i < alphabetQuant; i++)
	{
		heap->free_mem(alphabet[i]);
		alphabet[i] = NULL;
	}
	heap->free_mem(alphabet);
	alphabet = NULL;

	for (int i = 0; i < stateQuant; i++)
	{
		heap->free_mem(state[i]);
		state[i] = NULL;
	}
	heap->free_mem(state);
	state = NULL;

	for (int i = 0; i < errorQuant; i++)
	{
		heap->free_mem(error[i]);
		error[i] = NULL;
	}
	heap->free_mem(error);
	error = NULL;

	for (int i = 0; i < alphabetQuant + 1; i++)
	{
		heap->free_mem(table[i]);
		table[i] = NULL;
	}
	heap->free_mem(table);
	table = NULL;
}

int Automat::Check(char*& text)
{
	int start = 0;
	int curstate = 0;
	int tempstate = 0;
	int i = -1;
	do
	{
		i++;
		for (int x = 0; x < alphabetQuant; x++)
		{
			for (int y = 0; alphabet[x][y] != '\0'; y++)
			{
				if (alphabet[x][y] == text[i])
				{
					if (curstate == 0)
					{
						curstate = table[curstate][x];
						if (curstate == 0) return 2;
						if (curstate < 0)
						{
							SaveError(error[-curstate-1]);
							strcpy(text, &text[i]);
							return 0;
						}
						/*
						
						TODO: ÓÁÐÀÒÜ GOTO (ÄÈÍÎÇÀÂÐ ÓÆÅ ÂÛÅÕÀË)
						
						*/
						goto newletter;
					}
					tempstate = curstate;
					curstate = table[curstate][x];
					if (curstate == 0)
					{
						CopyTempData(i, text, state, tempstate);
						strcpy(text, &text[i]);
						return 1;
					}
					if (curstate < 0)
					{
						SaveError(error[-curstate-1]);
						strcpy(text, &text[i]);
						return 0;
					}
					goto newletter;
				}
			}
		}
		if (curstate == 0) return 2;
		tempstate = curstate;
		curstate = table[curstate][alphabetQuant];
		if (curstate == 0) // ñëîâî çàôèêñèðîâàíî
		{
			CopyTempData(i, text, state, tempstate);
			strcpy(text, &text[i]);
			return 1;
		}
		if (curstate < 0)
		{
			SaveError(error[-curstate-1]);
			strcpy(text, &text[i]);
			return 0;
		}
	newletter:
		;
	} while (text[i] != '\0');
	CopyTempData(i, text, state, curstate);
	text[0] = '\0';
	return 1;
}

void Automat::CopyTempData(int i, char* text, char** state, int curstate)
{
	templen = i;
	char* subst = (char*)heap->get_mem((i + 1)*sizeof(char));
	memcpy(subst, &text[0], i);
	subst[i] = '\0';
	strcpy(tempname, subst);
	strcpy(tempstate, state[curstate]);
	heap->free_mem(subst);
	subst = NULL;
}

void Automat::AddLexem(List*& Lexems, int lineNumInCode, int charNumInCode)
{
	Lexems->add(new Lexem(templen, tempname, tempstate));
	((Lexem*)Lexems->get(Lexems->count() - 1))->lineNumInCode = lineNumInCode;
	((Lexem*)Lexems->get(Lexems->count() - 1))->charNumInLine = charNumInCode;

}

void Automat::SaveError(char* error)
{
	if (temperror != NULL) 
		heap->free_mem(temperror);
	temperror = (char*)heap->get_mem((strlen(error) + 1) * sizeof(char));
	strcpy(temperror, error);
}

char* Automat::getErrorMessage()
{ 
	if (temperror != NULL) 
		return temperror;
}