#include <iostream>

using namespace std;

int main() {
	// ������� ���������
	setlocale(LC_ALL, "rus");
	// ���������� ����������
	int i = 0, a = 0, b = 1, c, m, n;
	// ���� ������ � "������� �� ������"
	do {
		m = n = 0;
		cout << "������� M � N> ";
		cin >> m >> n;
		if (m <= 0 || n < m)
			cout << "�������� �������� ������\n";
	} while (m <= 0 || n < m);
	// �������� ���� ������ �����
	while (i <= n) {
		if (i >= m) 
			cout << a << " ";
		c = a + b;
		a = b;
		b = c;
		i++;
	}
	// �������� ���������� ��������� �� ������� ����� �������
	cout << endl;
	system("pause");
}