#include <iostream>

using namespace std;

int main() {
	// ������� ���������
	setlocale(LC_ALL, "rus");
	// ���������� ����������
	int m, k, n, i, j;	
	bool f;
	// ���� ������� ������ � ������� �� ������
	do {
		m = n = 0;
		cout << "������� M � N> ";
		cin >> m >> n;
		if (m <= 0 || n < m)
			cout << "�������� �������� ������" << endl;
	} while (m <= 0 || n < m);
	// �������� ���� ������
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

	// �������� ����������� �� ������� ����� �������
	cout << endl;
	system("pause");
}