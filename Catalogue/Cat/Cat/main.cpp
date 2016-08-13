
#include "headers.h"

int state = 0;
/*
0 - общее меню
1 - меню каталога
2 - меню покупок
3 - меню продаж
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
		cout << "Введите пункт меню (0 - показать)> ";
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
				cout << "Введите код товара> ";
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
					cout << "Введите поля новой записи в соответствии с форматом справочника\n";
					cin >> buf;
					if (!cat.validate(buf, 1))
						throw "not valid";
					cat.add(buf);
					cout << "Запись успешно создана\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
				}
				break;
			
			case 4:
				cat.show();
				break;
			case 5:
				cout << "Введите номер столбца для сортировки (0-4)> ";
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
					cout << "Введите уникальное поле> ";
					cin >> buf;
					if (cat.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "Введите поля записи для замены в соответствии с форматом справочника\n";
						cin >> buf2;
						if (!cat.validate(buf2, 1))
							throw "not valid";
						cat.edit(buf, buf2);
						cout << "Запись успешно изменена\n";
					}
					else
					{
						cat.del(buf, 0);
						cout << "Запись успешно удалена\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
					if (strcmp(a, "not found") == 0)
						cout << "Запись с таким уникальным полем не найдена\n";
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
					cout << "Введите поля новой записи в соответствии с форматом справочника\n";
					cin >> buf;
					if (!buy.validate(buf, 2))
						throw "not valid";
					buy.add(buf);
					cout << "Запись успешно создана\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
				}
				break;
			case 2:
			case 3:
				try
				{
					cout << "Введите уникальное поле> ";
					cin >> buf;
					if (buy.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "Введите поля записи для замены в соответствии с форматом справочника\n";
						cin >> buf2;
						if (!buy.validate(buf2, 2))
							throw "not valid";
						buy.edit(buf, buf2);
						cout << "Запись успешно изменена\n";
					}
					else
					{
						buy.del(buf, 0);
						cout << "Запись успешно удалена\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
					if (strcmp(a, "not found") == 0)
						cout << "Запись с таким уникальным полем не найдена\n";
				}
				break;
			case 4:
				buy.show();
				break;
			case 5:
				cout << "Введите номер столбца для сортировки (0-4)> ";
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
					cout << "Введите поля новой записи в соответствии с форматом справочника\n";
					cin >> buf;
					if (!sale.validate(buf, 3))
						throw "not valid";
					sale.add(buf);
					cout << "Запись успешно создана\n";
				}
				catch(char *a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
				}
				break;
			case 2:
			case 3:
				try
				{
					cout << "Введите уникальное поле> ";
					cin >> buf;
					if (sale.find(buf, 0) == -1)
						throw "not found";
					if (enter == 2)
					{
						char *buf2 = new char[1024];
						cout << "Введите поля записи для замены в соответствии с форматом справочника\n";
						cin >> buf2;
						if (!sale.validate(buf2, 3))
							throw "not valid";
						sale.edit(buf, buf2);
						cout << "Запись успешно изменена\n";
					}
					else
					{
						sale.del(buf, 0);
						cout << "Запись успешно удалена\n";
					}
				}
				catch (char* a)
				{
					if (strcmp(a, "not valid") == 0)
						cout << "Запись задана неверно\n";
					if (strcmp(a, "not found") == 0)
						cout << "Запись с таким уникальным полем не найдена\n";
				}
				break;
			case 4:
				sale.show();
				break;
			case 5:
				cout << "Введите номер столбца для сортировки (0-4)> ";
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
		cout << "1. Выбрать каталог\n";
		cout << "2. Выбрать покупки\n";
		cout << "3. Выбрать продажи\n";
		cout << "4. Вывести отчет 1\n";
		cout << "5. Вывести отчет 2\n";
		cout << "6. Выход\n";
		break;
	default:
		cout << "1. Добавить запись\n";
		cout << "2. Редактировать запись\n";
		cout << "3. Удалить запись\n";
		cout << "4. Показать справочник\n";
		cout << "5. Выбрать столбец для сортировки\n";
		cout << "6. Сохранить справочник в файл и выбрать другой\n";
		cout << "7. Выйти без сохранения\n";
	}
}