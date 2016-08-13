#pragma once
#include "basefield.h"
#include <iostream>

using namespace std;

class NumberField :
	public BaseField
{
	int value;
public:
	NumberField(void);
	~NumberField(void);
	void set(char *);
	void show();
	friend ostream& operator<<(ostream& out, NumberField& p)
	{
		out << p.value;
		return out;
	}
	char *getValue();
	bool bigger(char*, char*);
};
