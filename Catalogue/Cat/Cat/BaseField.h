#pragma once
#include <iostream>
using namespace std;
class BaseField
{
public:
	BaseField(void);
	~BaseField(void);
	virtual void set(char *) = 0;
	virtual void show() = 0;
	virtual bool bigger(char*, char*) = 0;
	virtual char* getValue() = 0;
	friend ostream& operator<<(ostream& out, BaseField& p)
	{
		out <<  p.getValue();
		return out;
    };
};

