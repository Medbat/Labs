#include <iostream>

using namespace std;

// прототип функции определения четности суммы цифр числа
bool need(int a);

int main() {
	// русская кодировка
	setlocale(LC_ALL, "rus");
	// объявление переменных
	int n, i, j, k = 0;
	bool f;
	// ввод входных данных с защитой от дурака
	do {
		n = 0;
		cout << "Введите N> ";
		cin >> n;
		if (n < 1)
			cout << "Неверные исходные данные" << endl;
	} while (n < 1);
	if (n == 1)
		n = 2;
	// основной цикл вывода
	for (i = n; k < 10 ; i++) {
		f = true;
		if (!need(i))
			f = false;
		else
			for (j = 2; j <= sqrt((double(i))); j++)
				if (i % j == 0) {
					f = false;
					break;
				}
		if (f) {
			cout << i << " ";
			k++;
		}
	}
	

	// просмотр результатов до нажатия любой клавиши
	cout << endl;
	system("pause");
	return 0;
}

// реализации функции need
bool need(int a) {
	int sum = 0;
	while (a != 0) {
		sum += a % 10;
		a /= 10;
	}
	if (sum % 2 == 0)
		return true;
	else
		return false;
}