#pragma once

struct Node
{
	int id;
	int charge;
	int children;
	Node *child;
	Node *other;
};

class tree
{
private:
	Node *root;
	int n;
	void life(Node*);
	void countChildren(Node*);
	void find(int, Node*, Node*&);
	void find(Node*, Node*, Node*&, bool&);
	void show(Node*, int, int &);
	void death(Node*);
	void nullification(Node*);
	void destroyTree(Node*);
public:
	tree();
	~tree();
	void add(int);
	int show();
	bool find(int);
	Node* rt();
	void death();
	void life();
	void countChildren();
};

