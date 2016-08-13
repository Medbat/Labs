#pragma once
#include "HTML_elem.h"

class HTML_elem_strong : public HTML_elem
{
	string content;
public:
	HTML_elem_strong(const string& s)
	{
		content = s;
	}
	string getTag()
	{
		return "<strong>" + content + "</strong>";
	}
};
