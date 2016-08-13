#include "DataField.h"
#include <iostream>

DataField::DataField(void)
{
}
DataField::~DataField(void)
{
}
void DataField :: set(char *s)
{
	sscanf (s, "%d.%d.%d", &this->day, &this->month, &this->year);
}

void DataField :: show()
{

}

char* DataField :: getValue()
{
	char* buffer=new char[11];
	sprintf (buffer, "%02d.%02d.%04d", this->day, this->month, this->year);
	return buffer;
}

bool DataField :: bigger(char *s1, char *s2)
{
	int year1, year2, month1, month2, day1, day2;
	sscanf (s1, "%d.%d.%d", &day1, &month1, &year1);
	sscanf (s2, "%d.%d.%d", &day2, &month2, &year2);
	sprintf (s1, "%04d%02d%02d", year1, month1, day1);
	sprintf (s2, "%04d%02d%02d", year2, month2, day2);
	return strcmp(s1, s2) > 0;
}