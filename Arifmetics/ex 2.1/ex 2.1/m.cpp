// 3

#include <iostream>
#include <iomanip>

using namespace std;


int main() {
	// русска€ кодировка
	setlocale(LC_ALL, "rus");
	// объ€вление переменных
	int i;
	double x, z = 1, t, g = 0, p = 0;
	// ввод данных
	cout << "¬ведите точность(Q) и значение X(Q)> ";
	cin >> t >> x;
	// основной цикл вычислени€
	double iks = 1;
	double fctrl = 1;
	double fctrlm = 2;
	double med = 1;
	for (i = 1; ; i++) {
		g = med * iks / fctrl;
		cout << g << endl;
		med *= -1;
		iks = iks*x*x;
		fctrl *= fctrlm;
		fctrlm++;
		z += g;
		if (abs(g) < t || (i!=1&&abs(p)-abs(g)<t))
			break;
		p = g;
	}
	// результат
	cout.precision(15);
	cout << z << endl;
	// просмотр результата до нажати€ любой клавиши
	system("pause");
	return 0;
}

