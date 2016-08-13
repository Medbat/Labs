#include "MoneyField.h"


MoneyField::MoneyField(void)
{
}

MoneyField::~MoneyField(void)
{
}

void MoneyField :: set(char *s)
{
	if (s[strlen(s) - 3]=='E') 
		rurEur = true;
	else 
		rurEur = false;
	s[strlen(s) - 3] = '\0';
	value = atoi(s);
}

void MoneyField :: show()
{

}

char * MoneyField :: getValue()
{
	char* buffer = new char[15];
	sprintf (buffer, "%d%s", value, rurEur?"EUR":"RUR");
	return buffer;
}

bool MoneyField :: bigger(char *s1, char *s2)
{
	bool rurEur1, rurEur2;

	if (s1[strlen(s1) - 3]=='E') 
		rurEur1 = true;
	else 
		rurEur1 = false;
	s1[strlen(s1) - 3] = '\0';
	int value1 = atoi(s1);

	if (s2[strlen(s2) - 3]=='E') 
		rurEur2 = true;
	else 
		rurEur2 = false;
	s2[strlen(s2) - 3] = '\0';
	int value2 = atoi(s2);

	if (rurEur1)
		value1 *= 40;
	if (rurEur2)
		value2 *= 40;

	return value1 > value2;
}