// 16

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	// ������� ���������
	setlocale(LC_ALL, "rus");
	// ���������� ����������
	int i;
	double p, g, t = 0, x, z = 0;
	// ���� ������
	do {
		x = 0;
		cout << "������� ��������(Q) � �������� X(Q, x != 0)> ";
		cin >> t >> x;
	} while (x == 0);
	g = 0;
	// �������� ���� ����������
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
	// ���������
	cout.precision(t);
	cout << z << endl;
	// �������� ���������� �� ������� ����� �������
	system("pause");
	return 0;
}