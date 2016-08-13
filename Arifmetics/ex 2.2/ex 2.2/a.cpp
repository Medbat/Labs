// 16

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	// русска€ кодировка
	setlocale(LC_ALL, "rus");
	// объ€вление переменных
	int i;
	double p, g, t = 0, x, z = 0;
	// ввод данных
	do {
		x = 0;
		cout << "¬ведите точность(Q) и значение X(Q, x != 0)> ";
		cin >> t >> x;
	} while (x == 0);
	g = 0;
	// основной цикл вычислени€
	double iks = x;
	double fctrl = 1;
	double fctrlm = 2;
	double med = 1;
	for (i = 1; ; i++) {
		g = med * (iks/fctrl-1/iks) * (iks/fctrl-1/iks);
		iks *= x;
		med *= -1;
		fctrl *= fctrlm;
		fctrlm++;
		z += g;
		if (abs(g) < t || (i!=1&&abs(p)-abs(g)<t))
			break;
		p = g;
	}
	// результат
	cout.precision(t);
	cout << z << endl;
	// просмотр результата до нажати€ любой клавиши
	system("pause");
	return 0;
}