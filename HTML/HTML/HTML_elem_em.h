#pragma once
#include "HTML_elem.h"
#include <string>

using namespace std;

class HTML_elem_em : public HTML_elem
{
	string content;
public:
	HTML_elem_em(const string& s)
	{
		content = s;
	}
	string getTag()
	{
		return "<em>" + content + "</em>";
	}
};