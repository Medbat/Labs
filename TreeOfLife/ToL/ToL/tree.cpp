#include "tree.h"
#include <iostream>

tree::tree()
{
	root = new Node;
	root -> id = 0;
	root -> charge = 10;
	root -> child = NULL;
	root -> other = NULL;
	n = 0;
}

tree::~tree()
{
	destroyTree(root);
	root = NULL;
}

void tree::destroyTree(Node *t)
{
	if (t -> child)
		destroyTree(t -> child);
	if (t -> other)
		destroyTree(t -> other);
	delete [] t;
}

void tree::add(int b)
{
	n++;
	Node *a = NULL;
	find(b, root, a);
	Node *t = new Node;
	t -> id = n;
	t -> charge = 10;
	t -> other = NULL;
	t -> child = NULL;
	if (a -> child)
	{
		a = a -> child;
		while (a -> other != NULL)
			a = a -> other;
		a -> other = t;
	}
	else
	{
		a -> child = t;
	}
}

void tree::show(Node*t, int a, int &sum)
{
	for (int i = 0; i < a; i++)
		std::cout << " ";
	std::cout << t -> id << " (" << t -> charge << ")\n";
	sum += t->charge;
	if (t -> child)
		show(t -> child, a + 1, sum);
	if (t -> other)
		show(t -> other, a, sum);
}

int tree::show()
{
	int t = 0;
	show(root, 0, t);
	return t;
}

Node* tree::rt()
{
	return root;
}

void tree::life()
{
	life(root);
}

void tree::life(Node *t)
{
	if (t -> child)
		life(t -> child);
	if (t -> other)
		life(t -> other);
	// ÇÀÏÎÂÅÄÜ 1 - ÂÐÅÌß
	t -> charge--;
	// ÇÀÏÎÂÅÄÜ 2 - ÑÀÌÎÎÒÄÀ×À
	t -> charge -= t -> children;
	// ÇÀÏÎÂÅÄÜ 3 - ÐÀÇÂÈÒÈÅ
	if (t->children==2)
	{
		t->child->charge++;
		t->child->other->charge++;
	}
	// ÇÀÏÎÂÅÄÜ 4 - ÐÀÇÂÈÒÈÅ++
	if (t->children==3)
	{
		t->child->charge+=2;
		t->child->other->charge+=2;
		t->child->other->other->charge+=2;
	}
	// ÇÀÏÎÂÅÄÜ 5 - ÆÀÄÍÎÑÒÜ
	if (t->children>3)
	{
		Node *temp = t -> child;
		do
			temp -> charge -= t->children - 3;
		while (temp = temp -> other);
	}
}

void tree::death()
{
	death(root);
}

void tree::death(Node *t)
{
	if (t->charge<1)
	{
		Node *parent = NULL;
		bool cop;
		find(t, root, parent, cop);
		if (t->child)
		{
			if (t == root)
			{
				if (root->child->child&&root->child->other)
				{
					Node *tt = root->child->other;
					while (tt->other)
						tt=tt->other;
					tt->other=root->child->child;
				}
				root = t->child;
				if (root->other)
				{
					root->child = root->other;
					root->other=NULL;
				}
			}
			else
				if (cop)
					parent->other=t->child;
				else
					parent->child=t->child;
			Node *tt = t->child;
			while (tt->other)
				tt=tt->other;
			tt->other=t->other;
		}
		else
		{
			if (t == root)
				root = NULL;
			else
				if (cop)
					parent->other=t->other;
				else
					parent->child=t->other;
		}
	}
	if (t -> child)
		death(t -> child);
	if (t -> other)
		death(t -> other);
	if (t->charge<1)
		delete [] t;
}

void tree::countChildren(Node* t)
{
	if (t -> child)
	{
		t -> children = 1;
		Node *tt = t->child;
		while (tt->other)
		{
			t->children++;
			tt=tt->other;
		}
		countChildren(t->child);
	}
	if (t -> other)
		countChildren(t->other);
}

void tree::nullification(Node *t)
{
	t -> children = 0;
	if (t -> child)
		nullification(t -> child);
	if (t -> other)
		nullification(t -> other);
}

void tree::countChildren()
{
	nullification(root);
	countChildren(root);
}

void tree::find(Node *a, Node *t, Node *&ret, bool &childOrOther)
{
	if (t -> child)
		find(a, t -> child, ret, childOrOther);
	if (t -> other)
		find(a, t -> other, ret, childOrOther);
	if (t -> child == a)
	{
		ret = t;
		childOrOther = false;
	}
	if (t->other == a)
	{
		ret = t;
		childOrOther = true;
	}
}

void tree::find(int a, Node* ret, Node *&c)
{
	if (ret -> child)
		find(a, ret -> child, c);
	if (ret -> other)
		find(a, ret -> other, c);
	if (ret -> id == a)
		c = ret;
}

bool tree::find(int a)
{
	Node* t = NULL;
	find(a, root, t);
	return t;
}