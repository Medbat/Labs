
#pragma once

#include <iostream>
#include <string>

using namespace std;


class Elem
{
protected:
	Elem* next;
	friend class List;
	friend class Iter;
public:
	Elem* next_elem()
	{
		return next;
	}
	virtual string str() = 0;
};

class Iter
{
	friend class List;
	Elem* current_elem;
public:
	Iter() : current_elem(0) {}
	Iter operator++()
	{
		if (current_elem)
			current_elem = current_elem -> next_elem();
		return *this;
	}
	Elem& operator*() 
	{
		return *current_elem; 
	}
	Elem* operator->()
	{ 
		return current_elem; 
	}
	bool operator!=(Iter v)
	{
		return current_elem != v.current_elem;
	}
};

class List
{
protected:
	friend class Iter;
	Elem* first;
public:
	List() : first(NULL) {};
	~List()
	{
	}
	int length()
	{
		int ret = 0;
		Elem* temp = first;
		while (temp)
		{
			ret++;
			temp = temp -> next;
		}
		return ret;
	}
	void push(Elem* El)
	{
		El->next = first;
		first = El;
	}
	void push_back(Elem* p)
	{
		Elem *e = NULL;
		for (Iter i = begin(); i != end(); ++i)
			e = &*i;
		if (e)	
			e -> next = p;
		else
			first = p;
		p -> next = NULL;
			
	}
	Elem* pop()
	{
		Elem *p = first;
		if (p)
			first = p->next;
		return p;
	}
	bool empty();
	Iter begin()
	{
		Iter tmp;
		tmp.current_elem = first;
		return tmp;
	}
	Iter end()
	{
		Iter tmp;
		tmp.current_elem = NULL;
		return tmp;
	}
};


class Text : public Elem
{
	string s;
public:
	Text(string ss) : s(ss) {};
	string str()
	{
		return s;
	}
};

class Tag : public Elem
{
	string name;
	List content;
protected: 
	string content_str()
	{
		string s;
		for (Iter i = content.begin(); i != content.end(); ++i)
			s += i -> str();		
		return s;
	}
public:
	Tag(string s): name(s) {};
	string str()
	{
		return "<" + name + ">"	+ content_str() + "</" + name + ">";
	}
	Tag& push_back(Elem* a)
	{
		content.push_back(a);
		return *this;
	}
};

class Em : public Tag
{
public:
	Em(): Tag("em") {}
};

class Strong : public Tag
{
public:
	Strong() : Tag("strong") {}
};

class A : public Tag
{
	string href;
public:
	A(string s) : Tag("a"), href(s) {}
	string str()
	{
		return "<a href=\"" + href + "\">" + content_str() + "</a>";
	}
};

class P : public Tag
{
public:
	P() : Tag("p") {}
};