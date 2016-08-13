#include <iostream>

using namespace std;

// �������� ������� ����������� �������� ����� ���� �����
bool need(int a);

int main() {
	// ������� ���������
	setlocale(LC_ALL, "rus");
	// ���������� ����������
	int n, i, j, k = 0;
	bool f;
	// ���� ������� ������ � ������� �� ������
	do {
		n = 0;
		cout << "������� N> ";
		cin >> n;
		if (n < 1)
			cout << "�������� �������� ������" << endl;
	} while (n < 1);
	if (n == 1)
		n = 2;
	// �������� ���� ������
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
	

	// �������� ����������� �� ������� ����� �������
	cout << endl;
	system("pause");
	return 0;
}

// ���������� ������� need
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