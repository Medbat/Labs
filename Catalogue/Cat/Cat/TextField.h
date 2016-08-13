#pragma once
#include "basefield.h"
#include <iostream>

using namespace std;

class TextField :
	public BaseField
{
	char *str;
	void deleteData();
	char *getValue();
public:
	TextField(void);
	~TextField(void);
	void set(char *);
	void show();
	friend ostream& operator<<(ostream& out, TextField& p)
	{
		out << p.getValue();
		return out;
	}
	bool bigger(char*, char*);
};

