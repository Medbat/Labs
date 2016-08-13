#include "strlib.h"

int main() {
	setlocale(LC_ALL, "rus");
	int a, i, j, M = 0, N = 0;
	bool dir;
	char * buf = new char[1024];
	int ** Matrix;
	do {
		cout << "¬ведите количество строк массива (1-32676) > ";
		SuperCin(buf, M);
	} while (M < 1);
	do {
		cout << "¬ведите количество столбцов массива (1-32676) > ";
		SuperCin(buf, N);
	} while (N < 1);
	Give_Memory(Matrix, M, N);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++) {
			cout << "¬ведите элемент [" << i << "][" << j << "]>";
			SuperCin(buf, Matrix[i][j]);
		}
	cout << "»—’ќƒЌјя ћј“–»÷ј" << endl;
	Show_Matrix(Matrix, M, N);
	int ii;
	for (i = 0; i < N; i++) {
		do {
			cout << "¬ведите направление сортировки столбца номер " << i << " (0-по возрастанию, 1-по убыванию)> ";
			SuperCin(buf, ii);
		} while (ii < 0 || ii > 1);
		if (i == 1)
			dir = true;
		else
			dir = false;
		Qsort(Matrix, i, dir, 0, M - 1);
	}
	cout << "ќ“—ќ–“»–ќ¬јЌЌјя ћј“–»÷ј" << endl;
	Show_Matrix(Matrix, M, N);
	system("pause");
	delete [] buf;
	Delete_Matrix(Matrix, M);
	return 0;
}