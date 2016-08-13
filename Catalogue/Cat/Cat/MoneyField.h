#pragma once
#include "basefield.h"
#include <iostream>

using namespace std;

class MoneyField :
	public BaseField
{
	int value;
	bool rurEur;
public:
	MoneyField(void);
	~MoneyField(void);
	void set(char *);
	void show();
	friend ostream& operator<<(ostream& out, MoneyField& p)
	{
		out << p.value;
		if (p.rurEur)
			out << "EUR";
		else
			out << "RUR";
		return out;
	}
	char *getValue();
	bool bigger(char*, char*);
};