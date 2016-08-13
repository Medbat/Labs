
#include "lists.h"

int main() {

	int type, select, after;
	int id, how;
	char N;
	char * name = new char[1024];
	bool good;

	setlocale(LC_ALL, "rus");
	cout << "Выберите тип списка\n1. Однонаправленный линейный\n2. Двунаправленный циклический\n";
	cin >> type;
	oneLin * OL = NULL;
	twoCycl * TC = NULL;

	do {

		select = 0;

		cout << "МЕНЮ\n1. Показать элементы списка\n";
		cout << "2. Добавить элемент в начало списка\n";
		cout << "3. Добавить элемент в конец спика\n";
		cout << "4. Добавить элемент после определенного элемента\n";
		cout << "5. Удалить элемент\n";
		cout << "6. Добавить элементы из файла\n";
		cout << "7. Замена двух элементов списка\n";
		cout << "8. Удалить список\n";
		cout << "0. Выход\n";
		cin >> select;

		switch (select) {

		case 1:
			if (type == 1)
				if (!write(OL))
					cout << "Ошибка! Список не имеет элементов!\n";
			if (type == 2)
				if (!write(TC))
					cout << "Ошибка! Список не имеет элементов!\n";
			break;
		
		case 2:
			cout << "Введите ID элемента> ";
			cin >> id;
			cout << "Введите название элемента> ";
			cin >> name;
			if (type == 1)
				addFirst(OL, id, name);
			else
				addFirst(TC, id, name);
			cout << "Элемент успешно добавлен в начало списка!\n";
			break;

		case 3:
			cout << "Введите ID элемента> ";
			cin >> id;
			cout << "Введите название элемента> ";
			cin >> name;
			if (type == 1)
				addLast(OL, id, name);
			else
				addLast(TC, id, name);
			cout << "Элемент успешно добавлен в конец списка!\n";
			break;

		case 4:
			cout << "Введите ID элемента, после которого нужно вставить введённый элемент> ";
			cin >> after;
			if (type == 1)
				if (!addSmwh(OL, id, name, after))
					whyIsItSoBad(4);
			else
				if (!addSmwh(TC, id, name, after))
					whyIsItSoBad(4);
			cout << "Элемент успешно добавлен после элемента с ID = " << after << "!\n";
			break;

		case 5:
			cout << "Введите ID элемента> ";
			cin >> id;
			if (type == 1)
				if (!deleteElement(OL, id))
					whyIsItSoBad(5);
			else
				if (!deleteElement(TC, id))
					whyIsItSoBad(5);
			cout << "Элемент с ID = " << id << " был успешно удален!\n";
			break;
		case 6:
			cout << "Введите номер тестовых данных (1-3)> ";
			cin >> N;
			cout << "Укажите способ добавления элементов в список\n";
			cout << "0. Каждый элемент в начало\n";
			cout << "1. Каждый элемент в конец\n";
			cout << "2. Каждый элемент после определенного элемента\n";
			cin >> how;
			if (how == 2) {
				cout << "Введите ID элемента> ";
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
				cout << "Список успешно обновлен!\n";
			break;

		case 7:
			cout << "Введите ID первого элемента> ";
			cin >> id;
			cout << "Введите ID второго элемента> ";
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
			cout << "Список успешно удален!\n";
			break;
	
		}
		system("pause");
	} while (select);
	//*/
	
	return 0;
}