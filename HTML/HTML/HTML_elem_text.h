#pragma once
#include "HTML_elem.h"

class HTML_elem_text : public HTML_elem
{
	string content;
public:
	HTML_elem_text(const string& s)
	{
		content = s;
	}
	string getTag()
	{
		return "\n<p>" + content + "</p>\n";
	}
};