#include "TextField.h"

TextField::TextField(void)
{
	str = NULL;
}

void TextField :: deleteData()
{
	if (str)
		delete [] str;
}

TextField::~TextField(void)
{
	deleteData();
}

void TextField :: set(char *s)
{
	deleteData();
	str = new char[strlen(s) + 1];
	strcpy(str, s);
}

void TextField :: show()
{
	cout << str;
}

char* TextField :: getValue()
{
	return this -> str;
}

bool TextField :: bigger(char *s1, char *s2)
{
	return strcmp(s1, s2) > 0;
}