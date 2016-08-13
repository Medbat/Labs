#include "matrixlib.h"

void Give_Memory(int ** & a, int m, int n) {
	a = new int* [m];
	for (int i = 0; i < m; i++)
		a[i] = new int[n];
}

void Enter_Matrix(int ** &a, int &m, int &n) {
	int i, j;
	cout << "Введите размеры матрицы> ";
	cin >> m >> n;
	Give_Memory(a, m, n);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			cout << "[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
}

void Show_Matrix(int ** m, int a, int b, int c, int d) {
	int i, j;
	for (i = a; i < a + c; i++) {
		for (j = b; j < b + d; j++)
			cout << setw(4) << m[i][j];
		cout << endl;
	}
}

void Delete_Matrix(int ** & a, int m) {
	for (int i = 0; i < m; ++i )
        delete [] a[i];
    delete [] a;
}

void Load_Matrix_From_File(int ** & a, int &m, int &n, char file) {
	char filename[6] = " .txt";
	filename[0] = file;
	ifstream input(filename);
	if (!input) {
		cout << "Файл не найден.\n";
		return;
	}
	input >> m >> n;
	Give_Memory(a, m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			input >> a[i][j];
	input.close();
	cout << "Данные успешно загружены!\n";
}

void Transponate_Matrix(int **& m, int a, int b, int c) {
	int i, j;
	for (i = 0; i < c - 1 ; i++)
		for (j = i + 1; j < c; j++) 
			swap(m[a + i][b + j], m[a + j][b + i]);
}

void Calculate_B(int **& a, int m, int n, int &ba, int &bb, int &bdl) {
	int xStart = m - 1, yStart = 0, x, y, xmax, ymax, xmaxt = 0, ymaxt = 0, dl = 0, dlmax = 0;
	while (xStart != 0 || yStart != n) {
		for (x = xStart, y = yStart, dl = 0; x != m && y!= n; x++, y++) {
			if (a[x][y] == 0)
				dl = 0;
			else {
				if (dl == 0) {
					xmaxt = x;
					ymaxt = y;
				}
				dl++;
			}
			if (dl >= dlmax) {
				xmax = xmaxt;
				ymax = ymaxt;
				dlmax = dl;
			}
		}
		if (xStart > 0)
			xStart--;
		else
			yStart++;
	}
	ba = xmax;
	bb = ymax;
	bdl = dlmax;
}

void Turn_Matrix(int **& m, int a, int b, int c) {
	int h, k;
	int i, j, i1, j1;
	for (h = 0, i = a, j = b, i1 = a + c - 1 , j1 = b + c - 1; 
	c >= 2; 
	i++, j++, i1--, j1--, c = c - 2, h = 0) {
		while(h != c-1) {
			k = m[i + h][j1];
			m[i + h][j1]=m[i][j + h];
			m[i][j + h]=m[i1 - h][j];
			m[i1 - h][j]=m[i1][j1 - h];
			m[i1][j1 - h]=k;
			h++;
		}
	}
}

void Go(int ** m, int a, int b, int c) {
	int steps = 1, j, i, x = a, y = b;
	bool go = true;
	cout << "Вектор матрицы: ";
	for (i = 0; i < c * 2 - 2; i++) {
		for (j = 0; j < steps; j++) {
			cout << m[x][y] << " ";
			if (steps - 1 != j) {
				if (go) {
					x++;
						y--;
				}
				else {
					y++;
					x--;
				}
			}
		}
		if (i < c - 1)
			steps++;
		else
			steps--;
		if (go) {
			go = false;
			if (i == c - 1)
				y++;
			else
				x++;
		}
		else {
			go = true;
			if (i == c - 1)
				x++;
			else
				y++;
		}
	}
	cout << m[a + c - 1][b + c - 1] << endl;
}

void Bubble_Sort(int **& m, int a, int b, int c) {
	int i, j, k;
	for (k = 0; k < c * c - 1; k++)
		for (i = a + c - 1; i >= a; i--)
			for (j = b + c - 2; j >= b; j--) { 
				if (i != a + c - 1 && j + 1 == b + c - 1)
					if(m[i][j + 1] > m[i + 1][b]) 
						swap(m[i][j+1], m[i+1][b]);
				if(m[i][j] > m[i][j + 1]) 
					swap(m[i][j], m[i][j+1]);
			}
}