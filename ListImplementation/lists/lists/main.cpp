
#include "lists.h"

int main() {

	int type, select, after;
	int id, how;
	char N;
	char * name = new char[1024];
	bool good;

	setlocale(LC_ALL, "rus");
	cout << "�������� ��� ������\n1. ���������������� ��������\n2. ��������������� �����������\n";
	cin >> type;
	oneLin * OL = NULL;
	twoCycl * TC = NULL;

	do {

		select = 0;

		cout << "����\n1. �������� �������� ������\n";
		cout << "2. �������� ������� � ������ ������\n";
		cout << "3. �������� ������� � ����� �����\n";
		cout << "4. �������� ������� ����� ������������� ��������\n";
		cout << "5. ������� �������\n";
		cout << "6. �������� �������� �� �����\n";
		cout << "7. ������ ���� ��������� ������\n";
		cout << "8. ������� ������\n";
		cout << "0. �����\n";
		cin >> select;

		switch (select) {

		case 1:
			if (type == 1)
				if (!write(OL))
					cout << "������! ������ �� ����� ���������!\n";
			if (type == 2)
				if (!write(TC))
					cout << "������! ������ �� ����� ���������!\n";
			break;
		
		case 2:
			cout << "������� ID ��������> ";
			cin >> id;
			cout << "������� �������� ��������> ";
			cin >> name;
			if (type == 1)
				addFirst(OL, id, name);
			else
				addFirst(TC, id, name);
			cout << "������� ������� �������� � ������ ������!\n";
			break;

		case 3:
			cout << "������� ID ��������> ";
			cin >> id;
			cout << "������� �������� ��������> ";
			cin >> name;
			if (type == 1)
				addLast(OL, id, name);
			else
				addLast(TC, id, name);
			cout << "������� ������� �������� � ����� ������!\n";
			break;

		case 4:
			cout << "������� ID ��������, ����� �������� ����� �������� �������� �������> ";
			cin >> after;
			if (type == 1)
				if (!addSmwh(OL, id, name, after))
					whyIsItSoBad(4);
			else
				if (!addSmwh(TC, id, name, after))
					whyIsItSoBad(4);
			cout << "������� ������� �������� ����� �������� � ID = " << after << "!\n";
			break;

		case 5:
			cout << "������� ID ��������> ";
			cin >> id;
			if (type == 1)
				if (!deleteElement(OL, id))
					whyIsItSoBad(5);
			else
				if (!deleteElement(TC, id))
					whyIsItSoBad(5);
			cout << "������� � ID = " << id << " ��� ������� ������!\n";
			break;
		case 6:
			cout << "������� ����� �������� ������ (1-3)> ";
			cin >> N;
			cout << "������� ������ ���������� ��������� � ������\n";
			cout << "0. ������ ������� � ������\n";
			cout << "1. ������ ������� � �����\n";
			cout << "2. ������ ������� ����� ������������� ��������\n";
			cin >> how;
			if (how == 2) {
				cout << "������� ID ��������> ";
				cin >> after;
			}
			if (type == 1)
				if (how != 2)
					good = dlFromFile(OL, N, how);
				else
					good = dlFromFile(OL, N, how, after);
			if (type == 2)
				if (how != 2)
					good = dlFromFile(TC, N, how);
				else
					good = dlFromFile(TC, N, how, after);
			if (good) 
				whyIsItSoBad(4);
			else
				cout << "������ ������� ��������!\n";
			break;

		case 7:
			cout << "������� ID ������� ��������> ";
			cin >> id;
			cout << "������� ID ������� ��������> ";
			cin >> after;
			if (type == 1)
				if (!swapElements(OL, id, after))
					whyIsItSoBad(7);
			if (type == 2)
				if (!swapElements(TC, id, after))
					whyIsItSoBad(7);
			break;

		case 8:
			if (type == 1)
				deleteAll(OL);
			else
				deleteAll(TC);
			cout << "������ ������� ������!\n";
			break;
	
		}
		system("pause");
	} while (select);
	//*/
	
	return 0;
}