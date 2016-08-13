#include <iostream>

using namespace std;

int main() {
	// русская кодировка
	setlocale(LC_ALL, "rus");
	// объявление переменных
	int m, k, n, i, j;	
	bool f;
	// ввод входных данных с защитой от дурака
	do {
		m = n = 0;
		cout << "Введите M и N> ";
		cin >> m >> n;
		if (m <= 0 || n < m)
			cout << "Неверные исходные данные" << endl;
	} while (m <= 0 || n < m);
	// основной цикл вывода
	i = 1;
	for (k = 0; k <= n; k++) {
		do {
			f = true;
			i++;
			for (j = 2; j <= sqrt((double(i))); j++)
				if (i % j == 0) {
					f = false;
					break;
				}
		} while (f == false);
		if (k >= m && k % 2 != 0)
			cout << i << " ";
	}

	// просмотр результатов до нажатия любой клавиши
	cout << endl;
	system("pause");
}