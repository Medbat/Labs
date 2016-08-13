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
		cout << "������\n";
		cout << "��������� �����: " << tr->show();
		cout << "\n������� ����� ��������, � �������� ";
		cout << "������ ������� �������: ";
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