#include <iostream>

using namespace std;

int main() {
	// русская кодировка
	setlocale(LC_ALL, "rus");
	// объявление переменных
	int d = 0, e = 1, c, a, m;
	// ввод данных с "защитой от дурака"
	do {
		a = m = 0;
		cout << "Введите A и M> ";
		cin >> a >> m;
		if (a < 0 || a > 9)
			cout << "Неверные исходные данные\n";
	} while (a < 0 || a > 9);
	// основной цикл вывода чисел
	while (d < m) {
		if (d % 10 == a) 
			cout << d << " ";
		c = d + e;
		d = e;
		e = c;
	}
	// просмотр результата программы до нажатие любой клавиши
	cout << endl;
	system("pause");
}