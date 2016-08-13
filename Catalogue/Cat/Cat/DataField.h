#pragma once
#include "basefield.h"
#include <iostream>

using namespace std;

class DataField :
	public BaseField
{
	int day, month, year;
public:
	DataField(void);
	~DataField(void);
	void set(char *);
	void show();
	friend ostream& operator<<(ostream& out, DataField& p)
	{
		out << p.getValue();
		return out;
	}
	char *getValue();
	bool bigger(char*, char*);
};
