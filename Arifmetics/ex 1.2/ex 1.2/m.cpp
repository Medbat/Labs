#include <iostream>

using namespace std;

int main() {
	// ������� ���������
	setlocale(LC_ALL, "rus");
	// ���������� ����������
	int d = 0, e = 1, c, a, m;
	// ���� ������ � "������� �� ������"
	do {
		a = m = 0;
		cout << "������� A � M> ";
		cin >> a >> m;
		if (a < 0 || a > 9)
			cout << "�������� �������� ������\n";
	} while (a < 0 || a > 9);
	// �������� ���� ������ �����
	while (d < m) {
		if (d % 10 == a) 
			cout << d << " ";
		c = d + e;
		d = e;
		e = c;
	}
	// �������� ���������� ��������� �� ������� ����� �������
	cout << endl;
	system("pause");
}