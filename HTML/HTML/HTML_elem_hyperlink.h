#pragma once
#include "HTML_elem.h"

class HTML_elem_hyperlink : public HTML_elem
{
	string link, text;
public:
	HTML_elem_hyperlink(const string& link, const string& text)
	{
		this->link = link;
		this->text = text;
	}
	string getTag()
	{
		return "<a href=\"" + link + "\">" + text + "</a>";
	}
};