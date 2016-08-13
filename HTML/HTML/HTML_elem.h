
#pragma once
#include "HTML_file.h"

#include <string>

using namespace std;

class HTML_elem
{
public:
	HTML_elem() {};
	~HTML_elem() {};
	virtual string getTag() = 0;
};