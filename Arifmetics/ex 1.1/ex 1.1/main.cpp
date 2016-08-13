#include <iostream>

using namespace std;

int main() {
	// русская кодировка
	setlocale(LC_ALL, "rus");
	// объявление переменных
	int i = 0, a = 0, b = 1, c, m, n;
	// ввод данных с "защитой от дурака"
	do {
		m = n = 0;
		cout << "Введите M и N> ";
		cin >> m >> n;
		if (m <= 0 || n < m)
			cout << "Неверные исходные данные\n";
	} while (m <= 0 || n < m);
	// основной цикл вывода чисел
	while (i <= n) {
		if (i >= m) 
			cout << a << " ";
		c = a + b;
		a = b;
		b = c;
		i++;
	}
	// просмотр результата программы до нажатие любой клавиши
	cout << endl;
	system("pause");
}