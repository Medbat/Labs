#include "tree.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	tree *tr = new tree;
	while (tr->rt())
	{
		int n;
		tr->countChildren();
		// 5
		cout << "ДЕРЕВО\n";
		cout << "Суммарный заряд: " << tr->show();
		cout << "\nВведите номер элемента, к которому ";
		cout << "хотите создать потомка: ";
		// 1
		do
			cin >> n;

		while (!tr->find(n));
		// 2
		tr->life();
		// 3
		tr->add(n);
		// 4
		tr->death();
	}
	system("pause");
	return 0;
}