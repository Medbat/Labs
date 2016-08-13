#pragma once

#include "Elem.h"
#include <string>
#include <sstream>

using namespace std;

class Num : public Elem
{
	int x;
public:
	Num(int num) : x(num) {};
	~Num() {};
	string getElem()
	{
		stringstream s;
		s << x;
		return s.str();
	}
	int value()
	{
		return x;
	}
};