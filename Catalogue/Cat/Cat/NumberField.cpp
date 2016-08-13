#include "NumberField.h"


NumberField::NumberField(void)
{
}


NumberField::~NumberField(void)
{
}

void NumberField :: set(char *s)
{
	value = atoi(s);
}

void NumberField :: show()
{

}

char *NumberField :: getValue()
{
	char* buffer = new char[15];
	sprintf (buffer, "%d", value);
	return buffer;
}

bool NumberField :: bigger(char *s1, char *s2)
{
	return atoi(s1) > atoi(s2);
}