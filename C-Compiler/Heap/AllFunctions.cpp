#pragma once
#include "stdafx.h"


//Article* MakeAnArticle(char* word, char* description)
//{
//	Article* temp = (Article*)heap->get_mem(sizeof(Article));
//	int count;
//
//	for (count = 0; word[count] != '\0'; count++);
//	temp->word = MakeAWord(count);
//
//	for (count = 0; description[count] != '\0'; count++);
//	temp->description = MakeAWord(count);
//	return temp;
//}

bool isSpace(char a)
{
	return a == ' ' && a == '\n' && a == '\t';
}