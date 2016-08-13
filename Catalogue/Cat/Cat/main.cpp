
#include "headers.h"

int state = 0;
/*
0 - ����� ����
1 - ���� ��������
2 - ���� �������
3 - ���� ������
*/
void show_menu();

int main()
{
	setlocale(LC_ALL, "rus");
	int enter = 1;
	char *buf = new char[1024];

	HandBook cat(1), buy(2), sale(3), rep1(4), rep2(5);

	while (true)
	{
		cout << "������� ����� ���� (0 - ��������)> ";
		cin >> enter;
		switch (state)
		{
		case 0:
			switch (enter)
			{
			case 0:
				show_menu();
				break;
			case 1:
				cat.read();
				cat.show();
				state = 1;
				show_menu();
				break;
			case 2:
				buy.read();
				buy.show();
				state = 2;
				show_menu();
				break;
			case 3:
				sale.read();
				sale.show();
				state = 3;
				show_menu();
				break;
			case 4:
				rep1.Report1();
				rep1.sort(1);
				rep1.show();
				rep1.deleteData();
				break;
			case 5:
				cout << "������� ��� ������> ";
				cin >> buf;
				rep2.Report2(buf);
				rep2.sort(1);
				rep2.show();
				rep2.deleteData();
				break;
			case 6:
				return 0;
			}
		break;
		case 1:
			switch (enter)
			{
			case 0:
				show_menu();
				break;
			case 1:
				try
				{
					cout << "������� ���� ����� ������ � ������������ � �������� �����������\n";
					cin >> buf;
					if (!cat.validate(buf, 1))
						throw "not valid";
					cat.add(buf);
					cout << "������ ������� �������\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
				}
				break;
			
			case 4:
				cat.show();
				break;
			case 5:
				cout << "������� ����� ������� ��� ���������� (0-4)> ";
				cin >> buf;
				cat.sort(atoi(buf));
				cat.show();
				break;
			case 6:
			case 7:
				if (enter == 6)
					cat.reWrite();
				state = 0;
				break;
			default:
				try
				{
					cout << "������� ���������� ����> ";
					cin >> buf;
					if (cat.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "������� ���� ������ ��� ������ � ������������ � �������� �����������\n";
						cin >> buf2;
						if (!cat.validate(buf2, 1))
							throw "not valid";
						cat.edit(buf, buf2);
						cout << "������ ������� ��������\n";
					}
					else
					{
						cat.del(buf, 0);
						cout << "������ ������� �������\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
					if (strcmp(a, "not found") == 0)
						cout << "������ � ����� ���������� ����� �� �������\n";
				}
				break;
			}
			break;
		case 2:
			switch (enter)
			{
			case 0:
				show_menu();
				break;
			case 1:
				try
				{
					cout << "������� ���� ����� ������ � ������������ � �������� �����������\n";
					cin >> buf;
					if (!buy.validate(buf, 2))
						throw "not valid";
					buy.add(buf);
					cout << "������ ������� �������\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
				}
				break;
			case 2:
			case 3:
				try
				{
					cout << "������� ���������� ����> ";
					cin >> buf;
					if (buy.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "������� ���� ������ ��� ������ � ������������ � �������� �����������\n";
						cin >> buf2;
						if (!buy.validate(buf2, 2))
							throw "not valid";
						buy.edit(buf, buf2);
						cout << "������ ������� ��������\n";
					}
					else
					{
						buy.del(buf, 0);
						cout << "������ ������� �������\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
					if (strcmp(a, "not found") == 0)
						cout << "������ � ����� ���������� ����� �� �������\n";
				}
				break;
			case 4:
				buy.show();
				break;
			case 5:
				cout << "������� ����� ������� ��� ���������� (0-4)> ";
				cin >> buf;
				buy.sort(atoi(buf));
				buy.show();
				break;
			case 6:
			case 7:
				if (enter == 6)
					buy.reWrite();
				state = 0;
				break;
			}
			break;
		case 3:
			switch (enter)
			{
			case 0:
				show_menu();
				break;
			case 1:
				try
				{
					cout << "������� ���� ����� ������ � ������������ � �������� �����������\n";
					cin >> buf;
					if (!sale.validate(buf, 3))
						throw "not valid";
					sale.add(buf);
					cout << "������ ������� �������\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
				}
				break;
			case 2:
			case 3:
				try
				{
					cout << "������� ���������� ����> ";
					cin >> buf;
					if (sale.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "������� ���� ������ ��� ������ � ������������ � �������� �����������\n";
						cin >> buf2;
						if (!sale.validate(buf2, 3))
							throw "not valid";
						sale.edit(buf, buf2);
						cout << "������ ������� ��������\n";
					}
					else
					{
						sale.del(buf, 0);
						cout << "������ ������� �������\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "������ ������ �������\n";
					if (strcmp(a, "not found") == 0)
						cout << "������ � ����� ���������� ����� �� �������\n";
				}
				break;
			case 4:
				sale.show();
				break;
			case 5:
				cout << "������� ����� ������� ��� ���������� (0-4)> ";
				cin >> buf;
				sale.sort(atoi(buf));
				sale.show();
				break;
			case 6:
			case 7:
				if (enter == 6)
					sale.reWrite();
				state = 0;
				break;
			}
			break;
		}
	}

	return 0;
}

void show_menu()
{
	switch (state)
	{
	case 0:
		cout << "1. ������� �������\n";
		cout << "2. ������� �������\n";
		cout << "3. ������� �������\n";
		cout << "4. ������� ����� 1\n";
		cout << "5. ������� ����� 2\n";
		cout << "6. �����\n";
		break;
	default:
		cout << "1. �������� ������\n";
		cout << "2. ������������� ������\n";
		cout << "3. ������� ������\n";
		cout << "4. �������� ����������\n";
		cout << "5. ������� ������� ��� ����������\n";
		cout << "6. ��������� ���������� � ���� � ������� ������\n";
		cout << "7. ����� ��� ����������\n";
	}
}