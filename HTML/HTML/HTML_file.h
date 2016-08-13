#pragma once

#include "HTML_elem.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

class HTML_file
{
	list<HTML_elem*> content;
	string title;
public:
	HTML_file(const string& title)
	{
		this->title = title;
	}
	~HTML_file()
	{
		content.erase(content.begin(), content.end());
	}
	void addElem(HTML_elem *to_add)
	{
		content.push_back(to_add);
	}
	void out()
	{
		list<HTML_elem*>::iterator i;
		cout << "\nfile.html\n<html>\n\t<head>\n\t\t<title>\n\t\t\t" << title << "\n\t\t</title>\n\t</head>\n<body>";
		for (i = content.begin(); i != content.end(); i++)
			cout << (*i)->getTag();
		cout << "\n</body>\n</html>\n";
	}
};
